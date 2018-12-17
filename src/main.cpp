#include <Arduino.h>
#include <App.hpp>
#include <ESP8266WiFi.h>
#include <WifiHandler.hpp>
#include <OtaHandler.hpp>
#include <Syslog.hpp>
#include <WebHandler.hpp>
#include <OpenHabHandler.hpp>
#include <MqttHandler.hpp>

time_t lifeTicker;
time_t maxLoopTime;
time_t lastLoopTimestamp;
time_t thisLoopTimestamp;
time_t debounceTimestamp;
time_t buttonPressed0Timestamp;

volatile bool buttonPressed0;
volatile bool buttonPressed;
volatile bool showPressingDuration;

bool firstRun;
bool wifiAlreadyConnected;

void ringButtonPressed()
{
  time_t cm = millis();

  if (!buttonPressed && (cm - debounceTimestamp > 1000)) // button debouncing
  {
    buttonPressed0 = true;
    buttonPressed0Timestamp = cm;
  }

  if (buttonPressed0 && (cm - buttonPressed0Timestamp) >= 35)
  {
    buttonPressed = true;
    buttonPressed0 = false;
  }

  showPressingDuration = true;
  debounceTimestamp = millis();
}

void setup()
{
  buttonPressed0 = false;
  buttonPressed = false;
  wifiAlreadyConnected = false;
  showPressingDuration = false;
  firstRun = true;
  app.setup();
  app.writeConfig();
  app.printConfig();
  wifiHandler.setup();

  attachInterrupt(digitalPinToInterrupt(RING_BUTTON), &ringButtonPressed, FALLING);

  maxLoopTime = 0l;
  lifeTicker = lastLoopTimestamp = millis();
}

void loop()
{
  thisLoopTimestamp = millis();
  maxLoopTime = max(maxLoopTime, thisLoopTimestamp - lastLoopTimestamp);
  lastLoopTimestamp = thisLoopTimestamp;

  if (buttonPressed0 && (thisLoopTimestamp - debounceTimestamp) >= 200)
  {
    buttonPressed = false;
    buttonPressed0 = false;
    syslog.logInfo("Ringbutton pressed to short");
  }

  if ( showPressingDuration && (thisLoopTimestamp - debounceTimestamp) >= 1000)
  {
    showPressingDuration = false;
    syslog.logInfo("button pressing time in ms:", (int)(debounceTimestamp-buttonPressed0Timestamp));
  }

  if (buttonPressed)
  {
    buttonPressed = false;
    LOG0("Button pressed...\n");
    syslog.logInfo("The doorbell is ringing.");
    openHabHandler.sendValue("ON");
    mqttHandler.sendValue("ON");
  }

  if ((thisLoopTimestamp - lifeTicker) >= 120000)
  {
    LOG1("max loop time = %ld\n", maxLoopTime);
    LOG1("wifi is connected %d\n", wifiHandler.isConnected());
    maxLoopTime = 0l;
    lifeTicker = thisLoopTimestamp;
    syslog.logInfo("i'm alive");
  }

  if (wifiHandler.handle(thisLoopTimestamp))
  {
    otaHandler.handle(); 
    webHandler.handle();
    mqttHandler.handle();

    if (firstRun)
    {
      syslog.logInfo(APP_NAME ", Version " APP_VERSION ", by " APP_AUTHOR);
      syslog.logInfo("Build date: " __DATE__ " " __TIME__);
      firstRun = false;
    }

    if ( !wifiAlreadyConnected )
    {
      syslog.logInfo("WiFi connected");
      syslog.logInfo("  ip addr:", WiFi.localIP().toString().c_str());
      syslog.logInfo("  netmask:", WiFi.subnetMask().toString().c_str());
      syslog.logInfo("  gateway:", WiFi.gatewayIP().toString().c_str());
      syslog.logInfo("  dns server:", WiFi.dnsIP().toString().c_str());
      wifiAlreadyConnected = true;
    }
  }
  else
  {
    wifiAlreadyConnected = false;
  }

  app.handle();
}