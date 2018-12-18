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
  if (( appcfg.mqtt_useauth && client.connect(appcfg.mqtt_clientid, appcfg.mqtt_user, appcfg.mqtt_password ))
      || ( !appcfg.mqtt_useauth && client.connect(appcfg.mqtt_clientid)))
  {
    LOG0( "mqtt broker connected\n" );
  }

  return client.connected();
}


////////

void MqttHandler::setup()
{
  LOG0("MQTT Setup...\n");
  client.setServer( appcfg.mqtt_host, appcfg.mqtt_port );
  initialized = true;
}

void MqttHandler::handle()
{
  if ( appcfg.mqtt_enabled && wifiHandler.isReady())
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
  if( appcfg.mqtt_enabled && wifiHandler.isReady() && client.connected())
  {
    client.publish( appcfg.mqtt_outtopic, value );
  }
}
