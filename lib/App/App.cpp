#include "App.hpp"
#include "DefaultAppConfig.h"
#include <FS.h>

App app;
AppConfig appcfg;
AppConfig appcfgWR;

App::App()
{
  initialized = true;

  strncpy(appcfg.wifi_ssid, DEFAULT_WIFI_SSID, 63);
  strncpy(appcfg.wifi_password, DEFAULT_WIFI_PASSWORD, 63);
  appcfg.wifi_mode = DEFAULT_WIFI_MODE;

  appcfg.net_mode = DEFAULT_NET_MODE;
  strncpy(appcfg.net_host, DEFAULT_NET_HOST, 63);
  strncpy(appcfg.net_mask, DEFAULT_NET_MASK, 63);
  strncpy(appcfg.net_gateway, DEFAULT_NET_GATEWAY, 63);
  strncpy(appcfg.net_dns, DEFAULT_NET_DNS, 63);

  strncpy(appcfg.ota_hostname, DEFAULT_OTA_HOSTNAME, 63);
  strncpy(appcfg.ota_password, DEFAULT_OTA_PASSWORD, 63);

  strncpy(appcfg.admin_password, DEFAULT_ADMIN_PASSWORD, 63);

  appcfg.ohab_enabled = DEFAULT_OHAB_ENABLED;
  appcfg.ohab_version = DEFAULT_OHAB_VERSION;
  strncpy(appcfg.ohab_host, DEFAULT_OHAB_HOST, 63);
  appcfg.ohab_port = DEFAULT_OHAB_PORT;
  appcfg.ohab_useauth = DEFAULT_OHAB_USEAUTH;
  strncpy(appcfg.ohab_user, DEFAULT_OHAB_USER, 63);
  strncpy(appcfg.ohab_password, DEFAULT_OHAB_PASSWORD, 63);
  strncpy(appcfg.ohab_itemname, DEFAULT_OHAB_ITEMNAME, 63);

  appcfg.mqtt_enabled = DEFAULT_MQTT_ENABLED;
  strncpy(appcfg.mqtt_clientid, DEFAULT_MQTT_CLIENTID, 63);
  strncpy(appcfg.mqtt_host, DEFAULT_MQTT_HOST, 63);
  appcfg.mqtt_port = DEFAULT_MQTT_PORT;
  appcfg.mqtt_useauth = DEFAULT_MQTT_USEAUTH;
  strncpy(appcfg.mqtt_user, DEFAULT_MQTT_USER, 63);
  strncpy(appcfg.mqtt_password, DEFAULT_MQTT_PASSWORD, 63);
  strncpy(appcfg.mqtt_outtopic, DEFAULT_MQTT_OUTTOPIC, 63);

  appcfg.syslog_enabled = DEFAULT_SYSLOG_ENABLED;
  strncpy(appcfg.syslog_host, DEFAULT_SYSLOG_HOST, 63);
  appcfg.syslog_port = DEFAULT_SYSLOG_PORT;
  strncpy(appcfg.syslog_app_name, DEFAULT_SYSLOG_APP_NAME, 63);
}

void App::restartSystem()
{
  // watchdogTicker.detach();
  ESP.eraseConfig();
  LOG0("*** restarting system ***\n");
  delay(2000);
  ESP.restart();
  delay(2000);
  ESP.reset();
}

void App::setup()
{
  Serial.begin(115200);

  doSystemRestart = false;

  pinMode(RING_BUTTON, INPUT_PULLUP);
  pinMode(SETUP_BUTTON, INPUT_PULLUP);
  pinMode(WIFI_LED, OUTPUT);

  digitalWrite(WIFI_LED, 0);

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(WIFI_LED, 1);
    delay(500);
    digitalWrite(WIFI_LED, 0);
    delay(500);
  }

  Serial.println();
  Serial.println("\n\n");
  Serial.println("\n\n");
  Serial.println(F(APP_NAME ", Version " APP_VERSION ", by " APP_AUTHOR));
  Serial.println("Build date: " __DATE__ " " __TIME__);
  Serial.printf("appcfg file size: %d bytes\n\n", sizeof(appcfg));

  if (digitalRead(SETUP_BUTTON) == false)
  {
    Serial.println();
    LOG0("*** RESET app configuration ***\n");
    Serial.println();

    for (int i = 0; i < 15; i++)
    {
      digitalWrite(WIFI_LED, 1);
      delay(100);
      digitalWrite(WIFI_LED, 0);
      delay(100);
    }

    digitalWrite(WIFI_LED, 1);

    ESP.eraseConfig();

    if (SPIFFS.begin())
    {
      LOG0("File system format started...\n");
      SPIFFS.format();
      LOG0("File system format finished.\n");
      SPIFFS.end();
    }

    digitalWrite(WIFI_LED, 0);
    restartSystem();
  }

  ESP.eraseConfig();
  loadConfig();
  memcpy( &appcfgWR, &appcfg, sizeof(appcfg));
}

