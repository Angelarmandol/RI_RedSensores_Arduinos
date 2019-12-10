#include <Pinger.h>
#include <PingerResponse.h>

#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
 
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
const char* ssid = "Fam Lopez";
bool pingtest = false;
const char* password = "";
String page = "";
int LEDPin = 0;
int LEDPin1 = 1;
int LEDPin2 = 2;
int LEDPin3 = 3;
int LEDPin4 = 4;
 

ESP8266WebServer server(80); 

 
String header;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
// Client Ip Address……



IPAddress staticIP(192,168,1,22);

IPAddress gateway(192,168,1,254);

IPAddress subnet(255,255,255,0);

// Access point Ip Address……

IPAddress local_IP(192,168,4,35);

IPAddress gateway2(192,168,4,9);

IPAddress subnet2(255,255,255,0);

void setup(void)

{

  digitalWrite(LEDPin1, LOW);
   digitalWrite(LEDPin2, LOW);
   digitalWrite(LEDPin3, LOW);
   digitalWrite(LEDPin4, LOW);
   
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p><a href=\"Send\"><button>Send</button></a>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000); 
  });
  
   server.on("/Send", [](){
    server.send(200, "text/html", page);
    Serial.println("Guardar y enviar");
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");

  
Serial.printf("Connecting to %s\n", ssid);

WiFi.begin(ssid, password);
WiFi.config(staticIP, gateway, subnet);
while (WiFi.status() != WL_CONNECTED)

{

delay(500);

Serial.print(".");

}

Serial.println();

Serial.print("Connected, IP address — Client Ip: ");

Serial.println(WiFi.localIP());

////// Connection to the Access point……
Serial.println();

Serial.print("Setting soft-AP configuration … ");

Serial.println(WiFi.softAPConfig(local_IP, gateway2, subnet2) ? "Ready" : "Failed!");

Serial.print("Setting soft-AP … ");

Serial.println(WiFi.softAP("Principal") ? "Ready" : "Failed!");

Serial.print("Soft-AP IP address = ");

Serial.println(WiFi.softAPIP());

}
void loop() {
    server.handleClient();
   
  }
