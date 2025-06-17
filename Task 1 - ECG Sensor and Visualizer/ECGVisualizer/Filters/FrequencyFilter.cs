using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ECGVisualizer.Filters
{
    public class FrequencyFilter
    {
        public static List<double> LowPassFilter(List<double> input, double alpha)
        {
            // alpha should be between 0 and 1
            // smaller alpha = smoother filter but more lag
            List<double> output = new List<double>();
            double lastOutput = input[0];

            foreach (double value in input)
            {
                double currentOutput = lastOutput + alpha * (value - lastOutput);
                output.Add(currentOutput);
                lastOutput = currentOutput;
            }

            return output;
        }

        public static List<double> HighPassFilter(List<double> input, double alpha)
        {
            // alpha should be between 0 and 1
            // larger alpha = smoother filter
            List<double> output = new List<double>();
            double lastInput = input[0];
            double lastOutput = 0;

            foreach (double value in input)
            {
                double currentOutput = alpha * (lastOutput + value - lastInput);
                output.Add(currentOutput);
                lastOutput = currentOutput;
                lastInput = value;
            }

            return output;
        }

        public static List<double> ButterworthFilter(List<double> input, double cutoffFrequency, double samplingFrequency)
        {
            // Second-order Butterworth low-pass filter
            List<double> output = new List<double>();

            // Compute filter coefficients
            double omega = 2.0 * Math.PI * cutoffFrequency / samplingFrequency;
            double c = 1.0 / Math.Tan(omega / 2.0);
            double a1 = 2.0 * (1.0 - c * c) / (1.0 + Math.Sqrt(2.0) * c + c * c);
            double a2 = (1.0 - Math.Sqrt(2.0) * c + c * c) / (1.0 + Math.Sqrt(2.0) * c + c * c);
            double b0 = 1.0 / (1.0 + Math.Sqrt(2.0) * c + c * c);
            double b1 = 2.0 * b0;
            double b2 = b0;

            // Initialize delay elements
            double x1 = input[0];
            double x2 = input[0];
            double y1 = input[0];
            double y2 = input[0];

            // Apply filter
            foreach (double value in input)
            {
                double currentOutput = b0 * value + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
                output.Add(currentOutput);

                // Update delay elements
                x2 = x1;
                x1 = value;
                y2 = y1;
                y1 = currentOutput;
            }

            return output;
        }

        // Moving average filter (another type of low-pass filter)
        public static List<double> MovingAverageFilter(List<double> input, int windowSize)
        {
            List<double> output = new List<double>();
            Queue<double> window = new Queue<double>();
            double sum = 0;

            // Initialize window
            for (int i = 0; i < windowSize && i < input.Count; i++)
            {
                window.Enqueue(input[i]);
                sum += input[i];
                output.Add(sum / window.Count);
            }

            // Process remaining samples
            for (int i = windowSize; i < input.Count; i++)
            {
                sum -= window.Dequeue();
                window.Enqueue(input[i]);
                sum += input[i];
                output.Add(sum / windowSize);
            }

            return output;
        }

        // Example usage with real-time data
        private Queue<double> dataBuffer = new Queue<double>();
        private const double BUFFER_SIZE = 100;

        public double ProcessNewSample(double newSample, FilterType filterType)
        {
            // Add new sample to buffer
            dataBuffer.Enqueue(newSample);
            if (dataBuffer.Count > BUFFER_SIZE)
            {
                dataBuffer.Dequeue();
            }

            // Apply selected filter
            List<double> filtered;
            switch (filterType)
            {
                case FilterType.LowPass:
                    filtered = LowPassFilter(dataBuffer.ToList(), 0.1);
                    break;
                case FilterType.HighPass:
                    filtered = HighPassFilter(dataBuffer.ToList(), 0.95);
                    break;
                case FilterType.Butterworth:
                    filtered = ButterworthFilter(dataBuffer.ToList(), 0.5, 1000);
                    break;
                default:
                    filtered = MovingAverageFilter(dataBuffer.ToList(), 5);
                    break;
            }

            // Return most recent filtered value
            return filtered.Last();
        }

        public enum FilterType
        {
            LowPass,
            HighPass,
            Butterworth,
            MovingAverage
        }
    }
}
