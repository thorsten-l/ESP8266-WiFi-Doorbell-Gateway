#include <App.hpp>
#include <DefaultAppConfig.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WifiHandler.hpp>
#include "WebHandler.hpp"
#include "pure-min-css-gz.h"
#include "layout-css-gz.h"
#include "template-html.h"

WebHandler webHandler;

static AsyncWebServer server(80);
extern bool buttonPressed;

String jsonStatus()
{
  String message = "{\"state\":";
  message += ( buttonPressed ) ? "1}\r\n" : "0}\r\n";
  return message;
}

void handlePageNotFound( AsyncWebServerRequest *request )
{
  request->send(404);
}

void prLegend( AsyncResponseStream *response, const char *name )
{
  response->printf( "<legend>%s</legend>", name );
}

void prGroupLabel( AsyncResponseStream *response, int id, const char *label )
{
  response->printf(
    "<div class='pure-control-group'>"
      "<label for='pgid%d'>%s</label>", id, label );
}

void prTextGroup( AsyncResponseStream *response, int id, const char *label,
   const char *name, const char *value )
{
  prGroupLabel( response, id, label );
  response->printf(
      "<input id='pgid%d' type='text' name='%s' maxlength='64' value='%s'>"
    "</div>", id, name, value );
}

void prTextGroup( AsyncResponseStream *response, int id, const char *label,
   const char *name, int value )
{
  prGroupLabel( response, id, label );
  response->printf(
      "<input id='pgid%d' type='text' name='%s' maxlength='64' value='%d'>"
    "</div>", id, name, value );
}

void prCheckBoxGroup( AsyncResponseStream *response, int id, const char *label,
   const char *name, bool value )
{
  prGroupLabel( response, id, label );
  response->printf(
      "<input id='pgid%d' type='checkbox' name='%s' value='true' %s>"
    "</div>", id, name, value ? "checked" : "" );
}

void prSelectStart( AsyncResponseStream *response, int id, const char *label, const char *name )
{
  prGroupLabel( response, id, label );
  response->printf("<select id='pgid%d' name='%s'>", id, name );
}

void prSelectEnd( AsyncResponseStream *response )
{
  response->print("</select></div>" );
}

void prOption( AsyncResponseStream *response, int value, const char *name, bool selected )
{
  response->printf("<option %s value='%d'>%s</option>", selected ? "selected" : "", value, name );
}

