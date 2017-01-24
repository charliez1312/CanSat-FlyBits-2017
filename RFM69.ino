#include <RFM69.h>
#include <SPI.h>

#define NETWORKID     0
#define MYNODEID      2
#define TONODEID      1 

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
  Serial.println("pripraven");  

  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setHighPower();

  if (ENCRYPT)
    radio.encrypt(ENCRYPTKEY);
}

void loop()
{

  static char sendbuffer[62];
  static int sendlength = 0;

  // ODESILANI

  if (Serial.available() > 0)
  {
    char input = Serial.read();

    if (input != '\r')
    {
      sendbuffer[sendlength] = input;
      sendlength++;
    }

    if ((input == '\r') || (sendlength == 61))
    {

      Serial.print("posilam do Vysilac ");
      Serial.print(TONODEID, DEC);
      Serial.print(", zprava [");
      for (byte i = 0; i < sendlength; i++)
        Serial.print(sendbuffer[i]);
      Serial.println("]");

      if (USEACK)
      {
        if (radio.sendWithRetry(TONODEID, sendbuffer, sendlength))
          Serial.println("ACK prijat!");
        else
          Serial.println("ACK neprijat");
      }


      else
      {
        radio.send(TONODEID, sendbuffer, sendlength);
      }

      sendlength = 0;
    }
  }

  // PRIJIMANI

  if (radio.receiveDone()) // Got one!
  {
    Serial.print("prijato z Vysilac ");
    Serial.print(radio.SENDERID, DEC);
    Serial.print(", zprava [");

    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);


    Serial.print("], intenzita signalu ");
    Serial.println(radio.RSSI);

    if (radio.ACKRequested())
    {
      radio.sendACK();
      Serial.println("ACK odeslan");
    }

  }
}
