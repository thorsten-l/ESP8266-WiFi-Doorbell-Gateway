#include <Arduino.h>
#include <App.hpp>
#include <WifiHandler.hpp>
#include <ESP8266HTTPClient.h>
#include "OpenHabHandler.hpp"

OpenHabHandler openHabHandler;

void OpenHabHandler::sendValueV1(const char *value)
{
  LOG1("OpenHabHandler::sendValueV1 : %s\n", value);

  HTTPClient http;
  char urlBuffer[256];

  sprintf(urlBuffer, "http://%s:%d/CMD?%s=%s", appcfg.ohab_host,
          appcfg.ohab_port, appcfg.ohab_itemname, value);

  LOG1("URL=%s\n", urlBuffer);

  http.begin(urlBuffer);
  if (appcfg.ohab_useauth)
  {
    http.setAuthorization(appcfg.ohab_user, appcfg.ohab_password);
  }

  int httpCode = http.GET();

  if (httpCode > 0)
  {
    LOG1("[HTTP] GET... code: %d\n", httpCode);

    if (httpCode == HTTP_CODE_OK)
    {
      http.getString();
    }
  }
  else
  {
    LOG1("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void OpenHabHandler::sendValueV2(const char *value)
{
  LOG1("OpenHabHandler::sendValueV2 : %s\n", value);

  HTTPClient http;
  char urlBuffer[256];

  sprintf(urlBuffer, "http://%s:%d/rest/items/%s", appcfg.ohab_host,
          appcfg.ohab_port, appcfg.ohab_itemname);

  LOG1("URL=%s\n", urlBuffer);

  http.begin(urlBuffer);
  http.addHeader("Cache-Control", "no-cache");
  http.addHeader("Accept", "application/json");
  http.addHeader("Content-Type", "text/plain");

  if (appcfg.ohab_useauth)
  {
    http.setAuthorization(appcfg.ohab_user, appcfg.ohab_password);
  }

  int httpCode = http.POST(value);

  if (httpCode > 0)
  {
    LOG1("[HTTP] POST... code: %d\n", httpCode);

    if (httpCode == HTTP_CODE_OK)
    {
      http.getString();
    }
  }
  else
  {
    LOG1("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void OpenHabHandler::sendValue(const char *value)
{
  if (appcfg.ohab_enabled && wifiHandler.isReady())
  {
    if (appcfg.ohab_version == 1)
    {
      sendValueV1(value);
    }
    else
    {
      sendValueV2(value);
    }
  }
}
