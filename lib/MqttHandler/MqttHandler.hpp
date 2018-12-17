#ifndef __MQTT_HANDLER_H__
#define __MQTT_HANDLER_H__

class MqttHandler
{
private:
  bool initialized;
  bool reconnect();
  void setup();

public:
  MqttHandler();
  void handle();
  void sendValue( const char* value );
};

extern MqttHandler mqttHandler;

#endif
