// zmenit SS pin a D100 v knihovne

#include <RFM69.h>
#include <SPI.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include "RTClib.h"

#define DHTPIN        2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

#define NETWORKID     0
#define MYNODEID      1 //prohodit
#define TONODEID      2 //prohodit

#define FREQUENCY     RF69_433MHZ
#define ENCRYPT       true
#define ENCRYPTKEY    "CansatFlyBits017"
#define USEACK        false

RFM69 radio;

int korekce = 32;
char sendbuffer[62];

int svetelny_senzor = A1;

int fotorezistor = A0;

String den_noc = "err";

RTC_DS1307 RTC;


void setup()
{  
  SPI.begin();
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setFrequency(433700000);
  radio.setHighPower();

  if (ENCRYPT)
  {
    radio.encrypt(ENCRYPTKEY);
  }
  dht.begin();
  
  bmp.begin();

  RTC.begin();

  Serial.begin(9600);
  
  delay(200);
}

void loop()
{  
  String teplota_dht = "TD" + String(float(dht.readTemperature())) + "C";
  String vlhkost = " VL" + String(float(dht.readHumidity()));

  String teplota_bmp = "TB" + String(float(bmp.readTemperature()));
  String tlak = " Tl" + String(float(bmp.readPressure()));
  String nadm_vyska = "NV" + String(float(bmp.readAltitude()));

  String svetlo = "Sv" + String(float(analogRead(A1) * 0.9765625));

  if (analogRead(A0) > 100)
  {
    String den_noc = "D:";
  }
  else
  {
    String den_noc = "N";
  }

  DateTime now = RTC.now();
  String cas = String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + ":" + String(now.second(), DEC);

  String data = cas + teplota_dht + vlhkost + teplota_bmp + tlak + nadm_vyska + den_noc + svetlo;

  int delka = data.length();

  for (byte i = 0; i < delka; i++)
  {
    sendbuffer[i] = data[i];
  }
  radio.send(TONODEID, sendbuffer, delka);

  delay(100);
}
