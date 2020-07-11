
#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int select=13;
int lm=9;
int lmr=8;
int rm=12;
int rmr=7;
int ledPin=13;//led on pin 13 is ON except when bot is stationary
#define LS 2      // left sensor
#define RS 3      // right sensor

/*-------definning Outputs------*/
#define LM1 9       // left motor
#define LM2 8       // left motor
#define RM1 12       // right motor
#define RM2 7       // right motor

void setup()
{
 Serial.begin(9600);//Initialise the serial connection debugging

 pinMode(ledPin,OUTPUT);
 pinMode(lm,OUTPUT);
 pinMode(lmr,OUTPUT);
 pinMode(rm,OUTPUT);
 pinMode(rmr,OUTPUT);
 pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

 vw_setup(2000); // Bits per sec
 vw_rx_start(); // Start the receiver
}
void loop()
{   
  if(select==0)
  {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
 //Serial.println(buflen);

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

  for (i = 0; i < buflen; i++)
  {
     // Serial.print(buf[i],HEX);//You may also use integer values debugging
      //Serial.print(' ');// debugging

          if (buf[i]==115)//Stationary
          {
            digitalWrite(lm,LOW);  
            digitalWrite(lmr,LOW);
            digitalWrite(rm,LOW);
            digitalWrite(rmr,LOW);
          
            digitalWrite(ledPin,LOW);
            Serial.print("");
          }
          else
          {
            if(buf[i]==102)//Forward
            {
              digitalWrite(lm,LOW);  
              digitalWrite(lmr,HIGH);
              digitalWrite(rm,HIGH);
              digitalWrite(rmr,LOW);
              Serial.println("forward");
              
              digitalWrite(ledPin,HIGH);
            }
          
            if (buf[i]==97)//Backward
            {
              digitalWrite(lm,HIGH);  
              digitalWrite(lmr,LOW);
              digitalWrite(rm,LOW);
              digitalWrite(rmr,HIGH);
              
              digitalWrite(ledPin,HIGH);
              Serial.println("back");
          }
          
            if (buf[i]==108)//Left 
            {
              digitalWrite(lm,LOW);  
              digitalWrite(lmr,LOW);
              digitalWrite(rm,HIGH);
              digitalWrite(rmr,LOW);
              digitalWrite(ledPin,HIGH);
              Serial.println("left");
            }
          
            if (buf[i]==114)//Right 
            {
              digitalWrite(lm,LOW);  
              digitalWrite(lmr,HIGH);
              digitalWrite(rm,LOW);
              digitalWrite(rmr,LOW);
              digitalWrite(ledPin,HIGH);
              Serial.println("right");
            }
           }   
    }
    //Serial.print("\n");// debugging
        }
        //delay(1000);
        }
        if(select==1)
        {
          if(digitalRead(LS) && digitalRead(RS))     // Move Forward
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  
  if(!(digitalRead(LS)) && digitalRead(RS))     // Turn right
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  
  if(digitalRead(LS) && !(digitalRead(RS)))     // turn left
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  
  if(!(digitalRead(LS)) && !(digitalRead(RS)))     // stop
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
        }
        

}
