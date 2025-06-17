using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ScottPlot;
using ScottPlot.Plottables;
using ScottPlot.WPF;
using System.IO.Ports;
using System.Diagnostics;
using ScottPlot.AxisPanels;
using System.Windows.Threading;
using ECGVisualizer.Filters;

namespace ECGVisualizer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 

    public partial class MainWindow : Window
    {
           SerialPort port = new SerialPort();
        List<int> values = new List<int>();
        Stopwatch watch;
        int counter = 0;
        DataLogger logger;
        private readonly object lockObject = new object();
        private bool isRunning = true;
        bool ApplyButterWorthFilter = false;
        bool ApplyLowPassFilter = false;
        bool ApplyHighPassFilter = false;
        bool ApplyMovingAverageFilter = false;
        FrequencyFilter Filter = new FrequencyFilter();
        string lbText;
        string errorText;
        private long lastRecordedPeakTime = 0;
        private Queue<double> recentRRIntervals = new Queue<double>(); // Store recent intervals
        private const int MAX_RR_INTERVALS = 10; // Number of intervals to average
        private bool invertQRSWave = false; // Flag for QRS wave inversion

        public MainWindow()
        {
            InitializeComponent();

            Application.Current.DispatcherUnhandledException += (s, e) =>
            {
                Debug.WriteLine($"Unhandled exception: {e.Exception.Message}");
                e.Handled = true; // Prevent the application from crashing
            };

            port.PortName = getActivePort();
            port.BaudRate = 115200;

            logger = realTimePlot.Plot.Add.DataLogger();
            logger.LineColor = ScottPlot.Color.FromColor(System.Drawing.Color.Red);
            watch = new Stopwatch();

            // GUI update timer
            DispatcherTimer guiTimer = new DispatcherTimer();
            guiTimer.Interval = TimeSpan.FromMilliseconds(16); // 60 FPS
            guiTimer.Tick += UpdatePlot;
            guiTimer.Start();



            // Start data collection in separate thread
            Task.Run(DataCollectionLoop);
        }

        private async Task DataCollectionLoop()
        {

            try
            {
                port.Open();
                watch.Start();

                while (isRunning)
                {
                    if (port.BytesToRead > 0)
                    {
                        string readingString = port.ReadLine();
                        if (double.TryParse(readingString, out double reading))
                        {
                            lock (lockObject)
                            {
                                if(reading >= 450)
                                {
                                    long currentTime = watch.ElapsedMilliseconds;

                                    if (lastRecordedPeakTime > 0) // Skip first peak as we need two points
                                    {
                                        double timePerRate = (currentTime - lastRecordedPeakTime) / 1000.0; // Convert to seconds

                                        // Add to recent intervals
                                        recentRRIntervals.Enqueue(timePerRate);
                                        if (recentRRIntervals.Count > MAX_RR_INTERVALS)
                                            recentRRIntervals.Dequeue();

                                        // Calculate average heart rate from recent intervals
                                        if (recentRRIntervals.Count > 0)
                                        {
                                            double averageInterval = recentRRIntervals.Average();
                                            double heartRatePerMinute = 60.0 / averageInterval; // Convert to BPM

                                            // Filter out unrealistic values
                                            //Less than 30 is Bardycardia
                                            //More than 160 is supraventricular tachycardia
                                            /*
                                             * Irregular heartbeat or absence of P-wave: Atrial Fibrillation
                                                Resting Heart Rate of more than 100: Tachyarrhythmia
                                                Sawtooth P wave: Atrial flutter
                                                Depression of ST-segment: it might indicate Ischemia
                                                Elevation of ST-segment: it might indicate myocardial Infarction
                                             */
                                            if (heartRatePerMinute >= 30 && heartRatePerMinute <= 160)
                                            {
                                                double error = Math.Abs((heartRatePerMinute - 80) / 80) * 100;
                                                lbText = $"Average Heart Rate: {heartRatePerMinute:F1} BPM";
                                                errorText = $"Average Error : {error:F1} %";
                                            }
                                        }
                                    }

                                    lastRecordedPeakTime = currentTime;
                                }
                                if (ApplyLowPassFilter)
                                {
                                    reading = Filter.ProcessNewSample(reading, FrequencyFilter.FilterType.LowPass);
                                }
                                if (ApplyHighPassFilter)
                                {
                                    reading = Filter.ProcessNewSample(reading, FrequencyFilter.FilterType.HighPass);
                                }
                                if (ApplyButterWorthFilter)
                                {
                                    reading = Filter.ProcessNewSample(reading, FrequencyFilter.FilterType.Butterworth);
                                }
                                if (ApplyMovingAverageFilter)
                                {
                                    reading = Filter.ProcessNewSample(reading, FrequencyFilter.FilterType.MovingAverage);
                                }
                                
                                if (invertQRSWave)
                                {
                                    reading *= -1; // Invert the QRS wave
                                }

                                logger.Data.Coordinates.Add(new Coordinates(counter, reading));
                                counter++;
                                if (counter > 300)
                                {
                                    logger.Data.Coordinates.RemoveAt(0);
                                }
                            }
                        }
                    }
                    await Task.Delay(1); // Small delay to prevent CPU hogging
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error in data collection: {ex.Message}");
                Dispatcher.Invoke(() =>
                {
                    MessageBox.Show($"Error: {ex.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                });
            }
        }

        private void UpdatePlot(object sender, EventArgs e)
        {
            try
            {
                lock (lockObject)
                {
                    realTimePlot.Plot.Axes.AutoScaleY();
                    realTimePlot.Refresh();
                    lbAverageHeartRate.Text = lbText;
                    lbError.Text = errorText;
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        string getActivePort()
        {
            return "COM13";
        }

        // Make sure to clean up when the window closes

        private void Window_Closed(object sender, EventArgs e)
        {
            isRunning = false;
            if (port.IsOpen)
            {   
                port.Close();
            }
            base.OnClosed(e);
        }

        private void cbLowPassFilter_Checked(object sender, RoutedEventArgs e)
        {
            ApplyLowPassFilter = true;
        }

        private void cbLowPassFilter_Unchecked(object sender, RoutedEventArgs e)
        {
            ApplyLowPassFilter = false;
        }

        private void cbHighPassFilter_Checked(object sender, RoutedEventArgs e)
        {
            ApplyHighPassFilter = true;
        }

        private void cbHighPassFilter_Unchecked(object sender, RoutedEventArgs e)
        {
            ApplyHighPassFilter = false;
        }

        private void cbButterworthFilter_Checked(object sender, RoutedEventArgs e)
        {
            ApplyButterWorthFilter = true;
        }

        private void cbButterworthFilter_Unchecked(object sender, RoutedEventArgs e)
        {
            ApplyButterWorthFilter = false;
        }

        private void cbMovingAverageFilter_Checked(object sender, RoutedEventArgs e)
        {
            ApplyMovingAverageFilter = true;
        }

        private void cbMovingAverageFilter_Unchecked(object sender, RoutedEventArgs e)
        {
            ApplyMovingAverageFilter = false;
        }
        private void btnInvertQRS_Click(object sender, RoutedEventArgs e)
{
    invertQRSWave = !invertQRSWave; // Toggle inversion
}

    }

}   