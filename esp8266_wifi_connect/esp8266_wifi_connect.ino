#include "ESP8266WiFi.h"
 
const char* ssid = "IKUN";
const char* password = "1234567890";
 
void setup(void)
{  
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  //不斷嚐試連接
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");  //已連接
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());  //顯示IP位址
  pinMode(2,OUTPUT);
}

void loop() {
  if (Serial.available()) {   //若軟體序列埠 Rx 收到資料 (來自 ESP8266)
    Serial.write(Serial.read());  //讀取後寫入硬體序列埠 Tx (PC)
  }
}
