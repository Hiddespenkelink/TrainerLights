


String d;
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
d = String(Serial.read());
if (d == "TRUE"){
  digitalWrite(D6, LOW);
} else if (d == "FALSE"){
  digitalWrite(D6, HIGH);
}

}
}
