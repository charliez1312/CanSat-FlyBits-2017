#define NETWORKID     0
#define MYNODEID      2 //prohodit
#define TONODEID      1 //prohodit


void setup()
{
  Serial.begin(9600);
  Serial.print("Vysilac ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" pripraven");
}

void loop()
{
  String teplota = "Teplota: " + String(random(-6.2,-7)) + " C;";
  String tlak = " Tlak: " + String(random(1020, 1030)) + " P;";
  String vyska = " Nadm. vyska: " + String(random(265,270)) + "mnm";
  String data = teplota + tlak + vyska;

  Serial.println(data);

  delay(random(250, 400));
}
