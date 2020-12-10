#include <SoftwareSerial.h>

uint8_t lampData;

struct ls {
  uint8_t lampnummer;
  uint8_t state;
} lamp[4];

uint8_t lampnummerBuffer;
uint8_t stateBuffer;

void setup() {
  Serial.begin(115200);
  pinMode(D6, OUTPUT);

}

void loop() {
  int databuffer = Serial.read();
  Serial.println(databuffer);
  delay(500);
}
