#include "WifiHandler.hpp"
#include <App.hpp>
#include <DefaultAppConfig.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

WifiHandler wifiHandler;

static time_t lastTimestamp;

static void wifiOff()
{
  digitalWrite(WIFI_LED, HIGH);
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.setOutputPower(0.0f);
  WiFi.hostname(appcfgRD.ota_hostname);
}

static void wifiInitStationMode()
{
  WiFi.disconnect();
  ESP.eraseConfig();
  delay( 500 );

  LOG0("Starting Wifi in Station Mode");
  if (appcfgRD.net_mode == NET_MODE_STATIC)
  {
    LOG0("use static ip address");
    IPAddress host;
    host.fromString(appcfgRD.net_host);
    IPAddress gateway;
    gateway.fromString(appcfgRD.net_gateway);
    IPAddress mask;
    mask.fromString(appcfgRD.net_mask);
    IPAddress dns;
    dns.fromString(appcfgRD.net_dns);
    WiFi.config(host, gateway, mask);
    WiFi.dnsIP(dns);
  }
  else
  {
    LOG0("use dhcp server");
  }
  WiFi.begin();
  WiFi.hostname(appcfgRD.ota_hostname);
  WiFi.begin(appcfgRD.wifi_ssid, appcfgRD.wifi_password);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
}

void WifiHandler::setup()
{
  LOG0("WiFi Setup started...\n");
  connected = false;
  lastTimestamp = 0;

  wifiOff();

  scanNetworks();

  wifiOff();

  if (isInStationMode())
  {
    wifiInitStationMode();
  }
  else
  {
    LOG0("Starting Wifi Access Point Mode\n");
    char buffer[64];
    sprintf(buffer, DEFAULT_WIFI_SSID, ESP.getChipId());
    strcpy(appcfgRD.wifi_ssid, buffer);

    WiFi.mode(WIFI_AP);

    IPAddress host;
    host.fromString(appcfgRD.net_host);
    IPAddress gateway;
    gateway.fromString(appcfgRD.net_gateway);
    IPAddress mask;
    mask.fromString(appcfgRD.net_mask);
    IPAddress dns;
    dns.fromString(appcfgRD.net_dns);

    WiFi.softAPConfig(host, gateway, mask);
    WiFi.softAP(appcfgRD.wifi_ssid, appcfgRD.wifi_password);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
    digitalWrite(WIFI_LED, LOW);
    connected = true;
  }
}

const bool WifiHandler::handle(time_t timestamp)
{
  if (timestamp - lastTimestamp >= 500 && isInStationMode())
  {
    lastTimestamp = timestamp;
    int status = WiFi.status();

    if (connected)
    {
      if (status == WL_CONNECTED)
      {
        return true;
      }
      else
      {
        LOG0("WARNING: WiFi connection lost!\n");

        wifiOff();
        wifiInitStationMode();

        connected = false;
      }
    }
    else
    {
      if (status == WL_CONNECTED)
      {
        Serial.println("\n");
        Serial.printf("WiFi connected to %s\n", appcfgRD.wifi_ssid);

        if (appcfgRD.net_mode == NET_MODE_DHCP)
        {
          Serial.println( "copy wifi config from dhcp response" );
          strncpy(appcfgRD.net_host, WiFi.localIP().toString().c_str(), 63);
          strncpy(appcfgRD.net_gateway, WiFi.gatewayIP().toString().c_str(),
                  63);
          strncpy(appcfgRD.net_mask, WiFi.subnetMask().toString().c_str(), 63);
          strncpy(appcfgRD.net_dns, WiFi.dnsIP().toString().c_str(), 63);
        }
        else
        {
          Serial.println( "setting dns server" );
          IPAddress dns;
          dns.fromString(appcfgRD.net_dns);
          WiFi.dnsIP(dns);
        }

        Serial.printf(" - host ip address: %s\n", appcfgRD.net_host);
        Serial.printf(" - gateway: %s\n", appcfgRD.net_gateway);
        Serial.printf(" - mask: %s\n", appcfgRD.net_mask);
        Serial.printf(" - dns server: %s\n", appcfgRD.net_dns);

        Serial.println();
        digitalWrite(WIFI_LED, LOW);
        connected = true;
      }
      else
      {
        Serial.print(".");
        digitalWrite(WIFI_LED, digitalRead(WIFI_LED) ^ true);
      }
    }
  }
  return connected;
}

const bool WifiHandler::isInStationMode()
{
  return (appcfgRD.wifi_mode == WIFI_STA);
}

const bool WifiHandler::isConnected() { return connected; }

const bool WifiHandler::isReady() { return isConnected() && isInStationMode(); }

const char *WifiHandler::scanNetworks()
{
  networkBuffer[0] = 0;

  Serial.println("\nScanning WiFi networks...");
  int n = WiFi.scanNetworks(false, false);
  Serial.println("done.");

  if (n == 0)
  {
    Serial.println("no networks found");
    strcpy(networkBuffer, "no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    int l = 0;

    for (int i = 0; i < n; ++i)
    {
      l += sprintf(networkBuffer + l, "%2d: %s (%d)%s\n", i + 1,
                   WiFi.SSID(i).c_str(), WiFi.RSSI(i),
                   (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(5);
    }
  }

  Serial.println("----------------------------------------------");
  Serial.print(networkBuffer);
  Serial.println("----------------------------------------------");

  return networkBuffer;
}

const char *WifiHandler::getScannedNetworks() { return networkBuffer; }

char ipBuffer[32];

const char *WifiHandler::getLocalIP()
{
  strncpy(ipBuffer, WiFi.localIP().toString().c_str(), 31);
  ipBuffer[31] = 0;
  return ipBuffer;
}
