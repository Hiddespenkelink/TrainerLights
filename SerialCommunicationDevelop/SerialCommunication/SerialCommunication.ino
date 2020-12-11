
struct ls {
  uint8_t lampnummer;
  uint8_t state;
} lamp[4];

uint8_t begindata = 10;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    lamp[i].lampnummer = (i + 1);
    lamp[i].state = 0;
  }
}

void loop() {


  //  for (int i = 0; i < 4; i++){
  //    int numBuffer = lamp[i].lampnummer;
  //    Serial.print(numBuffer);
  //
  //    delay(500);
  //  }
  if (Serial.available() > 0){
  Serial.println(begindata, 0);
  }
  delay(1000);
//  Serial.println(lamp[1].lampnummer, 0);

}
