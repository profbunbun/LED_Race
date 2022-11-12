// libraries used in this project
#include <FastLED.h> // library for led functions
#include <ESP8266WiFi.h> //library for the nodemcu esp8266
#include <WebSocketsServer.h> //networking library

float rpm = 0.0; //rpm variable

// network ports
WiFiServer server(80); 
WebSocketsServer webSocket(81);

//constants
#define NUM_LEDS 100
#define BRIGHTNESS  5
#define DATA_PIN D5

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];

// led strips and topper relay control
const int ledPin =  D4;
const int ledPin2 =  D1;
const int relayPin =  D7;

// led blink variables
long interval ;
int ledState = LOW;
int count = 0;
int led = 0;
unsigned long previousMillis = 0;
// topper state....false= off, tre= on 
bool topper= false;
int relaystate = 1;
int ledmap = 0.0;





void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    case WStype_TEXT:                     // if new text data is received

      String str = (char*)payload;
      rpm = str.toFloat();
      ledmap = map(rpm, 0, 150, 0, 40);

      break;
  }
}


void setup() {
  //just for debugging
  Serial.begin(115200);  
  delay(1000);
  Serial.println();

//led strip setup
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, ledPin2, RGB>(leds2, NUM_LEDS);
  //FastLED.setBrightness(75);
  Serial.print("Setting soft-AP ... ");
  pinMode(ledPin, OUTPUT);
 pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relaystate);

// setup accespoint node
  boolean result = WiFi.softAP("ESPsoftAP_01", "pass-to-soft-AP");
  if (result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }


  //server.on("/", handleRoot);

  startWebSocket();
  server.begin();






}



// actual program loop

void loop() {
  //ge time for blink math
  unsigned long currentMillis = millis();

//listen for bikes and rpm data
  webSocket.loop();

  // Serial.println(rpm);
  // Serial.println(ledmap);
  
  //multi stage speeds
  
  // speed of blinking light_1

  if (ledmap >= 0 && ledmap <= 5) {
    interval = 1000;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED and turn on or off accordingly
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
        leds[led] = CRGB::Red;
        FastLED.show();   
      } else {
        ledState = LOW;
        leds[led] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }

// speed of blinking light_2
   if (ledmap > 5 && ledmap <= 10) {
    interval = 1000/2;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
        leds[led] = CRGB::Red;
         leds[led - 1] = CRGB::Red;
        FastLED.show();
        count ++;
      } else {
        ledState = LOW;
       leds[led] = CRGB::Black;
        leds[led - 1] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }
  // speed of blinking light_3
   if (ledmap > 10 && ledmap <= 15) {
    interval = 1000/2;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
        leds[led] = CRGB::Red;
         leds[led - 1] = CRGB::Red;
        FastLED.show();
        count ++;
      } else {
        ledState = LOW;
        leds[led] = CRGB::Black;
        leds[led - 1] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }
  // speed of blinking light_4
   if (ledmap > 15 && ledmap <= 20) {
    interval = 1000/4;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
       leds[led] = CRGB::Red;
         leds[led - 1] = CRGB::Red;
        FastLED.show();
        count ++;
      } else {
        ledState = LOW;
        leds[led] = CRGB::Black;
        leds[led - 1] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }
  // speed of blinking light_5
   if (ledmap > 20 && ledmap <= 25) {
    interval = 1000/8;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
        leds[led] = CRGB::Red;
         leds[led - 1] = CRGB::Red;
        FastLED.show();
        count ++;
      } else {
        ledState = LOW;
        leds[led] = CRGB::Black;
        leds[led - 1] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }
  // speed of blinking light_6
   if (ledmap > 25 && ledmap <= 30) {
    interval = 1000/10;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
        leds[led] = CRGB::Red;
         leds[led - 1] = CRGB::Red;
        FastLED.show();
        count ++;
      } else {
        ledState = LOW;
        leds[led] = CRGB::Black;
        leds[led - 1] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }
  // speed of blinking light_7
   if (ledmap >30 && ledmap <= 35) {
    interval = 1000/15;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
       leds[led] = CRGB::Red;
         leds[led - 1] = CRGB::Red;
        FastLED.show();
        count ++;
      } else {
        ledState = LOW;
       leds[led] = CRGB::Black;
        leds[led - 1] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }
  // speed of blinking light_8
   if (ledmap > 35 && ledmap <= 40) {
    interval = 1000/20;
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
       leds[led] = CRGB::Red;
         leds[led - 1] = CRGB::Red;
        FastLED.show();
        count ++;
      } else {
        ledState = LOW;
        leds[led] = CRGB::Black;
        leds[led - 1] = CRGB::Black;
        FastLED.show();
      }
    }
    digitalWrite(ledPin, ledState);
  }


//increment 2 leds at a time
  if (count >= 2 ) {
    led += 2;
    count = 0;
  }
// when led hits last one, trigger topper
  if (led >= 99 ) {
    led = 0;
    count = 0;
  relaystate=0;
  }
 digitalWrite(relayPin, relaystate);
}
