char caracter;

#define push7 7   // PushButton 7.
#define push8 8   // PushButton 8.
String status_push7;
String status_push8;
String status;


void setup() { 
  Serial.begin(9600);
  pinMode(push7, INPUT);
  pinMode(push8, INPUT);
}

void loop() { 
  delay(50);
 
  if(Serial.available()) {
  caracter = Serial.read();
  if (digitalRead(push7) == HIGH) {status_push7 = "Push7 ON";} else {status_push7 = "Push7 OFF";}
  if (digitalRead(push8) == HIGH) {status_push8 = "Push8 ON";} else {status_push8 = "Push8 OFF";}
  status = status_push7 + "," + status_push8;

    if(caracter == '7'){Serial.println(status_push7);}
    if(caracter == '8'){Serial.println(status_push8);} 
    if(caracter == 'D'){Serial.println(status);} 
  } 
} 
