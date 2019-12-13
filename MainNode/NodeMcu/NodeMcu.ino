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
int a = 1;

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
   
   //comprobacion de targeta SD

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


        
   
  //HTML  que se muestra en la pagina web
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p><a href=\"Send\"><button>Send</button></a>";

   

   //casos en que abre el servidor web, peticiones
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

    //boton de Send, se desactiva el soft AP
    Serial.println("Se apaga softap, listo para enviar");
    a=0;
    softap(a);
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
  //Se inicia el servidor web
  
        
}// end of setup


void loop() {
//url de la peticion get
String url = "http://reddesensores2019.000webhostapp.com/postdemo.php?station=";

HTTPClient http2;
// inicializacion de la instancia http
   WiFiClient client;
 
   if (http2.begin(client, url+random(20)+"000&status="+random(20))) //Iniciar conexión
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http2.GET();  // Realizar petición
 
      if (httpCode > 0) {
        //se muestra el codigo de respuesta http en caso satifactorio
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http2.getString();   // Obtener respuesta
            Serial.println(payload);   // Mostrar respuesta por serial
            Serial.println("se enciende ap");
            a=1;
            softap(a);
         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode).c_str());
         //codigo de error HTML
      }
 
      http2.end();
   }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
   }
 

 
delay(30000);    //Send a request every 30 seconds
 

 //leds para codigo de errores

   digitalWrite(LEDPin1, LOW);
   digitalWrite(LEDPin2, LOW);
   digitalWrite(LEDPin3, LOW);
   digitalWrite(LEDPin4, LOW);




   
    server.handleClient();
 
   
  
  delay(5000);
    }

//metodo para la configuraciondel soft ap
    void softap(int a){

               

              // Se inicializa la conexion de red
              Serial.printf("Connecting to %s\n", ssid);      
              WiFi.begin(ssid, password);
              WiFi.config(staticIP, gateway, subnet);
              
              while (WiFi.status() != WL_CONNECTED){
              delay(500);
              Serial.print(".");
              }
              // se muestra la configuracion de la red
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
              
              if(a==0){
                // si se pide dar de baja el ap se forza a apagar el modo
             WiFi.forceSleepBegin();      
                }
              
          
    }

    
    
