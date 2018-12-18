#include <App.hpp>
#include <ArduinoOTA.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Syslog.hpp"

// #define END_PACKET_DELAY 75

Syslog syslog;
WiFiClient client;

void Syslog::send(const char *buffer)
{
  if (appcfg.syslog_enabled)
  {
    if (client.connect(appcfg.syslog_host, appcfg.syslog_port))
    {
      client.print(strlen(buffer));
      client.print(" ");
      client.print(buffer);
      client.flush();
      client.stop();
    }
    else
    {
      LOG0("Connection <0> to Syslog server failed.");
    }
  }
}

void Syslog::logInfo(const char *message)
{
  if (appcfg.syslog_enabled)
  {
    LOG1("loginfo: %s\n", message);

    char buffer[256];
    sprintf(buffer, "<134>1 - %s %s - - - %s", appcfg.ota_hostname,
            appcfg.syslog_app_name, message);
    send(buffer);

    /*
    WiFiUDP client;
    //char buffer[512];
    client.beginPacket(appcfg.syslog_host, appcfg.syslog_port);
    client.printf("<134>1 - %s %s - - - \xEF\xBB\xBF%s\r\n",
    appcfg.ota_hostname, appcfg.syslog_app_name, message);
    // sprintf(buffer, "<134>1 - %s %s - - - \xEF\xBB\xBF%s\r\n",
    appcfg.ota_hostname, appcfg.syslog_app_name, message);
    // client.write(buffer, strlen(buffer));
    client.endPacket();
    // delay(END_PACKET_DELAY);
  */
  }
}

void Syslog::logInfo(const char *message, int value)
{
  if (appcfg.syslog_enabled)
  {
    char buffer[256];
    sprintf(buffer, "<134>1 - %s %s - - - %s %d", appcfg.ota_hostname,
            appcfg.syslog_app_name, message, value);
    send(buffer);

    /*
    // WiFiClient client;
    if (client.connect(appcfg.syslog_host, appcfg.syslog_port))
    {
      char buffer[256];
      sprintf(buffer, "<134>1 - %s %s - - - %s %d", appcfg.ota_hostname,
              appcfg.syslog_app_name, message, value);
      client.printf("%d %s\r\n", strlen(buffer), buffer);
      client.flush();
      client.stop();
    }
    else
    {
      LOG0("Connection <1> to Syslog server failed.");
    }
  */

    /*
    WiFiUDP client;
    client.beginPacket(appcfg.syslog_host, appcfg.syslog_port);
    client.printf("<134>1 - %s %s - - - \xEF\xBB\xBF%s %d",
    appcfg.ota_hostname, appcfg.syslog_app_name, message, value);
    client.endPacket(); delay(END_PACKET_DELAY);
  */
  }
}

void Syslog::logInfo(const char *message, const char *value)
{
  if (appcfg.syslog_enabled)
  {
    char buffer[256];
    sprintf(buffer, "<134>1 - %s %s - - - %s %s", appcfg.ota_hostname,
            appcfg.syslog_app_name, message, value);
    send(buffer);
  }
}
