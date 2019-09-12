#include <SoftwareSerial.h>

SoftwareSerial BT(0,1);   // 接收腳(RX), 傳送腳(TX)；接HC-06之TXD、RXD；先不要用0,1,因為USB用

int potPin = 0; 

void setup()
{
  Serial.begin(9600); //for arduino serial port mointor
  BT.begin(9600);
  Serial.print("BT is ready!");  
  pinMode(potPin, INPUT);
}

void loop()
{
    int value = analogRead(potPin);    // read the value of the Analog Input
    BT.println(value); 
    Serial.println(value);       // Print the value; can also be seen on Serial Monitor
    delay(1000);                  // Don't send too fast or the Android buffer will flood - this worked for me
}
 
