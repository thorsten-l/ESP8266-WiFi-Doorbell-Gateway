#ifndef __WIFI_HANDLER_H__
#define __WIFI_HANDLER_H__

#include <Arduino.h>

class WifiHandler
{
private:
  bool connected;
  char networkBuffer[1024];
  const char *scanNetworks();

public:
  void setup();
  const bool isReady();
  const bool isConnected();
  const bool isInStationMode();
  const char *getScannedNetworks();
  const bool handle(time_t timestamp);
  const char *getLocalIP();
};

extern WifiHandler wifiHandler;

#endif
