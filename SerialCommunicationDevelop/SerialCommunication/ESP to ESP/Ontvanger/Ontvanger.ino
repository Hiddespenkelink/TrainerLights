
int d;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  pinMode(D6, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}




void loop() { // run over and over
  if (Serial.available()) {
    Serial.write(Serial.read());
    d = Serial.read();
    if (d == 0) {
      digitalWrite(D6, LOW);
    } else if (d == 1) {
      digitalWrite(D6, HIGH);
    }
  }

}
