#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 6);
bool y = false;
String h = "FALSE";
String str;
void setup(){
Serial.begin(115200);
espSerial.begin(115200);
delay(2000);
}
void loop()
{
Serial.println(y);
str =String("coming from arduino: ")+String("H= ")+String(h);
espSerial.println(str);
delay(1000);
if (h == "FALSE"){
  y = true;
} else {
  y = false;
}
}
