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
 
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SD.h>
#include <ESP8266WiFi.h>
#include <HttpClient.h>


//#define CS_PIN  D8 
const char* ssid = "Fam Lopez";
const char* password = "testtest";
String page = "";
String header;


int LEDPin = 0;
int LEDPin1 = 1;
int LEDPin2 = 2;
int LEDPin3 = 3;
int LEDPin4 = 4;
 
ESP8266WebServer server(80); 

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;



IPAddress staticIP(192,168,1,22);
IPAddress gateway(192,168,1,254);
IPAddress subnet(255,255,255,0);

// Access point Ip Address……

IPAddress local_IP(192,168,4,35);
IPAddress gateway2(192,168,4,9);
IPAddress subnet2(255,255,255,0);

void setup(void)

{

   pinMode(LEDPin1, OUTPUT);
   pinMode(LEDPin2, OUTPUT);
   pinMode(LEDPin3, OUTPUT);
   pinMode(LEDPin4, OUTPUT);
   
 
  /*
   
  if (!SD.begin(CS_PIN)) {
    Serial.println("Falla SD.");
    return;
  }
   
  Serial.println("SD OK.");
 
*/
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

/*
              /////Soft AP
              Serial.printf("Connecting to %s\n", ssid);      
              WiFi.begin(ssid, password);
              WiFi.config(staticIP, gateway, subnet);
              
              while (WiFi.status() != WL_CONNECTED){
              delay(500);
              Serial.print(".");
              }
              
              Serial.println();
              Serial.print("Connected, IP address — Client Ip: ");
              Serial.println(WiFi.localIP());
              Serial.println();
              Serial.print("Setting soft-AP configuration … ");
              Serial.println(WiFi.softAPConfig(local_IP, gateway2, subnet2) ? "Ready" : "Failed!");
              Serial.print("Setting soft-AP … ");
              Serial.println(WiFi.softAP("Principal") ? "Ready" : "Failed!");
              Serial.print("Soft-AP IP address = ");
              Serial.println(WiFi.softAPIP());
          */


        
   
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p><a href=\"Send\"><button>Send</button></a>";

   
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
    File dataFile = SD.open("LOG.txt", FILE_WRITE);
      if (dataFile) {
    Serial.println("SD OPEN OK.");
      dataFile.print(currentTime);
      dataFile.println(" * ");
      dataFile.close();
  }
  
  else {
    Serial.println("No se encuentra LOG.txt");
  }
 
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");

  
        
}// end of setup
void loop() {

String url = "http://reddesensores2019.000webhostapp.com/postdemo.php?station=8888&status=9999";

HTTPClient http2;
   WiFiClient client;
 
   if (http2.begin(client, url)) //Iniciar conexión
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http2.GET();  // Realizar petición
 
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http2.getString();   // Obtener respuesta
            Serial.println(payload);   // Mostrar respuesta por serial
         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode).c_str());
      }
 
      http2.end();
   }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
   }
 


///////////////////////////////////////
 
 
delay(30000);    //Send a request every 30 seconds
 

   digitalWrite(LEDPin1, LOW);
   digitalWrite(LEDPin2, LOW);
   digitalWrite(LEDPin3, LOW);
   digitalWrite(LEDPin4, LOW);




   
    server.handleClient();

/*

WiFiClient client = server.available();
  if (!client) {return;}

  String request = client.readStringUntil('\r');
  Serial.println("********************************");
  Serial.println("From the station: " + request);
  client.flush();
  Serial.print("Byte sent to the station: ");
  Serial.println(client.println(request + "ca" + "\r"));
*/

 

 HTTPClient http;   
 Serial.println("inicio 1"); 
  String ADCData, station, postData;
  int adcvalue=analogRead(A0);  //Read Analog value of LDR
  ADCData = String(adcvalue);   //String to interger conversion
  station = "A";
  Serial.println("inicio 2"); 
  //Post Data
  postData = "status=" + ADCData + "&station=" + station ;
 
    
    /*
     * http.begin("http://reddesensores2019.000webhostapp.com/postdemo.php"); //local
    http.POST("Content-Type: application/x-www-form-urlencoded");
    http.POST("POST /postdemo.php HTTP/1.1");
    http.POST("Host: http://reddesensores2019.000webhostapp.com/");
    http.POST("Content-Length: 7");
    http.POST("");
      String payload = http.getString();
    int httpCode = http.POST(postData);
      Serial.println("postData: "+postData);
  Serial.println("payload: "+payload);
  Serial.println("inicio 5"); 
  Serial.println("codigo de error");
  Serial.println(httpCode);   //Print HTTP return code
    http.end();
   Serial.println("inicio 7"); 
  delay(5000);   
*/










    
    }
