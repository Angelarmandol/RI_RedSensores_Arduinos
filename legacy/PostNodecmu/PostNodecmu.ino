 
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
 
const char *ssid = "Fam Lopez";   
const char *password = "";
 
//webserver local
const char *host = "192.168.1.69";   
 
void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);            
  delay(1000);
  WiFi.mode(WIFI_STA);        
  
  WiFi.begin(ssid, password);  
  Serial.println("");
 
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}
 
 
void loop() {
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
  http.begin("http://192.168.1.69/postdemo.php");             
   Serial.println("inicio 3"); 
http.addHeader("Content-Type", "text/plain");
  Serial.println("inicio 4"); 
  int httpCode = http.POST(postData);    
  String payload = http.getString();    
   Serial.println("postData: "+postData);
  Serial.println("payload: "+payload);
  Serial.println("inicio 5"); 
  Serial.println("codigo de error");
  Serial.println(httpCode);   
  Serial.println(payload);    
  Serial.println("inicio 6"); 
  http.end();  //Close connection
  */

    
    http.begin("http://192.168.1.69/postdemo.php"); //local
    http.POST("Content-Type: application/x-www-form-urlencoded");
    http.POST("POST /postdemo.php HTTP/1.1");
    http.POST("Host: http://192.168.1.69/");
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
}
 
