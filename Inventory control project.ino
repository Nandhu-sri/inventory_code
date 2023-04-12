
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "R&D-LABS";   // your network SSID (name)
const char* password = "12345678";   // your network password

WiFiClient  client;

unsigned long myChannelNumber =  1781192;
const char * myWriteAPIKey = "5KRVJ8NQTQSEL1G4";
#define FIELD3 3
#define FIELD4 4

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 3;

// Variable to hold temperature readings
int IR1 = 13;
int IR2 = 14;
void setup() {
  Serial.begin(115200);  
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  WiFi.mode(WIFI_STA);  
 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {
   
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password);
        delay(5000);    
      }
      Serial.println("\nConnected.");
    }
  }
  int sens1=digitalRead(IR1);
  int sens2=digitalRead(IR2);
 
  int sensor1;
  int sensor2;
  if(sens1==HIGH){
    sensor1=LOW;
  }else{
   sensor1=HIGH;
   }
     if(sens2==HIGH){
    sensor2=LOW;
     }else{
   sensor2=HIGH;
   }
   {
ThingSpeak.setField(3, sensor1);
ThingSpeak.setField(4, sensor2);
ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
       
    lastTime = millis();
  }
}
