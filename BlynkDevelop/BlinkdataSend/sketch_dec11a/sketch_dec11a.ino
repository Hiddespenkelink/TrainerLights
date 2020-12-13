/* 0- Blynk Server and Wifi Connection */

        #define BLYNK_PRINT Serial                            // to write data to the blynk server. Make sure you download and installed the Blynk library
        #include <ESP8266WiFi.h>                              // Enable the use of wifi module. Make sure you downloaded and installed the ESP8266 library
        #include <BlynkSimpleEsp8266.h>                       
        char auth[] = "pS6yoAOJtTu63e3ZPB_kTbZcNSO0d6sC";     // Put in the Auth Token for the project from Blynk. You should receive it in your email.
        
                                                              // This Auth Token is for project A for Device A. If 2 devices using same project, then Auth Token can be same with Device B.
        char ssid[] = "Hidde";                  // Key in your wifi name. You can check with your smart phone for your wifi name
        char pass[] = "1234567890";                             // Key in your wifi password.
        BlynkTimer timer;                                     // Create variable for Timer function in Blynk App.
        
        /* 0.1 - Bridge Widget Blynk Server */

        WidgetBridge bridge1(V10);                            // Assign virtual pin 10 of this device (Device A) for Bridge Widget to communicate with other Devices (Device B) and the channel is named "bridge1"
                                                              // Do not need to do Widget setting. It just let the Blynk server knows that you assign the pin for Bridge Widget.
        /* 1- Values on Device A */

        int lampState1;                                          // use Potentiometer as sensor
        int lampState2;                                          // use Potentiometer as sensor
        int lampState3;                                          // use Potentiometer as sensor
        int lampState4;                                          // use Potentiometer as sensor


        
        int countTime=0;                                      // use formula as data
        unsigned long startMillisReadData;                    // start counting time for value display
        int secondsDataDisplay = 1000;                        // use to calculate time for sensor. By default every 1000 milli seconds.

        //

        int raakState[8];

BLYNK_CONNECTED() 
{ bridge1.setAuthToken("qhbu0KEVQeI611aHj0RTKW55-EWgX7yk"); } // Place Device B AuthToken here so that can access permission to write the values to Device B

void setup() 
{
       
        /*0 General*/

        Serial.begin(9600);                                   /* To assign communication port to communicate with meter. with 2 stop bits (refer to manual)*/
        Blynk.begin(auth, ssid, pass);                        /* Connecting to Blynk server */
        while (Blynk.connect() == false) {}                   // Wait until Blynk is connected
        timer.setInterval(500L, readValue);                  // Every 1000 milli seconds (1 second), run the Void readValue set of function  

        /* 2 - Data submission to Blynk Server  */

        startMillisReadData = millis();                       /* Start counting time for data submission to Blynk Server*/

        for (int i = 0; i < 8; i++){
          raakState[i] = 0;
        }
}

void loop() 
{
        /* 0- General */
        
        Blynk.run();                                                            /* keep the Blynk active */
        timer.run();                                                            /* keep the counter for Blynk active */

        if(raakState[1] == 0){
          lampState = 1;
        } else {
          lampState = 0;
        }
        
        /* 1 - Internal calculation in Device A  */
          
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

BLYNK_WRITE(V4)                                                     // Read the potentiometer values from Blynk Server
{
  raakState[4] = param.asInt();
}

void readValue()                                                                /* it activates every second*/
{
        bridge1.virtualWrite(V1,lampState1);                                       // send potRead to Device B (project B) web interface 
//        bridge2.virtualWrite(V1,lampState2);                                       // send potRead to Device C (project C) web interface 
//        bridge3.virtualWrite(V1,lampState3);                                       // send potRead to Device D (project D) web interface 
//        bridge4.virtualWrite(V1,lampState4);                                       // send potRead to Device E (project E) web interface 
                
}
