#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h>
#define FIREBASE_HOST "_"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "_"       //Your Firebase Database Secret goes here
#define WIFI_SSID "_"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "_"                                      //Password of your wifi network 


FirebaseData firebaseData;

FirebaseJson json;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  pinMode(D5,OUTPUT);
  digitalWrite(D5,HIGH);
}

void loop()
{
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
    digitalWrite(D5,LOW);
  }
  else if(a.equalsIgnoreCase("OFF"))
  {
    digitalWrite(D5,HIGH);
  }
}