void App::loadConfig()
{
  if (!SPIFFS.begin())
  {
    LOG0("ERROR: Failed to mount file system");
  }
  else
  {
    if (SPIFFS.exists(APP_CONFIG_FILE))
    {
      File configFile = SPIFFS.open(APP_CONFIG_FILE, "r");

      if (!configFile)
      {
        LOG1("ERROR: file %s not found.\n", APP_CONFIG_FILE);
      }
      else
      {
        LOG1("Loading appcfguration from %s file...\n", APP_CONFIG_FILE);

        if (configFile.size() != sizeof(appcfg))
        {
          Serial.printf("ERROR: %s file size not match appcfg structure %d != %d bytes.\n", APP_CONFIG_FILE, configFile.size(), sizeof(appcfg));
        }
        else
        {
          int bytesRead = configFile.readBytes((char *)&appcfg, sizeof(appcfg));
          LOG1("%d bytes read from appcfg file.\n", bytesRead);
          configFile.close();
        }
      }
    }
    else
    {
      LOG0("WARNING: appcfg file " APP_CONFIG_FILE " does not exist. Using default appcfg.\n");
    }
    SPIFFS.end();
  }
}

void App::writeConfig()
{
  if (!SPIFFS.begin())
  {
    LOG0("ERROR: Failed to mount file system");
  }
  else
  {
    LOG1("writing file %s.\n", APP_CONFIG_FILE);

    File configFile = SPIFFS.open(APP_CONFIG_FILE, "w");

    if (!configFile)
    {
      LOG1("ERROR: Failed to open appcfg file %s for writing.\n", APP_CONFIG_FILE);
      return;
    }

    int length = configFile.write((const uint8_t *)&appcfgWR, sizeof(appcfgWR));
    LOG1("%d bytes written to appcfg file.\n", length);

    configFile.close();

    FSInfo fs_info;
    SPIFFS.info(fs_info);

    Serial.printf("\n--- SPIFFS Info ---\ntotal bytes = %d\n", fs_info.totalBytes);
    Serial.printf("used bytes = %d\n", fs_info.usedBytes);
    Serial.printf("block size = %d\n", fs_info.blockSize);
    Serial.printf("page size = %d\n", fs_info.pageSize);
    Serial.printf("max open files = %d\n", fs_info.maxOpenFiles);
    Serial.printf("max path length = %d\n", fs_info.maxPathLength);

    SPIFFS.end();
  }
}

void App::printConfig()
{
  Serial.println();
  Serial.println("--- App appcfguration -----------------------------------");
  Serial.println("  Security:");
  Serial.printf("    Admin password: %s\n", appcfg.admin_password);
  Serial.println("\n  WiFi:");
  Serial.printf("    SSID: %s\n", appcfg.wifi_ssid);
  Serial.printf("    Password: %s\n", appcfg.wifi_password);
  Serial.printf("    Mode: %s\n", (appcfg.wifi_mode == 1) ? "Station" : "Access Point");
  Serial.println("\n  Network:");
  Serial.printf("    Mode: %s\n", ( appcfg.net_mode == NET_MODE_DHCP ) ? "DHCP" : "Static");
  Serial.printf("    host address: %s\n", appcfg.net_host);
  Serial.printf("    gateway: %s\n", appcfg.net_gateway);
  Serial.printf("    netmask: %s\n", appcfg.net_mask);
  Serial.printf("    dns server: %s\n", appcfg.net_dns);
  Serial.println("\n  OTA:");
  Serial.printf("    Hostname: %s\n", appcfg.ota_hostname);
  Serial.printf("    Password: %s\n", appcfg.ota_password);
  Serial.println("\n  OpenHAB:");
  Serial.printf("    Enabled: %s\n", (appcfg.ohab_enabled ? "true" : "false"));
  Serial.printf("    Version: %d\n", appcfg.ohab_version);
  Serial.printf("    Host: %s\n", appcfg.ohab_host);
  Serial.printf("    Port: %d\n", appcfg.ohab_port);
  Serial.printf("    Use Auth: %s\n", (appcfg.ohab_useauth ? "true" : "false"));
  Serial.printf("    User: %s\n", appcfg.ohab_user);
  Serial.printf("    Password: %s\n", appcfg.ohab_password);
  Serial.printf("    Itemname: %s\n", appcfg.ohab_itemname);
  Serial.println("\n  MQTT:");
  Serial.printf("    Enabled: %s\n", (appcfg.mqtt_enabled ? "true" : "false"));
  Serial.printf("    Client ID: %s\n", appcfg.mqtt_clientid);
  Serial.printf("    Host: %s\n", appcfg.mqtt_host);
  Serial.printf("    Port: %d\n", appcfg.mqtt_port);
  Serial.printf("    Use Auth: %s\n", (appcfg.mqtt_useauth ? "true" : "false"));
  Serial.printf("    User: %s\n", appcfg.mqtt_user);
  Serial.printf("    Password: %s\n", appcfg.mqtt_password);
  Serial.printf("    Out Topic: %s\n", appcfg.mqtt_outtopic);
  Serial.println("\n  Syslog:");
  Serial.printf("    Enabled: %s\n", (appcfg.syslog_enabled ? "true" : "false"));
  Serial.printf("    Host: %s\n", appcfg.syslog_host);
  Serial.printf("    Port: %d\n", appcfg.syslog_port);
  Serial.printf("    App Name: %s\n", appcfg.syslog_app_name);
  Serial.println("---------------------------------------------------------");
  Serial.println();
}

void App::delayedSystemRestart()
{
  doSystemRestart = true;
  systemRestartTimestamp = millis();
  LOG0("*** delayedSystemRestart ***\n");
}

void App::handle()
{
  if (doSystemRestart && (millis() - systemRestartTimestamp) > 5000)
  {
    LOG0("*** doSystemRestart ***\n");
    writeConfig();
    restartSystem();
  }
}
