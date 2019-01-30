#include <pm25senses.h>

const char *ssid = "your-wifi-ssid";
const char *passw = "your-wifi-password";

String sendername = "your-reporter-name";
float lat = 13.000000;
float lng = 100.000000;
float pm25=0, pm10=0;

String response; 

pm25senses mydevice;

void setup() {

  Serial.begin(9600);
  
  mydevice.begin(ssid, passw);
  response = mydevice.checkServerReady();
  Serial.println("PM25Senses response :" + String(response)); 
  
}

void loop() {

  /* Set your lat, lng, pm25, pm10 here */
  // This is Mock up data only
  lat = 13.685024;  
  lng = 100.509837;
  pm25 = 25;
  pm10 = 90;

  response = mydevice.reportPM25senses(sendername, lat, lng, pm25, pm10);
  Serial.println(response);
  
  delay(5000);
}
