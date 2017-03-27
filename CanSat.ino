// zmenit SS pin a D100 v knihovne

#include <RFM69.h>
#include <SPI.h>
#include <Wire.h>

#define NETWORKID     0
#define MYNODEID      1 //prohodit
#define TONODEID      2 //prohodit

#define FREQUENCY   RF69_433MHZ

#define ENCRYPT       true
#define ENCRYPTKEY    "CansatFlyBits017"

#define USEACK        false

RFM69 radio;

int korekce = 32;
char sendbuffer[62];

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
  
}

void loop()
{
  String teplota = "Teplota: C;";

  String data = teplota;

  int delka = data.length();

  for (byte i = 0; i < delka; i++)
  {
    sendbuffer[i] = data[i];
  }
  radio.send(TONODEID, sendbuffer, delka);

  delay(300);
}
