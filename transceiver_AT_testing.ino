#include <SoftwareSerial.h>

SoftwareSerial transceiverSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  Serial.println("Wait for AT commands");
  mySerial.begin(9600);
}

void loop(){
  if (transceiverSerial.available()){
    Serial.write(transceiverSerial.read());
  }
  if (Serial.available()){
    transceiverSerial.write(Serial.read());
  }
}
