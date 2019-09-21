int photocellPin=A3;
int photocellVal;
int LedPin=13;
char comdata;
void setup() {
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);
}

void loop() {
  photocellVal=analogRead(photocellPin);
  Serial.println(photocellVal);
  delay(500);
  if(Serial.available()>0){
    comdata=Serial.read();
    if(comdata=='o'){
      while(Serial.available()==0);
      comdata=Serial.read();
      if(comdata=='n'){
        digitalWrite(LedPin,HIGH);
      }else if(comdata=='f'){
        while(Serial.available()==0);
        comdata=Serial.read();
        if(comdata=='f'){
          digitalWrite(LedPin,LOW);
        }
      }
    }
  }
}