void handleSetupPage( AsyncWebServerRequest *request )
{
  int id = 0;

  if(!request->authenticate("admin", appcfg.admin_password))
  {
    return request->requestAuthentication();
  }

  AsyncResponseStream *response = request->beginResponseStream("text/html");
  response->printf( TEMPLATE_HEADER, APP_NAME " - Setup");
  response->println("<form class=\"pure-form pure-form-aligned\" action='/savecfg' method=POST><fieldset>");

  // Setup

  prLegend( response, "Setup 'admin' user" );
  prTextGroup( response, id++, "Password", "admin_password", appcfg.admin_password );

  // WiFi
  prLegend( response, "WiFi Network Scan" );
  response->printf("<pre>%s</pre>\n", wifiHandler.getScannedNetworks() );

  prLegend( response, "WiFi" );

  prSelectStart( response, id++, "Mode", "wifi_mode" );
  prOption( response, WIFI_AP, "Access Point", appcfg.wifi_mode == WIFI_AP );
  prOption( response, WIFI_STA, "Station", appcfg.wifi_mode == WIFI_STA );
  prSelectEnd( response );

  prTextGroup( response, id++, "SSID", "wifi_ssid", appcfg.wifi_ssid );
  prTextGroup( response, id++, "Password", "wifi_password", appcfg.wifi_password );

  // Network
  prLegend( response, "Network" );

  prSelectStart( response, id++, "Mode", "net_mode" );
  prOption( response, WIFI_AP, "DHCP", appcfg.net_mode == NET_MODE_DHCP );
  prOption( response, WIFI_STA, "Static", appcfg.net_mode == NET_MODE_STATIC );
  prSelectEnd( response );

  prTextGroup( response, id++, "Host Address", "net_host", appcfg.net_host );
  prTextGroup( response, id++, "Gateway", "net_gateway", appcfg.net_gateway );
  prTextGroup( response, id++, "Netmask", "net_mask", appcfg.net_mask );
  prTextGroup( response, id++, "DNS Server", "net_dns", appcfg.net_dns );

  // OTA (Over The Air - firmware update)
  prLegend( response, "Over The Air - firmware update (OTA)");
  prTextGroup( response, id++, "Hostname", "ota_hostname", appcfg.ota_hostname );
  prTextGroup( response, id++, "Password", "ota_password", appcfg.ota_password );

  // OpenHAB
  prLegend( response, "OpenHAB");
  prCheckBoxGroup( response, id++, "Callback Enabled", "ohab_enabled", appcfg.ohab_enabled );

  prSelectStart( response, id++, "OpenHAB Version", "ohab_version" );
  prOption( response, 1, "1.8", appcfg.ohab_version == 1 );
  prOption( response, 2, "&gt;=2.0", appcfg.ohab_version == 2 );
  prSelectEnd( response );

  prTextGroup( response, id++, "Item Name", "ohab_itemname", appcfg.ohab_itemname );
  prTextGroup( response, id++, "Host", "ohab_host", appcfg.ohab_host );
  prTextGroup( response, id++, "Port", "ohab_port", appcfg.ohab_port );
  prCheckBoxGroup( response, id++, "Use Authentication", "ohab_useauth", appcfg.ohab_useauth );
  prTextGroup( response, id++, "User", "ohab_user", appcfg.ohab_user );
  prTextGroup( response, id++, "Password", "ohab_password", appcfg.ohab_password );

  // MQTT
  prLegend( response, "MQTT");
  prCheckBoxGroup( response, id++, "Enabled", "mqtt_enabled", appcfg.mqtt_enabled );
  prTextGroup( response, id++, "Client ID", "mqtt_clientid", appcfg.mqtt_clientid );
  prTextGroup( response, id++, "Host", "mqtt_host", appcfg.mqtt_host );
  prTextGroup( response, id++, "Port", "mqtt_port", appcfg.mqtt_port );
  prCheckBoxGroup( response, id++, "Use Authentication", "mqtt_useauth", appcfg.mqtt_useauth );
  prTextGroup( response, id++, "User", "mqtt_user", appcfg.mqtt_user );
  prTextGroup( response, id++, "Password", "mqtt_password", appcfg.mqtt_password );
  prTextGroup( response, id++, "Out Topic", "mqtt_outtopic", appcfg.mqtt_outtopic );

  // Syslog
  prLegend( response, "Syslog");
  prCheckBoxGroup( response, id++, "Enabled", "syslog_enabled", appcfg.syslog_enabled );
  prTextGroup( response, id++, "Host", "syslog_host", appcfg.syslog_host );
  prTextGroup( response, id++, "Port (TCP)", "syslog_port", appcfg.syslog_port );
  prTextGroup( response, id++, "App Name", "syslog_app_name", appcfg.syslog_app_name );

  response->println("<p><input class='pure-button pure-button-primary' type='submit' value='Save Configuration'></p>");
  response->println("</fieldset></form>");
  response->print( TEMPLATE_FOOTER );
  request->send(response);
}

void paramChars( AsyncWebServerRequest *request, char *dest,
   const char* paramName, const char* defaultValue )
{
  const char *value = defaultValue;

  if(request->hasParam( paramName, true ))
  {
    AsyncWebParameter* p = request->getParam(paramName, true);
    value = p->value().c_str();
    if ( value == 0 || strlen( value ) == 0 )
    {
      value = defaultValue;
    }
  }

  strncpy( dest, value, 63 );
  dest[63] = 0;
}

int paramInt( AsyncWebServerRequest *request, const char* paramName, int defaultValue )
{
  int value = defaultValue;

  if(request->hasParam( paramName, true ))
  {
    AsyncWebParameter* p = request->getParam(paramName, true);
    const char *pv = p->value().c_str();
    if ( pv != 0 && strlen( pv ) > 0 )
    {
      value = atoi( pv );
    }
  }

  return value;
}

bool paramBool( AsyncWebServerRequest *request, const char* paramName )
{
  bool value = false;

  if(request->hasParam( paramName, true ))
  {
    AsyncWebParameter* p = request->getParam(paramName, true);
    const char *pv = p->value().c_str();
    if ( pv != 0 && strlen( pv ) > 0 )
    {
      value = strcmp( "true", pv ) == 0;
    }
  }
  return value;
}

