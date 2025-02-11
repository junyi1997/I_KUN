/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "IFTTT";
const char* password = "1234567890";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
int Step=0;
void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(2, 0);
  digitalWrite(14, 0);
  Connect_to_WiFi_network();
  
}

void loop() {
  // Check if a client has connected
  if(digitalRead(4)==1){if(Step==0){Serial.println(WiFi.localIP());Step=1;delay(10);}}
  else{if(Step==1){Step=0;}}
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1)
    // Set GPIO2 according to the request
    digitalWrite(2, 0);
  else if (req.indexOf("/gpio/1") != -1)
    // Set GPIO2 according to the request
    digitalWrite(2, 1);
  else if (req.indexOf("/gpio/2") != -1)
    // Set GPIO2 according to the request
    digitalWrite(14, 0);
  else if (req.indexOf("/gpio/3") != -1)
    // Set GPIO2 according to the request
    digitalWrite(14, 1);
      
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void Connect_to_WiFi_network(){
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}
