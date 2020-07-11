/*Arduino Code for Face Tracking Arduino
 * Coded by Circuitdigest.com
 * On 25-05-2017
 */

 /*CONNECTION DETIALS
  * Arduino D11 -> RX of BT Module
  * Arduino D12 -> Tx of BT
  * Servo1 -> pin 3 of arduino Nano to pan
  * Servo2 -> pin 5 of arduino Nano to tilt
  */

#include <Servo.h> //header to drive servo motors
#include <SoftwareSerial.h>// import the serial library
SoftwareSerial cam_BT(4, 5);  // RX, TX
int ledpin=2; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

//lets declare the servo objects
Servo servo1;  
Servo servo2;

long gmotor,gnum1,gnum2;
int pos;
int flag=0; 
int pos1 = 40;
int pos2 = 90;

void setup() {
   servo1.attach(14);
   servo2.attach(0);;

   //**Initial position of all four servo motors**//
   servo1.write(pos1);
   Serial.println("yes");
   servo2.write(pos2);
   //**initialised**//
   
cam_BT.begin(9600); //start the Bluetooth communication at 9600 baudrate
cam_BT.println("Ready to take commands");

Serial.begin(57600); 
Serial.println("Face tracking programming by CircuitDigest.com");
}

//***Function for each Servo actions**//
void call(int motor, int num1, int num2) // The values like Motor number , from angle and to angle are received 
{
Serial.println("Passing values...");
flag =0;
switch (motor) 
  {  
    case 1:            // For motor one
    { 
    Serial.println("Executing motor one");
    if(num1<num2) // Clock wise rotation
    { 
        for ( pos =num1; pos<=num2; pos+=1)
            {
            servo1.write(pos);
            delay( 20);
            }
    }
    
    if(num1>num2) // Anti-Clock wise rotation
    {
        for ( pos =num1; pos>=num2; pos-=1)
        {
        servo1.write(pos);
        delay( 20);
        }
    }
     break;
    }     

       ////////JUST  DUPLICATE FOR OTHER SERVOS////

       
    case 2:    // For motor 2
    {
    Serial.println("Executing motor two");
    if(num1<num2)
    {
        for ( pos =num1; pos<=num2; pos+=1)
        {
        servo2.write(pos);
        delay( 20);
        }
    }
    if(num1>num2)
    {
        for ( pos =num1; pos>=num2; pos-=1)
        {
        servo2.write(pos);
        delay( 20);
        }
    }
    break;
    }     
  }
}

void loop() {
 if(Serial.available()>0) //Read whats coming in through Serial
  {
  gmotor= Serial.parseInt(); 
  Serial.print(" selected Number-> ");  
  Serial.print(gmotor);
  Serial.print(" , ");    
  gnum1= Serial.parseInt();   
  Serial.print(gnum1);  
  Serial.print(" degree , ");
  gnum2= Serial.parseInt();   
  Serial.print(gnum2);  
  Serial.println(" degree ");
  flag=1;
  }
   
 if (cam_BT.available()) //Read whats coming in through Bluetooth
 {
  BluetoothData=cam_BT.read();
  Serial.print("Incoming from BT:");
  Serial.println(BluetoothData);
 }

 if (flag ==1)
 call(gmotor,gnum1,gnum2); //call the respective motor for action

 if (BluetoothData==49) //Turn Left
 {pos1+=2; servo1.write(pos1);}

 if (BluetoothData==50) //Turn Right
 {pos1-=2; servo1.write(pos1);}

 if (BluetoothData==51) //Turn Up
 {pos2-=2; servo2.write(pos2);}

 if (BluetoothData==52) //Turn Down
 {pos2+=2; servo2.write(pos2);}

 flag=0;
 BluetoothData=0;
}
