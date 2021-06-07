#include <EasyButton.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "_"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "_"       //Your Firebase Database Secret goes here
#define WIFI_SSID "_"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "_"         

// Arduino pin where the button is connected to.
#define BUTTON_PIN 0

// Instance of the button.
EasyButton button(BUTTON_PIN);

FirebaseData firebaseData;
FirebaseJson json;

// Callback function to be called when the button is pressed.
void onPressed() {
    Serial.println("Button has been pressed!");
    Firebase.setString(firebaseData,"/","ON");
    delay(5000);
}

void setup() {
    // Initialize Serial for debuging purposes.
    pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.begin(9600);
  Serial.println();
    // Initialize the button.
    button.begin();
    // Add the callback function to be called when the button is pressed.
    button.onPressed(onPressed);
    
    
}

void loop() {
    // Continuously read the status of the button. 
    button.read();
    bool was_released = button.wasReleased();
    if(was_released==true){
    Serial.println("Button has been released!");
    Firebase.setString(firebaseData,"/","OFF");
    delay(5000);
    }
    if(firebaseData.stringData().length()>0)
    {
    Serial.println(firebaseData.stringData());
    cmd(firebaseData.stringData());
    Firebase.setString(firebaseData,"/","");
    }
   firebaseData.clear();
   delay(1000);
}

void cmd(String a)
{
  if(a.equalsIgnoreCase("ON"))
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
  else if(a.equalsIgnoreCase("OFF"))
  {
    digitalWrite(LED_BUILTIN,HIGH);
  }
}