void handleSavePage( AsyncWebServerRequest *request )
{
  if(!request->authenticate("admin", appcfg.admin_password))
  {
    return request->requestAuthentication();
  }

  AsyncResponseStream *response = request->beginResponseStream("text/html");
  response->printf( TEMPLATE_HEADER, APP_NAME " - Save Configuration");
  response->print("<pre>");

  int params = request->params();

  for(int i=0;i<params;i++)
  {
    AsyncWebParameter* p = request->getParam(i);
    response->printf("%s = '%s'\n", p->name().c_str(), p->value().c_str());
  }

  // Security
  paramChars( request, appcfgWR.admin_password, "admin_password", DEFAULT_ADMIN_PASSWORD );

  // WIFI
  appcfgWR.wifi_mode = paramInt( request, "wifi_mode", DEFAULT_WIFI_MODE);
  paramChars( request, appcfgWR.wifi_ssid, "wifi_ssid", DEFAULT_WIFI_SSID );
  paramChars( request, appcfgWR.wifi_password, "wifi_password", DEFAULT_WIFI_PASSWORD );

  // Network
  appcfgWR.net_mode = paramInt( request, "net_mode", DEFAULT_NET_MODE );
  paramChars( request, appcfgWR.net_host, "net_host", DEFAULT_NET_HOST );
  paramChars( request, appcfgWR.net_gateway, "net_gateway", DEFAULT_NET_GATEWAY );
  paramChars( request, appcfgWR.net_mask, "net_mask", DEFAULT_NET_MASK );
  paramChars( request, appcfgWR.net_dns, "net_dns", DEFAULT_NET_DNS );
 
  // OTA
  paramChars( request, appcfgWR.ota_hostname, "ota_hostname", DEFAULT_OTA_HOSTNAME );
  paramChars( request, appcfgWR.ota_password, "ota_password", DEFAULT_OTA_PASSWORD );

  // OpenHAB
  appcfgWR.ohab_enabled = paramBool( request, "ohab_enabled" );
  appcfgWR.ohab_version = paramInt( request, "ohab_version", DEFAULT_OHAB_VERSION );
  paramChars( request, appcfgWR.ohab_itemname, "ohab_itemname", DEFAULT_OHAB_ITEMNAME );
  paramChars( request, appcfgWR.ohab_host, "ohab_host", DEFAULT_OHAB_HOST );
  appcfgWR.ohab_port = paramInt( request, "ohab_port", DEFAULT_OHAB_PORT );
  appcfgWR.ohab_useauth = paramBool( request, "ohab_useauth" );
  paramChars( request, appcfgWR.ohab_user, "ohab_user", DEFAULT_OHAB_USER );
  paramChars( request, appcfgWR.ohab_password, "ohab_password", DEFAULT_OHAB_PASSWORD );

  // MQTT
  appcfgWR.mqtt_enabled = paramBool( request, "mqtt_enabled" );
  paramChars( request, appcfgWR.mqtt_clientid, "mqtt_clientid", DEFAULT_MQTT_CLIENTID );
  paramChars( request, appcfgWR.mqtt_host, "mqtt_host", DEFAULT_MQTT_HOST );
  appcfgWR.mqtt_port = paramInt( request, "mqtt_port", DEFAULT_MQTT_PORT );
  appcfgWR.mqtt_useauth = paramBool( request, "mqtt_useauth" );
  paramChars( request, appcfgWR.mqtt_user, "mqtt_user", DEFAULT_MQTT_USER );
  paramChars( request, appcfgWR.mqtt_password, "mqtt_password", DEFAULT_MQTT_PASSWORD );
  paramChars( request, appcfgWR.mqtt_outtopic, "mqtt_outtopic", DEFAULT_MQTT_OUTTOPIC );

  // Syslog
  appcfgWR.syslog_enabled = paramBool( request, "syslog_enabled" );
  paramChars( request, appcfgWR.syslog_host, "syslog_host", DEFAULT_SYSLOG_HOST );
  appcfgWR.syslog_port = paramInt( request, "syslog_port", DEFAULT_SYSLOG_PORT );
  paramChars( request, appcfgWR.syslog_app_name, "syslog_app_name", DEFAULT_SYSLOG_APP_NAME );

  response->println("</pre>");
  response->println("<h2 style='color: red'>Restarting System</h2>");
  response->print( TEMPLATE_FOOTER );
  request->send(response);
  app.delayedSystemRestart();
}


