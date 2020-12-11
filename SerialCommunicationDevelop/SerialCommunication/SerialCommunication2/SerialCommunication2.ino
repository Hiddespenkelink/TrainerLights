uint8_t lampData;

struct ls {
  uint8_t lampnummer;
  uint8_t state;
} lamp[4];

uint8_t lampnummerBuffer;
uint8_t stateBuffer;
int readed = 0;
uint8_t databuffer;


void setup() {
  Serial.begin(115200);
  pinMode(D6, OUTPUT);

}

void loop() {
  if (Serial.available() > 0) {
    databuffer = Serial.readBytes();
  }
  
  delay(1000);
}
