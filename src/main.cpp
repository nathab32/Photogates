#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Button.h>

Button right(6, 50, 1000);
Button left(7, 50, 1000);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int photo0 = 0;
const int photo1 = 1;

//calibrate when phototransistors are unlit to get full scale value
double sensitivity = 1.0;
int threshold0, threshold1;
unsigned long initialTime;
bool timing = false;
bool timeRecorded = false;

const int length = 3;
float times[length];

void resetSensitivity(){
  threshold0 = (int)((0.5/sensitivity) * analogRead(photo0));
  threshold1 = (int)((0.5/sensitivity) * analogRead(photo1));
  Serial.print("sensitivity reset, threshold0: ");
  Serial.print(threshold0);
  Serial.print(", threshold1: ");
  Serial.println(threshold1);

  lcd.setCursor(7, 1);
  lcd.print("Sens rst.");
}

float* updateTimes(float* array, float newTime){
  
  for (int i = length-2; i >= 0; i--) {
    array[i + 1] = array[i];
  }
  array[0] = newTime;

  // char buffer[50];
  // sprintf(buffer, "[%lu, %lu, %lu]", times[0], times[1], times[2]);
  // Serial.println(buffer);
  return array;
}

void updateLCD(){
  lcd.clear();

  char buffer1[50];
  char floatBuffer1[10], floatBuffer2[10], floatBuffer3[10];

  dtostrf(times[0], 6, 3, floatBuffer1);
  dtostrf(times[1], 6, 3, floatBuffer2);
  dtostrf(times[2], 6, 3, floatBuffer3);

  snprintf(buffer1, sizeof(buffer1), "%s,%s", floatBuffer1, floatBuffer2);

  Serial.println(buffer1);
  Serial.println(floatBuffer3);

  lcd.print(buffer1);
  lcd.setCursor(0, 1);
  lcd.print(floatBuffer3);
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("Photogate");

  threshold0 = (int)((0.5/sensitivity) * analogRead(photo0));
  threshold1 = (int)((0.5/sensitivity) * analogRead(photo1));

  right.pressFunction(resetSensitivity);
}

void loop() {
  right.handle();

  // Serial.print(">base:0, peak:5");
  // Serial.print(",photo0: ");
  // Serial.print(analogRead(photo0)*5/1024.0);
  // Serial.print(",photo1: ");
  // Serial.println(analogRead(photo1)*5/1024.0);


  if(!timing && (analogRead(photo0) > threshold0)){
    timing = true;
    initialTime = micros();
    Serial.println("Timing...");

    lcd.setCursor(7, 1);
    lcd.print("Timing...");
  }

  if(timing){

    if(!timeRecorded && (analogRead(photo1) > threshold1)){
      Serial.println("timed");
      updateTimes(times, (micros() - initialTime)/1000000.0);
      updateLCD();
      timeRecorded = true;
    }

    if(timeRecorded && (analogRead(photo1) < threshold1)){
      timing = false;
      timeRecorded = false;
      Serial.println("booleans reset");
    }
  }

  
}
