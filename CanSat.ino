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

int fotorezistor_hodnota = 0;

int reprak = 4;
int reprak_pocet;
float nadmorska_vyska_zaloha = 0;

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
  delay(100);

  RTC.begin();
  delay(100);
  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  pinMode(reprak, OUTPUT);
  //digitalWrite(reprak, HIGH);

  Serial.begin(9600);
  
  delay(200);
}

void loop()
{  
  String teplota_dht = "TD" + String(float(dht.readTemperature()));
  String vlhkost = "VL" + String(int(dht.readHumidity()));

  String teplota_bmp = "TB" + String(float(bmp.readTemperature()));
  String tlak = " Tl" + String(int(bmp.readPressure()));

  float nadm_vyska_cislo = bmp.readAltitude();
  
  //String nadm_vyska = "NV" + String(float(bmp.readAltitude()));
  String nadm_vyska = "NV" + String(nadm_vyska_cislo);

  if ((nadmorska_vyska_zaloha > 0.0) && (nadmorska_vyska_zaloha - 1 <= nadm_vyska_cislo <= nadmorska_vyska_zaloha + 1))
  {
    reprak_pocet++;
    if (reprak_pocet >= 250)
    {
      digitalWrite(reprak, HIGH);
    }
  }
  else
  {
    nadmorska_vyska_zaloha = nadm_vyska_cislo;
    reprak_pocet = 0;
  }

  String svetlo = "Sv" + String(float(analogRead(A1) * 0.9765625));


  fotorezistor_hodnota = analogRead(A0);
  
  
  if (fotorezistor_hodnota > 150)
  {
    String den_noc = "D";
  }
  else
  {
    String den_noc = "N";
  }

  delay(30);

  DateTime now = RTC.now();
  String cas = String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + ":" + String(now.second(), DEC);

  String data = cas + teplota_dht + vlhkost + teplota_bmp + tlak + nadm_vyska + svetlo + "v" + String(float(reprak_pocet));

  int delka = data.length();

  for (byte i = 0; i < delka; i++)
  {
    sendbuffer[i] = data[i];
  }
  radio.send(TONODEID, sendbuffer, delka);

  delay(30);
}
