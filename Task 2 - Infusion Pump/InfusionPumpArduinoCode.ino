
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define buzzerPin 4
LiquidCrystal_I2C lcd(0x27,  16, 2);
volatile int flow_pulses;  
float vol = 0.0;
float l_second;
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime = 0;
unsigned long lastPrintTime = 0;
unsigned long lastRecordedFlowPulses = 0;
unsigned long lastErrorTime = 0;
int valuetobewritten = 0;
bool error = false;
bool finished = false;
void flow () 
{
   flow_pulses++;
}

void PrintReadings(){
          Serial.print("Rate: ");
        Serial.print(l_second);
        Serial.println(" mL/s");
        Serial.print("Vol:");
        Serial.print(vol);
        Serial.println(" mL");
        //If there the tube is not clogged or the water has not ran out, print the rate and the volume
        if(!error){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Rate:");
        lcd.setCursor(6, 0);
        lcd.print(l_second);

        lcd.setCursor(0,1);
        lcd.print("Volume:");
        lcd.setCursor(7, 1);
        lcd.print(vol);
        }
}

void UpdateFlowSensorReadings(){
   // Every second, calculate and print litres/hour
   if(millis() - currentTime >= 100)
   {
    currentTime = millis(); // Updates cloopTime
      //For every liter, 450 pulses. We use the delta pulses because we want to calculate the instantanous flow rate at each 100 milliseconds
      unsigned long deltaFlowPulses = (flow_pulses - lastRecordedFlowPulses) * 1000;
      l_second = (deltaFlowPulses / 450.0) / 0.1; //L/second
          //If the flow rate is 0 or larger than 115 (air is being pumped in, water ran out) output an error message
          if((l_second <= 2 || l_second >= 115) && finished == false)
          {
          analogWrite(3, 0);
          //lcd.clear();
          //lcd.setCursor(5,0);
          //lcd.print("ERROR");
          //lcd.setCursor(0,1);
          //lcd.print("Source Empty!");
          digitalWrite(buzzerPin, HIGH);
          error = true;
          }
          else if(finished == false){
            //If no errors exist, add the calculated instantanous volume to the total volume
            error = false;
            vol = vol + (deltaFlowPulses / 450.0);
            digitalWrite(buzzerPin, LOW);
            error = false;


            PrintReadings();
          }
          else if(finished == true){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("done!");
          }
      lastRecordedFlowPulses = flow_pulses;
   }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); 
  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
    lcd.init();
    lcd.backlight();
   currentTime = millis();
   Serial.begin(9600);
   lcd.setCursor(0,0);
   lcd.print("Enter volume:");
   Serial.write("Please enter a required volume in mL: ");
  while(valuetobewritten < 1){
      if(Serial.available()){
        valuetobewritten = Serial.parseFloat();
      }
    }


}

//( PULSATING )// 
void loop() {
  //Take input value from serial monitor

    //Update the measured flowrates and the total volume 
      UpdateFlowSensorReadings();
      //When we reach desired volume, stop the pump and print done
      if(vol >= valuetobewritten){
        analogWrite(3, 0);
        finished = true;
      }
      else{

        //Keep the pump working otherwise
           analogWrite(3, 255);
      }

}