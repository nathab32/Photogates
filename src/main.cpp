#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Button.h>

Button button1(6, 50, 1000);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int photoresistor0 = 0;
const int photoresistor1 = 1;

double sensitivity = 1.0;
int ref0, ref1;
unsigned long initialTime;
bool timing;

void resetSensitivity(){
  ref0 = analogRead(photoresistor0);
  ref1 = analogRead(photoresistor1);
  Serial.println("sensitivity reset");
  // lcd.clear();
  // lcd.println("Sensitivity reset");
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Hello World");

  ref0 = analogRead(photoresistor0);
  ref1 = analogRead(photoresistor1);

  button1.pressFunction(resetSensitivity);
}

void loop() {
  button1.handle();

  
  if(!timing && (ref0 - analogRead(photoresistor0) > (0.1/sensitivity) * ref0)){
    timing = true;
    initialTime = micros();
    Serial.println("triggered");
    lcd.clear();
    lcd.print("triggered");
  }

  if(timing){
    if(ref1 - analogRead(photoresistor1) > (0.1/sensitivity) * ref1){
      lcd.clear();
      Serial.println(micros() - initialTime);
      lcd.print((micros() - initialTime)/1000000.0, 3);
      timing = false;
    }
  }

}
