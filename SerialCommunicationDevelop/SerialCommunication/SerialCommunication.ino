#include <SoftwareSerial.h>

SoftwareSerial s(3, 1);

struct ls {
  uint8_t lampnummer;
  uint8_t state;
} lamp[4];

char beginbit[255] = "128";

void setup() {
  s.begin(115200);

  for (int i = 0; i < 4; i++){
    lamp[i].lampnummer = (i + 1);
    lamp[i].state = 0;
  }
}

void loop() {
  
  
  for (int i = 0; i < 4; i++){
    int numBuffer = lamp[i].lampnummer;
    s.print(numBuffer);
//    s.println(lamp[i].state);
//    s.println("---");
  delay(500);
  }
  

}
