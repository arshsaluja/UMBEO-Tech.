
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "-"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "-"       //Your Firebase Database Secret goes here
#define WIFI_SSID "-"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "-"   

FirebaseData firebaseData;

FirebaseJson json;
const int buttonPin = D5; 
int buttonState = 0; 
void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  pinMode(buttonPin, INPUT);
  pinMode(D1, OUTPUT);
  
}

void loop()
{  
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
   Firebase.setString(firebaseData,"/","ON");
  } else {
   Firebase.setString(firebaseData,"/","OFF");
  }
  Firebase.getString(firebaseData,"/");
  if(firebaseData.stringData().length()>0)
  {
    Serial.println(firebaseData.stringData());
    cmd(firebaseData.stringData());
    Firebase.setString(firebaseData,"/","");
  }
  
  firebaseData.clear();
  delay(3000);
}

void cmd(String a)
{
  if(a.equalsIgnoreCase("ON"))
  {
    digitalWrite(D1,LOW);
  }
  else if(a.equalsIgnoreCase("OFF"))
  {
    digitalWrite(D1,HIGH);
  }
}
