# ESP8266-WiFi-Doorbell-Gateway
A gateway for your doorbell button ;-)

## Compile
This is a [PlatformIO](https://platformio.org/) project.

## Firmware Reset
1. Power on the WiFi Doorbell Gateway
2. Press down and hold the Power-Button during the first 5s
3. Release Power-Button when the WiFi LED starts rapidly fast blinking
4. The firmware reset ends after about 30s indicated by a permanent WiFi LED on.

## Default Settings
After a firmware reset the following values are set.

|    | value | description |
|----|-------|-------------|
| WiFi SSID | DoorbellGW-`esp id` | SSID in accesspoint mode |
| IP Address | 192.168.192.1 | ip address in accesspoint mode |
| Admin password | admin | Setup admin password |
| OTA Hostname | doorbell-gateway-1 | *O*ver *T*he *A*ir hostname |
| OTA Password | otapass | OTA firmware upload password |
| OpenHAB Callback Enabled | **false** | |
| OpenHAB Version | 1 | Callback for OpenHAB version 1 or 2 |
| OpenHAB Item Name | DoorbellGateway1 | |
| OpenHAB Host | 192.168.1.1 | |
| OpenHAB Port | 80 | |
| OpenHAB Use Authentication | false | |
| OpenHAB User | user |  |
| OpenHAB Password | password | |
| Alexa enabled | **false** |  |
| Alexa devicename | Socket | Devicename for Alexa HA |
| MQTT Enabled | **false** |  |
| MQTT ClientId | DoorbellGateway1 |  |
| MQTT Host | 192.168.1.1 | |
| MQTT Port | 80 | |
| MQTT Use Authentication | false | |
| MQTT User | user |  |
| MQTT Password | password | |
| MQTT Out Topic | doorbell1/out | sending callback |
| Syslog Enabled | **false** |  |
| Syslog Host | 192.168.1.1 | |
| Syslog Port (TCP) | 80 | |
| Syslog App Name | gateway-doorbell |  |

## Hardware
- [WEMOS D1 mini](https://wiki.wemos.cc/products:d1:d1_mini)

## References
- [PlatformIO](https://platformio.org/)
- [Arduino core for ESP8266 WiFi chip](https://github.com/esp8266/Arduino)
- [Async TCP Library for ESP8266](https://github.com/me-no-dev/ESPAsyncTCP)
- [Async Web Server for ESP8266 and ESP32](https://github.com/me-no-dev/ESPAsyncWebServer)
- [Arduino-pubsubclient - A client library for the ESP8266 that provides support for MQTT](https://github.com/heman4t/Arduino-pubsubclient)
- [Pure.CSS - A nice CSS, as GZIP it is less than 4k so it is useful for embedded devices](https://purecss.io/)
