/*
This library brought to you by "Senses"
Powered by LogiSenses and IoTtweet
2019.Jan.30
*/

#ifndef pm25senses_h
#define pm25senses_h

#include "Arduino.h"
#include "ESP8266WiFi.h"

class pm25senses{

  public:
    bool begin(const char *ssid, const char *passw);
    String checkServerReady();
    String getVersion();
    String reportPM25senses(String senderName, String lat, String lng, float pm25, float pm10);

  private:
    const char *_ssid, *_passw, *_libversion;
    String _str, _res, _senderName, _lat, _lng, _pm25, _pm10;
    bool _conn;
};

#endif
