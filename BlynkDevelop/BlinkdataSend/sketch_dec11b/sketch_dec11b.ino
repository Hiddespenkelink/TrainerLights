// Bridge Widget Device B using Blynk App By Solarduino

// Note Summary
// Note :  Safety is very important when dealing with electricity. We take no responsibilities while you do it at your own risk.
// Note :  This Code wants to read values from Device A. This code uploaded to Device B (This device) in order to collect readings from Device A (other device).
// Note :  The values collected from Device A can be use for further calculation or analysis.
// Note :  You need to create 2 Projects (with 2 Auth tokens from Blynk). Make sure to clearly identify which Auth Token is for which Device.
// Note :  You need to download the Blynk App on your smart phone for display.
// Note :  Solarduino only amend necessary code and integrate with Blynk Server.
// Note :  Blog page for this code :

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/////////////*/


/* 0- Blynk Server and Wifi Connection */

#define BLYNK_PRINT Serial                            // to write data to the blynk server. Make sure you download and installed the Blynk library
#define echoPin D2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin D1 //attach pin D3 Arduino to pin Trig of HC-SR04


#include <ESP8266WiFi.h>                              // Enable the use of wifi module. Make sure you downloaded and installed the ESP8266 library
#include <BlynkSimpleEsp8266.h>
char auth[] = "qhbu0KEVQeI611aHj0RTKW55-EWgX7yk";     // Put in the Auth Token for the project from Blynk. You should receive it in your email.
// This is the Auth Token or project for Device B. If Device A & Device B sharing same project, can use same Atuth Token
char ssid[] = "Hidde";                  // Key in your wifi name. You can check with your smart phone for your wifi name
char pass[] = "1234567890";                             // Key in your wifi password.
BlynkTimer timer;                                     // Create variable for timer function in Blynk App.
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement



/* 0.1 - Bridge Widget Blynk Server */

WidgetBridge bridge0(V10);                            // Assign virtual pin 10 of this device (Device B) for Bridge Widget to communicate with other Devices (Device A) and the channel is named "bridge0"
// Do not need to do Widget setting. It just let the Blynk server knows that you assign the pin for Bridge Widget.

/* 1- Values on Device B */
int raakState = 0;
int lampState = 0;
int potRead = 0;                                      // create variable for potRead values received from Device A
int countTime = 0;                                    // create variable for countTime values received from Device A
unsigned long startMillisReadData;                    // start counting time for value display
int secondsDataDisplay = 1000;                        // use to calculate time for sensor. By default every 1000 milli seconds.

BLYNK_CONNECTED() 
{ bridge0.setAuthToken("pS6yoAOJtTu63e3ZPB_kTbZcNSO0d6sC"); }


void setup()
{

  /*0 General*/
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);                                   /* To assign communication with Serial Monitor*/
  Blynk.begin(auth, ssid, pass);                        /* Connecting to Blynk server */
  while (Blynk.connect() == false) {}                   // Wait until Blynk is connected
  timer.setInterval(500L, readValue);                  // Every 1000 milli seconds (1 second), run the Void readValue set of function
  pinMode(D6, OUTPUT);
  /* 2 - Data submission to Blynk Server  */

  startMillisReadData = millis();                       /* Start counting time for data submission to Blynk Server*/
}

void loop()
{
  /* 0- General */

  Blynk.run();                                                /* keep the Blynk active */
  timer.run();                                                /* keep the counter for Blynk active */
  if (lampState == 1) {
    digitalWrite(D6, HIGH);
  } else {
    digitalWrite(D6, LOW);
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

  if (distance < 10){
    raakState =1;
  }
}

BLYNK_WRITE(V1)                                                     // Read the potentiometer values from Blynk Server
{
  lampState = param.asInt();
}

void readValue()                                                    // it activates every second
{
  bridge0.virtualWrite(V1,raakState);                                       // send potRead to Device A (project A) web interface 

}
