//http://IP位置/cmd?A=1&B=2

#include <ESP8266WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <ESP8266WebServer.h>  // 提供網站伺服器功能的程式庫
///////////////////////////
#define SSID   "19-1H5F"
#define PASSWORD  "2268159779"
///////////////////////////
ESP8266WebServer server(80);   // 宣告網站伺服器物件與埠號
unsigned long t1,t2;
String cmd1,cmd2;

// 定義處理首頁請求的自訂函式
void rootRouter() {
  server.send(200, "text/html",  "A = <b>" + cmd1 + "</b><br>"+"B = <b>" + cmd2 + "</b><br>");
}

void setup() {
Serial.begin(9600);  
WiFi.mode(WIFI_STA);
WiFi.begin(SSID, PASSWORD);
while (WiFi.status() != WL_CONNECTED) {delay(500);}
 Serial.println(WiFi.localIP());
  Serial.println("-----------------------------------------------------");
  server.on("/index.html", rootRouter); //處理首頁連結請求的事件
  server.on("/", rootRouter);
  server.on("/cmd", []() {
    cmd1="";
    cmd2="";
    cmd1=server.arg("A");
    cmd2=server.arg("B");
////////////////////////////////(若要加入更多筆資料，請由此下手)
    Serial.print(cmd1);
    Serial.print(",");
    Serial.println(cmd2);
////////////////////////////////(若要加入更多筆資料，請由此下手)
    Serial.flush();
    server.send(200, "text/html", "OK" );
  }); 
  server.onNotFound([](){   // 處理「找不到指定路徑」的事件
    server.send(404, "text/plain", "File NOT found!");
  });
  server.begin();
}

void loop() {

server.handleClient();  // 處理用戶連線
}