void handleRootPage( AsyncWebServerRequest *request )
{

  if(request->hasParam( "ring" ))
  {
    AsyncWebParameter* p = request->getParam("ring");
    const char *pv = p->value().c_str();
    if ( pv != 0 && strlen( pv ) > 0 )
    {
      if ( strcmp( "ON", pv ) == 0 )
      {
        buttonPressed = true;
      }
    }
    request->redirect("/");
    return;
  }


  char titleBuffer[100];
  sprintf( titleBuffer, APP_NAME " - %s", appcfg.ota_hostname );

  AsyncResponseStream *response = request->beginResponseStream("text/html");
  response->printf( TEMPLATE_HEADER, titleBuffer );

  response->print("<form class='pure-form'>");

  prLegend( response, "Actions");
  response->print("<a href=\"/?ring=ON\" class=\"pure-button button-on\">RING</a>" );

  response->print("</form>");
  response->print( TEMPLATE_FOOTER );
  request->send(response);
}


WebHandler::WebHandler()
{
  initialized = false;
}

void WebHandler::setup()
{
  LOG0("HTTP server setup...\n");

  server.on( "/", HTTP_GET, handleRootPage );
  server.on( "/setup.html", HTTP_GET, handleSetupPage );
  server.on( "/savecfg", HTTP_POST, handleSavePage );
  server.onNotFound( handlePageNotFound );

  server.on("/ring", HTTP_GET, [](AsyncWebServerRequest *request) {
    buttonPressed = true;
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "{\"state\":1}\r\n" );
    response->addHeader( "Access-Control-Allow-Origin", "*" );
    request->send(response);  });

  server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", jsonStatus() );
    response->addHeader( "Access-Control-Allow-Origin", "*" );
    request->send(response);
  });

  server.on("/pure-min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css",
            PURE_MIN_CSS_GZ, PURE_MIN_CSS_GZ_LEN);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  server.on("/layout.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css",
            LAYOUT_CSS_GZ, LAYOUT_CSS_GZ_LEN);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  server.on("/info.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->printf( TEMPLATE_HEADER, APP_NAME " - Info");

    response->print("<form class='pure-form'>");

    prLegend( response, "Application");

    response->print(
      "<p>Name: " APP_NAME "</p>"
      "<p>Version: " APP_VERSION "</p>"
      "<p>Author: Dr. Thorsten Ludewig &lt;t.ludewig@gmail.com></p>");

    prLegend( response, "RESTful API");
      char ipAddress[16];
      strcpy( ipAddress, WiFi.localIP().toString().c_str());

    response->printf("<p><a href='http://%s/ring'>http://%s/ring</a> - Ring</p>"
      "<p><a href='http://%s/state'>http://%s/state</a> - Doorbell JSON status (0 or 1)</p>",
      ipAddress, ipAddress, ipAddress, ipAddress );

      prLegend( response, "Build");
      response->print(
        "<p>Date: " __DATE__ "</p>"
        "<p>Time: " __TIME__ "</p>");

    prLegend( response, "Services");
    response->printf( "<p>OpenHAB Callback Enabled: %s</p>", (appcfg.ohab_enabled) ? "true" : "false" );
    response->printf( "<p>MQTT Enabled: %s</p>", (appcfg.mqtt_enabled) ? "true" : "false" );
    response->printf( "<p>Syslog Enabled: %s</p>", (appcfg.syslog_enabled) ? "true" : "false" );

    response->print("</form>");
    response->print( TEMPLATE_FOOTER );
    request->send( response );
  });

  MDNS.addService("http", "tcp", 80);
  MDNS.addServiceTxt( "http", "tcp", "path", "/" );
  MDNS.addServiceTxt( "http", "tcp", "fw_name", APP_NAME );
  MDNS.addServiceTxt( "http", "tcp", "fw_version", APP_VERSION );

  server.begin();

  LOG0("HTTP server started\n");
  initialized = true;
}

void WebHandler::handle()
{
  if( ! initialized )
  {
    setup();
  }
}
