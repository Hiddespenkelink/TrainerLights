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
        #include <ESP8266WiFi.h>                              // Enable the use of wifi module. Make sure you downloaded and installed the ESP8266 library
        #include <BlynkSimpleEsp8266.h>                       
        char auth[] = "qhbu0KEVQeI611aHj0RTKW55-EWgX7yk";     // Put in the Auth Token for the project from Blynk. You should receive it in your email.
                                                              // This is the Auth Token or project for Device B. If Device A & Device B sharing same project, can use same Atuth Token
        char ssid[] = "Hidde";                  // Key in your wifi name. You can check with your smart phone for your wifi name
        char pass[] = "1234567890";                             // Key in your wifi password.
        BlynkTimer timer;                                     // Create variable for timer function in Blynk App.
        
        /* 0.1 - Bridge Widget Blynk Server */
        
        WidgetBridge bridge1(V10);                            // Assign virtual pin 10 of this device (Device A) for Bridge Widget to communicate with other Devices (Device B) and the channel is named "bridge1"
                                                              // Do not need to do Widget setting. It just let the Blynk server knows that you assign the pin for Bridge Widget. 
        
        /* 1- Values on Device B */

        int potRead=0;                                        // create variable for potRead values received from Device A
        int countTime=0;                                      // create variable for countTime values received from Device A
        int combine=0;                                        // create variable for potRead x countTime values
        unsigned long startMillisReadData;                    // start counting time for value display
        int secondsDataDisplay = 1000;                        // use to calculate time for sensor. By default every 1000 milli seconds.

void setup() 
{
       
        /*0 General*/

        Serial.begin(9600);                                   /* To assign communication with Serial Monitor*/
        Blynk.begin(auth, ssid, pass);                        /* Connecting to Blynk server */
        while (Blynk.connect() == false) {}                   // Wait until Blynk is connected
        timer.setInterval(1000L, readValue);                  // Every 1000 milli seconds (1 second), run the Void readValue set of function 
                                            
        /* 2 - Data submission to Blynk Server  */

        startMillisReadData = millis();                       /* Start counting time for data submission to Blynk Server*/
}

void loop() 
{
        /* 0- General */
        
        Blynk.run();                                                /* keep the Blynk active */
        timer.run();                                                /* keep the counter for Blynk active */
        
        /* 1 - Internal calculation in Device B  */
        
        if(millis() - startMillisReadData >= secondsDataDisplay)    /* every second, run the code*/
        {
        Serial.print("potRead : ");
        Serial.println(potRead);                                    /* Read the potentiometer in analog values (0-1024)*/
        Serial.print("countTime : ");
        Serial.println(countTime);                                  /* Read the time in seconds*/
        combine = potRead*countTime;    
        Serial.print("combine : ");
        Serial.println(combine);
        startMillisReadData = millis(); 
        }    
}

BLYNK_WRITE(V1)                                                     // Read the potentiometer values from Blynk Server
{
potRead = param.asInt();
Serial.println(potRead);
}

BLYNK_WRITE(V2)                                                     // Read the countTime values from Blynk Server
{
countTime = param.asInt();
Serial.println(countTime);
}

void readValue()                                                    // it activates every second
{
Blynk.virtualWrite(V3,combine);                                     // Re-post the Combined Values up to the Blynk App
}
