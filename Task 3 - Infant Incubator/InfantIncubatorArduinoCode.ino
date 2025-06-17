#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define lampPin 6
#define coolingFanPin 7
#define heatingFanPin 10
#define babyTemperaturePin 13

OneWire oneWire(babyTemperaturePin);

DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27,  16, 2);

DHT dht(2,DHT11);
int temp;
int hum;
float babyTempCelcius=0;

void PrintReadings(){
    lcd.setCursor(9,0);
  lcd.print(temp);
  lcd.setCursor(11,0);
  lcd.print("C");
  lcd.setCursor(12, 0);
  lcd.print("/");
  lcd.setCursor(13, 0);
  lcd.print(hum);
  lcd.setCursor(15, 0);
  lcd.print("%");
    lcd.setCursor(10, 1);
  lcd.print(babyTempCelcius);
      lcd.setCursor(15, 1);
  lcd.print("C");
}

void setup() {
  dht.begin();
  sensors.begin();
  lcd.init();
  lcd.backlight();
  pinMode(lampPin, OUTPUT);
  pinMode(coolingFanPin, OUTPUT);
  pinMode(heatingFanPin, OUTPUT);
    lcd.setCursor(0,0);
  lcd.print("Temp/Hum:");
  lcd.setCursor(0, 1);
  lcd.print("Baby Temp:");
}

void loop() { 
  delay(100);
  temp= dht.readTemperature(); 
  sensors.requestTemperatures(); 
  babyTempCelcius = sensors.getTempCByIndex(0);
  Serial.print(temp);
  hum = dht.readHumidity();
  if(!isnan(temp)){
    if(temp< 37){
      digitalWrite(lampPin, HIGH);
      digitalWrite(coolingFanPin, LOW);
      analogWrite(heatingFanPin, 200);
    }
    else{
        digitalWrite(lampPin, LOW);
        digitalWrite(coolingFanPin, HIGH);
        analogWrite(heatingFanPin, 0);
    }
    PrintReadings();
  }
}