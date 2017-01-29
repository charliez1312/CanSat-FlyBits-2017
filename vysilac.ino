#include <RFM69.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define NETWORKID     0
#define MYNODEID      1 //prohodit
#define TONODEID      2 //prohodit

#define FREQUENCY   RF69_433MHZ

#define ENCRYPT       true
#define ENCRYPTKEY    "CansatFlyBits017"

#define USEACK        false

Adafruit_BMP085 bmp180;

RFM69 radio;

int korekce = 32;
char sendbuffer[62];

void setup()
{
  Serial.begin(9600);
  Serial.print("Vysilac ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" pripraven");  

  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setFrequency(433700000);
  radio.setHighPower();

  if (ENCRYPT)
  {
    radio.encrypt(ENCRYPTKEY);
  }

  bmp180.begin();
}

void loop()
{
  String teplota = "Teplota: " + String(bmp180.readTemperature()) + " C;";
  String tlak = " Tlak: " + String((bmp180.readPressure() + korekce*100)/100.00) + " P;";
  String vyska = " Nadm. vyska: " + String(bmp180.readAltitude(bmp180.readPressure() + korekce*100));

  String data = teplota + tlak + vyska;

  int delka = data.length();

  for (byte i = 0; i < delka; i++)
  {
    sendbuffer[i] = data[i];
  }
  radio.send(TONODEID, sendbuffer, delka);

  delay(300);
}
