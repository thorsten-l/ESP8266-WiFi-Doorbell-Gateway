#include <Arduino.h>
#include <App.hpp>
#include <WifiHandler.hpp>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "MqttHandler.hpp"

MqttHandler mqttHandler;

static WiFiClient wifiClient;
static PubSubClient client(wifiClient);
static long lastReconnectAttempt = 0;

MqttHandler::MqttHandler()
{
  initialized = false;
}

bool MqttHandler::reconnect()
{
  if (( appcfgRD.mqtt_useauth && client.connect(appcfgRD.mqtt_clientid, appcfgRD.mqtt_user, appcfgRD.mqtt_password ))
      || ( !appcfgRD.mqtt_useauth && client.connect(appcfgRD.mqtt_clientid)))
  {
    LOG0( "mqtt broker connected\n" );
  }

  return client.connected();
}


////////

void MqttHandler::setup()
{
  LOG0("MQTT Setup...\n");
  client.setServer( appcfgRD.mqtt_host, appcfgRD.mqtt_port );
  initialized = true;
}

void MqttHandler::handle()
{
  if ( appcfgRD.mqtt_enabled && wifiHandler.isReady())
  {
    if ( initialized == false )
    {
      setup();
    }

    if (!client.connected())
    {
      long now = millis();

      if (now - lastReconnectAttempt > 5000)
      {
        lastReconnectAttempt = now;

        if (reconnect())
        {
          lastReconnectAttempt = 0;
        }
      }
    }
    else
    {
      client.loop();
    }
  }
}

void MqttHandler::sendValue( const char* value )
{
  if( appcfgRD.mqtt_enabled && wifiHandler.isReady() && client.connected())
  {
    client.publish( appcfgRD.mqtt_outtopic, value );
  }
}
