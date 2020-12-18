/* 0- Blynk Server and Wifi Connection */

#define BLYNK_PRINT Serial                            // to write data to the blynk server. Make sure you download and installed the Blynk library
#define echoPin D2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin D1 //attach pin D3 Arduino to pin Trig of HC-SR04

#include <ESP8266WiFi.h>                              // Enable the use of wifi module. Make sure you downloaded and installed the ESP8266 library
#include <BlynkSimpleEsp8266.h>
char auth[] = "pS6yoAOJtTu63e3ZPB_kTbZcNSO0d6sC";     // Put in the Auth Token for the project from Blynk. You should receive it in your email.

// This Auth Token is for project A for Device A. If 2 devices using same project, then Auth Token can be same with Device B.
char ssid[] = "Hidde";                  // Key in your wifi name. You can check with your smart phone for your wifi name
char pass[] = "1234567890";                             // Key in your wifi password.
BlynkTimer timer;                                     // Create variable for Timer function in Blynk App.

/* 0.1 - Bridge Widget Blynk Server */

WidgetBridge bridge1(V11);                            // Assign virtual pin 10 of this device (Device A) for Bridge Widget to communicate with other Devices (Device B) and the channel is named "bridge1"
WidgetBridge bridge2(V12);                            // Assign virtual pin 10 of this device (Device A) for Bridge Widget to communicate with other Devices (Device B) and the channel is named "bridge1"
WidgetBridge bridge3(V13);                            // Assign virtual pin 10 of this device (Device A) for Bridge Widget to communicate with other Devices (Device B) and the channel is named "bridge1"
// Do not need to do Widget setting. It just let the Blynk server knows that you assign the pin for Bridge Widget.
/* 1- Values on Device A */
int lampState[4] = {0, 0, 0, 0};
int lampState1;                                          // use Potentiometer as sensor
int lampState2;                                          // use Potentiometer as sensor
int lampState3;                                          // use Potentiometer as sensor
int lampState4;                                          // use Potentiometer as sensor
int selectionLamp;
int selectionMade = 0;

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
double timeSet;
double reactieTijd;
double bufferTijd;


double gemReactietijd;

double rt = 0 ;

int countTime = 0;                                    // use formula as data
unsigned long startMillisReadData;                    // start counting time for value display
int secondsDataDisplay = 1000;                        // use to calculate time for sensor. By default every 1000 milli seconds.

//

int raakState[8];

BLYNK_CONNECTED()
{
  bridge1.setAuthToken("qhbu0KEVQeI611aHj0RTKW55-EWgX7yk");  // Place Device B AuthToken here so that can access permission to write the values to Device B
  bridge2.setAuthToken("DBO3UcGnFjdiIiH2pjtb0nQa2FXI8xFI");  // Place Device C AuthToken here so that can access permission to write the values to Device B
  bridge3.setAuthToken("pwSYUIQdVySoCVd5eJrFQMgr6iaUQdBZ");  // Place Device D AuthToken here so that can access permission to write the values to Device B
}

void setup_init() {
  /*0 General*/
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(D6, OUTPUT);
  Serial.begin(9600);                                   /* To assign communication port to communicate with meter. with 2 stop bits (refer to manual)*/
  Blynk.begin(auth, ssid, pass);                        /* Connecting to Blynk server */
  while (Blynk.connect() == false) {}                   // Wait until Blynk is connected
  timer.setInterval(500L, readValue);                  // Every 1000 milli seconds (1 second), run the Void readValue set of function

  /* 2 - Data submission to Blynk Server  */
  startMillisReadData = millis();                       /* Start counting time for data submission to Blynk Server*/

  for (int i = 0; i < 8; i++) {
    raakState[i] = 0;
  }
}

void main_loop() {
  Blynk.run();                                                            /* keep the Blynk active */
  timer.run();                                                            /* keep the counter for Blynk active */

  if (selectionMade == 0) {
    selectionLamp = rand() % 4;
    selectionMade = 1;
    Serial.print("dit is: "); Serial.println(selectionLamp);

  }

  if (raakState[selectionLamp] == 0) {                                  //niet aangeraakt dan lamp aan, anders lamp uit en nieuwe selectie
    lampState[selectionLamp] = 1;
  } else {
    lampState[selectionLamp] = 0;
    raakState[selectionLamp] = 0;
    selectionMade = 0;
    
  }

  if (lampState[0] == 1) {
    digitalWrite(D6, HIGH);
    if (timeSet == 0) {
      bufferTijd = millis();
      timeSet = 1;
    }
  } else {
    digitalWrite(D6, LOW);
    timeSet = 0;
  }

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  Serial.println(distance);

  if (distance < 10 && selectionLamp == 0) {
    raakState[0] = 1;
    digitalWrite(D6, LOW);
    if (timeSet == 1) {
      reactieTijd = (millis() - bufferTijd) / 1000;
    }
  }
  gemReactietijd = (gemReactietijd + rt) / 2;
}

void setup()
{
  setup_init();
}

void loop()
{
  main_loop();
}

BLYNK_WRITE(V1)                                                     // Read the potentiometer values from Blynk Server
{
  raakState[1] = param.asInt();
}

BLYNK_WRITE(V2)                                                     // Read the potentiometer values from Blynk Server
{
  raakState[2] = param.asInt();
}

BLYNK_WRITE(V3)                                                     // Read the potentiometer values from Blynk Server
{
  raakState[3] = param.asInt();
}

BLYNK_WRITE(V91)                                                     // Read the potentiometer values from Blynk Server
{
  rt = param.asDouble();
}

BLYNK_WRITE(V92)                                                     // Read the potentiometer values from Blynk Server
{
  rt = param.asDouble();
}

BLYNK_WRITE(V93)                                                     // Read the potentiometer values from Blynk Server
{
  rt = param.asDouble();
}

void readValue()                                                                /* it activates every second*/
{
  Blynk.virtualWrite(V120, gemReactietijd);                                      // send potRead to Device B (project B) web interface
  bridge1.virtualWrite(V1, lampState[1]);                                      // send potRead to Device B (project B) web interface
  bridge2.virtualWrite(V1, lampState[2]);                                      // send potRead to Device C (project C) web interface
  bridge3.virtualWrite(V1, lampState[3]);                                      // send potRead to Device D (project D) web interface

}
