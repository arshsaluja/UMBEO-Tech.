#include <EasyButton.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "_"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "_"       //Your Firebase Database Secret goes here
#define WIFI_SSID "_"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "_"                                      //Password of your wifi network 
#define BUTTON_PIN 0

EasyButton button(BUTTON_PIN);
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
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  button.begin();
  button.onPressed(onPressed);
}

void loop()
{
   button.read();
   bool was_released = button.wasReleased();
   if(was_released==true){
   Serial.println("Button has been released!");
   Firebase.setString(firebaseData,"/button","OFF"); 
   delay(3000);}
    
  Firebase.getString(firebaseData,"/relay");
  if(firebaseData.stringData().length()>0)
  {
    Serial.println(firebaseData.stringData());
    cmd(firebaseData.stringData());
    Firebase.setString(firebaseData,"/relay","");
  }
  Firebase.getString(firebaseData,"/button");
   if(firebaseData.stringData().length()>0)
  {
    Serial.println(firebaseData.stringData());
    cmd2(firebaseData.stringData());
    Firebase.setString(firebaseData,"/button","");
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
void cmd2(String a)
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
void onPressed() {
    Serial.println("Button has been pressed!");
    Firebase.setString(firebaseData,"/button","ON");
    delay(3000);
}
