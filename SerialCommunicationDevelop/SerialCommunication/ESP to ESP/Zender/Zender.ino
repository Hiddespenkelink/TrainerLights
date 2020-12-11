#include <SoftwareSerial.h>

int y;
SoftwareSerial espSerial(5, 6);
String h = "FALSE";
String str;
void setup(){
Serial.begin(115200);
espSerial.begin(115200);
delay(2000);
}
void loop()
{

str =String("coming from arduino: ")+String("H= ")+String(h);
espSerial.println(str);
delay(1000);
if (h == "FALSE"){
  y = 1;
  Serial.println(y);
} else {
  y = 0; 
  Serial.println(y);
}
}
