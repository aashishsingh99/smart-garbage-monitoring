#include<ESP8266WiFi.h>
#include<WIFIClient.h>
#include<ThingSpeak.h>
const char* ssid="vivo V3Max";
const char* password="26032112";
int val;
int sensor=A0;
WiFiClient Client;
unsigned long myChannelNumber=745261;
const char* myWriteAPIKey="N5AGGV9MKYCR95CJ";
void setup()
{
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid,password);
  ThingSpeak.begin(Client);
}
void loop()
{
  val=analogRead(sensor);
  Serial.print(val);
  delay(1000);
  ThingSpeak.writeField(myChannelNumber,1,val,myWriteAPIKey);
  delay(100);
}
