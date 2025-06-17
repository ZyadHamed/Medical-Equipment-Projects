#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define S0 6
#define S1 7
#define S2 9
#define S3 10
#define sensorOut 8
#define BloodLeakAlarmPin 2
#define BubblesAlarmPin 11
#define SuddenDisconnectionAlarmPin 12
#define IRSensorPin A0

#define BloodPumpPin 4
#define DialysatePumpPin 5
#define ONE_WIRE_BUS 13

float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
int RateCalibrationNumber;
float AccX, AccY, AccZ;
float AngleRoll = 0;
float AnglePitch = 0;
float AngleYaw = 0;
uint32_t LoopTimer;
unsigned long lastMillis;
unsigned long gyrotime = 0;

OneWire oneWire(ONE_WIRE_BUS);	
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,  16, 2);


int redMin = 150; // Red minimum value
int redMax = 1700; // Red maximum value
int greenMin = 170; // Green minimum value
int greenMax = 2040; // Green maximum value
int blueMin = 50; // Blue minimum value
int blueMax = 600; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

bool flag = false;
bool motionFlag = false;

void TurnBloodPumpOn(){
  digitalWrite(BloodPumpPin, HIGH);
}

void TurnBloodPumpOff(){
  digitalWrite(BloodPumpPin, LOW);
}

void TurnDialysatePumpOn(){
  digitalWrite(DialysatePumpPin, HIGH);
}

void TurnDialysatePumpOff(){
  digitalWrite(DialysatePumpPin, LOW);
}


// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

void UpdateColorSensorReadings(){
  	// Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	redValue = map(redPW, redMin,redMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	greenValue = map(greenPW, greenMin,greenMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Blue value
	bluePW = getBluePW();
	// Map to value from 0-255
	blueValue = map(bluePW, blueMin,blueMax,255,0);
	// Delay to stabilize sensor
	delay(200);
}

float GetTemperature(){
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}

void gyro_signals(void) {
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(); 
  Wire.requestFrom(0x68,6);
  int16_t AccXLSB = Wire.read() << 8 | Wire.read();
  int16_t AccYLSB = Wire.read() << 8 | Wire.read();
  int16_t AccZLSB = Wire.read() << 8 | Wire.read();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B); 
  Wire.write(0x8);
  Wire.endTransmission();     
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  int16_t GyroX=Wire.read()<<8 | Wire.read();
  int16_t GyroY=Wire.read()<<8 | Wire.read();
  int16_t GyroZ=Wire.read()<<8 | Wire.read();
  RateRoll=(float)GyroX/65.5;
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;
  AccX=(float)AccXLSB/4096;
  AccY=(float)AccYLSB/4096;
  AccZ=(float)AccZLSB/4096;
}

void setup() {
	// Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

  pinMode(BloodLeakAlarmPin, OUTPUT);
	pinMode(BubblesAlarmPin, OUTPUT);
	pinMode(SuddenDisconnectionAlarmPin, OUTPUT);

  digitalWrite(BloodLeakAlarmPin,LOW);
	digitalWrite(BubblesAlarmPin,LOW);
  digitalWrite(SuddenDisconnectionAlarmPin,LOW);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

	// Set Frequency scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

  pinMode(BloodPumpPin, OUTPUT);
  pinMode(DialysatePumpPin, OUTPUT);

  sensors.begin();

  lcd.init();
  lcd.backlight();

	// Setup Serial Monitor
	Serial.begin(9600);

    Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68); 
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  for (RateCalibrationNumber=0; RateCalibrationNumber<2000; RateCalibrationNumber ++) {
    gyro_signals();
    RateCalibrationRoll+=RateRoll;
    RateCalibrationPitch+=RatePitch;
    RateCalibrationYaw+=RateYaw;
    delay(1);
  }
  RateCalibrationRoll/=2000;
  RateCalibrationPitch/=2000;
  RateCalibrationYaw/=2000;
  LoopTimer=micros();
  lastMillis = millis();
  gyrotime = millis();
}

void loop() {
  UpdateColorSensorReadings();
    gyro_signals();
  RateRoll-=RateCalibrationRoll;
  RatePitch-=RateCalibrationPitch;
  RateYaw-=RateCalibrationYaw;
  AngleRoll = 0.004 * RateRoll + AngleRoll;
  AnglePitch = 0.004 * RatePitch + AnglePitch;
  AngleYaw = 0.004 * RateYaw + AngleYaw;
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(6,0);
  lcd.print(GetTemperature());
  TurnDialysatePumpOn();
  if(redValue > 230){
    lcd.setCursor(0,1);
    lcd.print("Leak Detected!");
    digitalWrite(BloodLeakAlarmPin,HIGH);
    flag = true;
  }
  else{
    lcd.setCursor(0,1);
    flag = false;
    digitalWrite(BloodLeakAlarmPin,LOW);
  }

  if(AccX >= 0.5 || AccY >= 0.5 || AccZ >= 0.5){
    motionFlag = true;
  }

  if(analogRead(IRSensorPin) >= 200 && analogRead(IRSensorPin) <= 250 ){
    lcd.setCursor(0,1);
    lcd.print("Bubbles Detected!");
    digitalWrite(BubblesAlarmPin,HIGH);
    //flag = true;
  }
  else{
    digitalWrite(BubblesAlarmPin,LOW);
    lcd.setCursor(0,1);
    lcd.print("          ");
  }
  Serial.println(GetTemperature());
  if(flag == true){
    Serial.println("error here!");
  TurnBloodPumpOff();
  }
  else{
      TurnBloodPumpOn();
  }
  if(motionFlag == true){
    Serial.println("error here!");
    TurnBloodPumpOff();
    TurnDialysatePumpOff();
    digitalWrite(SuddenDisconnectionAlarmPin, HIGH);
  }
  if(millis() - gyrotime >= 10000){
    motionFlag = true;
  }
}