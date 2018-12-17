#ifndef __DEFAULT_APP_CONFIG_H__
#define __DEFAULT_APP_CONFIG_H__

#include <ESP8266WiFi.h>

#define DEFAULT_WIFI_SSID "DoorbellGW-%06x"
#define DEFAULT_WIFI_PASSWORD "12345678"
#define DEFAULT_WIFI_MODE WIFI_AP

#define DEFAULT_OTA_HOSTNAME "doorbell-gateway-1"
#define DEFAULT_OTA_PASSWORD "otapass"

#define DEFAULT_ADMIN_PASSWORD "admin"

#define DEFAULT_OHAB_ENABLED false
#define DEFAULT_OHAB_VERSION 1
#define DEFAULT_OHAB_HOST "192.168.1.1"
#define DEFAULT_OHAB_PORT 80
#define DEFAULT_OHAB_USEAUTH true
#define DEFAULT_OHAB_USER "user"
#define DEFAULT_OHAB_PASSWORD "password"
#define DEFAULT_OHAB_ITEMNAME "DoorbellGateway1"

#define DEFAULT_MQTT_ENABLED false
#define DEFAULT_MQTT_CLIENTID "DoorbellGateway1"
#define DEFAULT_MQTT_HOST "192.168.1.1"
#define DEFAULT_MQTT_PORT 1883
#define DEFAULT_MQTT_USEAUTH true
#define DEFAULT_MQTT_USER "user"
#define DEFAULT_MQTT_PASSWORD "password"
#define DEFAULT_MQTT_OUTTOPIC "doorbell1/out"

#define DEFAULT_SYSLOG_ENABLED false
#define DEFAULT_SYSLOG_HOST "192.168.1.1"
#define DEFAULT_SYSLOG_PORT 514
#define DEFAULT_SYSLOG_APP_NAME "doorbell-gateway"

#endif
