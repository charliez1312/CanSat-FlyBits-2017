#include <RFM69.h>
#include <SPI.h>

#define NETWORKID     0
#define MYNODEID      2 //prohodit
#define TONODEID      1 //prohodit

#define FREQUENCY   RF69_433MHZ

#define ENCRYPT       true
#define ENCRYPTKEY    "CansatFlyBits017"

#define USEACK        false

RFM69 radio;

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
    radio.encrypt(ENCRYPTKEY);
}

void loop()
{
  static char sendbuffer[62];

  if (radio.receiveDone())
  {
    Serial.print("zprava [");

    for (byte i = 0; i < radio.DATALEN; i++)
    {
      Serial.print((char)radio.DATA[i]);
    }

    Serial.print("], intenzita signalu ");
    Serial.println(radio.RSSI);

    if (radio.ACKRequested())
    {
      radio.sendACK();
      Serial.println("ACK odeslan");
    }
  }
}
