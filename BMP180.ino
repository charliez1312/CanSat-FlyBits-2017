#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp180;

int correction = 32;
int index = 1;

void setup() {
  Serial.begin(9600);
  bmp180.begin();
}

void loop() {
  Serial.print(" Index: ");
  Serial.print(index);
  
  Serial.print(" ;Teplota [stupen Celsia]: ");
  Serial.print(bmp180.readTemperature());

  Serial.print(" ;Tlak [Pascal]: ");
  Serial.print((bmp180.readPressure() + correction*100)/100.00);

  Serial.print(" ;Nadmorska vyska [metr]: ");
  Serial.println(bmp180.readAltitude(bmp180.readPressure() + correction*100));
  
  delay(1000);
  index++;
}
