
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "-"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "-"       //Your Firebase Database Secret goes here
#define WIFI_SSID "-"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "-"   

FirebaseData firebaseData;

FirebaseJson json;
const int buttonPin1 = D5; 
int buttonState1 = 0; 
const int buttonPin2 = D1; 
int buttonState2 = 0; 
void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  pinMode(buttonPin1, INPUT);
  pinMode(D5, OUTPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(D1, OUTPUT);
  
}

void loop()
{  
  buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
  if (buttonState1 == HIGH) {
   Firebase.setString(firebaseData,"/a","ON");
  } else {
   Firebase.setString(firebaseData,"/a","OFF");
  }
  if (buttonState2 == HIGH) {
   Firebase.setString(firebaseData,"/b","ON");
  } else {
   Firebase.setString(firebaseData,"/b","OFF");
  }
  Firebase.getString(firebaseData,"/a");
  if(firebaseData.stringData().length()>0)
  {
    Serial.println(firebaseData.stringData());
//    cmd1(firebaseData.stringData());
    Firebase.setString(firebaseData,"/a","");
  }
   Firebase.getString(firebaseData,"/b");
  if(firebaseData.stringData().length()>0)
  {
    Serial.println(firebaseData.stringData());
//    cmd2(firebaseData.stringData());
    Firebase.setString(firebaseData,"/b","");
  }
  
  firebaseData.clear();
  delay(3000);
}

//void cmd1(String a)
//{
//  if(a.equalsIgnoreCase("ON"))
//  {
//    digitalWrite(D6,LOW);
//  }
//  else if(a.equalsIgnoreCase("OFF"))
//  {
//    digitalWrite(D6,HIGH);
//  }
//}
//void cmd2(String a)
//{
//  if(a.equalsIgnoreCase("ON"))
//  {
//    digitalWrite(D7,LOW);
//  }
//  else if(a.equalsIgnoreCase("OFF"))
//  {
//    digitalWrite(D7,HIGH);
//  }
//}
