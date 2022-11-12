#include <ESP8266WiFi.h>

#include <WebSocketsClient.h>

//#include <Hash.h>


WebSocketsClient webSocket;

const char* ssid     = "ESPsoftAP_01";
const char* password = "pass-to-soft-AP";
const char* host = "192.168.4.1";
const uint16_t port = 80;

volatile int interruptCounter; 
unsigned long previousmills;
#define tachInputPIN  D2
#define calculationPeriod 1000 

void ICACHE_RAM_ATTR handleInterrupt() { 
  interruptCounter++;
}
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
         Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      Serial.printf("[WSc] Connected to url: %s\n", payload);

      // send message to server when Connected
      webSocket.sendTXT("Connected");
    
    }
      break;
    case WStype_TEXT:
       Serial.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
        case WStype_PING:
            // pong will be send automatically
          Serial.printf("[WSc] get ping\n");
            break;
        case WStype_PONG:
            // answer to a ping we send
         Serial.printf("[WSc] get pong\n");
            break;
    }

}

void setup()
{
Serial.begin(115200);

  // We start by connecting to a WiFi network
WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 WiFi.begin(ssid, password);

 webSocket.begin("192.168.4.1", 81, "/");

 // event handler
  webSocket.onEvent(webSocketEvent);
webSocket.setReconnectInterval(5000);
 previousmills = 0;
  interruptCounter = 0;
  

 
 while(WiFi.status() != WL_CONNECTED) {
  
   delay(500);
    Serial.println(".");
  }
   Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  pinMode(tachInputPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(tachInputPIN), handleInterrupt, FALLING);
 
}

void loop()
{
    String rpmstring = "";     // empty string
    float rpm;
  if ((millis() - previousmills) > calculationPeriod) { // Process counters once every second
    previousmills = millis();
  float count = interruptCounter;
    interruptCounter = 0;
   rpm=count/31;
     rpmstring.concat(rpm);
    Serial.println(rpmstring);
    webSocket.sendTXT(rpmstring);
    }
 webSocket.loop();

  }
