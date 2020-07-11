
#define BLYNK_PRINT Serial
long duration;
int distance;

#include <SPI.h>
#include<ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int trigPin = 12;
const int echoPin = 13;

char auth[] = "2d4e551e04ab4222ab807fefb24cace2";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo 1609";
char pass[] = "rd123456";

BlynkTimer timer;

int thresh[3] = {25, 50, 75};


WidgetLED green(V1);
WidgetLED orange(V2);
WidgetLED red(V3);



void setup()
{
  // Debug console
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
}

void loop()
{
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
  
  
  Blynk.run();

  if(distance<thresh[0]){
    green.on();
    }
  else if(distance<thresh[1]){
    green.on();
    orange.on();
  }
  else if(distance<thresh[2])
    {green.on();
    orange.on();
    red.on();
  }
  else{
    green.off();
    orange.off();
    red.off();
  delay(100);
}
}
