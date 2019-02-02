/*
This library brought to you by "Senses"
Powered by LogiSenses and IoTtweet
2019.Jan.30
*/

#include "pm25senses.h"

#define host "pm25senses.iottweet.com"
#define port 4000
#define libversion "v1.1"
#define sensesSecretToken "AA9319345113693D34CC6F66AC568"

#define LAG_TIME 500

bool pm25senses::begin(const char *ssid, const char *passw){
  _ssid = ssid;
  _passw = passw;

  int _cnt = 0;

  WiFi.begin(_ssid, _passw);
  Serial.println("### Welcome PM2.5 platform ###");
  Serial.println("-- Platform by SENSES --");
  Serial.println("-- Powered by LogiSenses and IoTtweet --");
  Serial.println("WiFi connecting.");

  while((WiFi.status() != WL_CONNECTED)){
    delay(200);
    Serial.print(".");
    _cnt++;
  }

  if(WiFi.status() == WL_CONNECTED){
    _conn = true;
    Serial.println("connected !");

    String _version = getVersion();
    Serial.println("---------------------------------------------");
    Serial.println("pm25senses library version > " + _version);
    Serial.println("---------------------------------------------");
    Serial.println("- Ready to send data to pm25senses platform. -");
    Serial.println();
    Serial.println("This library compatible for WiFi Chip ESP8266.");
    Serial.println("0. Set your name in String format. (No white space in name)");
    Serial.println("1. Prepare your coordinate location as 'latitude' and 'longitude' in float format. (6 digits)");
    Serial.println("2. PM2.5 and PM10 data in ug/m3 as float format");
    Serial.println("3. Call function 'reportPM25senses' and place your above data in this function");
    Serial.println("4. See community data at http://pm25senses.iottweet.com");
    Serial.println();
    Serial.println("Finished..!");
    Serial.println("-----------------------------------------------");
  }else{
    //..do something later na.
  }

  return _conn;
}

String pm25senses::checkServerReady(){

  WiFiClient client;
  if(client.connect(host, port)){
    _str = "GET /";
    _str += " HTTP/1.1\r\n";
    _str += "Host: ";
    _str += host;
    _str += ":";
    _str += port;
    _str += "\r\n";
    _str += "Connection: keep-alive\r\n\r\n";

    client.print(_str);

    delay(LAG_TIME);

    while(client.available()){
      _res = client.readStringUntil('\r');
    }

    return _res;

  }else{
    //..
  }
}

String pm25senses::reportPM25senses(String senderName, String lat, String lng, float pm25, float pm10){

    _senderName = senderName;
    _lat = String(lat);
    _lng = String(lng);
    _pm25 = String(pm25);
    _pm10 = String(pm10);

    WiFiClient client;
    if(client.connect(host, port)){

      _str = "GET /reportpm25senses/";
      _str += _senderName;
      _str += "/";
      _str += _lat;
      _str += "/";
      _str += _lng;
      _str += "/";
      _str += _pm25;
      _str += "/";
      _str += _pm10;
      _str += "/";
      _str += sensesSecretToken;
      _str += " HTTP/1.1\r\n";
      _str += "Host: ";
      _str += host;
      _str += ":";
      _str += port;
      _str += "\r\n";
      _str += "Connection: keep-alive\r\n\r\n";

      client.print(_str);

      delay(LAG_TIME);

      while(client.available()){
        _res = client.readStringUntil('\r');
      }

      return _res;
    }else{
      //Nothing..
    }
}

String pm25senses::getVersion(){
  return libversion;
}
