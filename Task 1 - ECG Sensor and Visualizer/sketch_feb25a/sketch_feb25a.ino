void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

void loop() { 
  if(digitalRead(10) == 1 || digitalRead(11) == 1){
    Serial.println("!");
  }
        Serial.println(analogRead(A0));
  delay(20);
}
