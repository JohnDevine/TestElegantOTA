
//  NOTE!!! If the system does not reboot after an update add "ElegantOTA.onStart" to the setup function

#if defined(ESP8266)
//===========
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>
//===========
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#endif

#include <ElegantOTA.h>
#include <elapsedMillis.h>

//============== Include JD stuff ===============
#define ARDUINOTRACE_ENABLE true // Enable ArduinoTrace ((#define ARDUINOTRACE_ENABLE = true) = do trace,(#define ARDUINOTRACE_ENABLE = false) = don't trace)
#include "JDGlobal.h"

#include "LedBlinker.h"
//===============================================

LedBlinker led(2, 200, 1000, 2);

ESP8266WiFiMulti wifiMulti; // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

const char *ssid = "TestOTA";
const char *password = "1234567890";

#if defined(ESP8266)
ESP8266WebServer server(80);
#elif defined(ESP32)
WebServer server(80);
#endif

void setup(void)
{
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  led.BlinkIt(SetupStarted);
  // ====================================
  /*
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  */
  // ====================== setup wifi networks to try to connect to - select the strongest ===========
  wifiMulti.addAP("BAANFARANG_O", "tAssy@#28");
  wifiMulti.addAP("BAANFARANG_2.4GHz", "tAssy@#28"); // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("BAANFARANG_5GHz", "tAssy@#28");
  wifiMulti.addAP("SolarBlue", "BAAN231101");
  Serial.println("Connecting ...");

  while (wifiMulti.run() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(500);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID()); // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

  // ================ setup the mDns responder ======================================
  if (MDNS.begin("esp8266"))
  { // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  }
  else
  {
    Serial.println("Error setting up MDNS responder!");
  }

  // ================================= setup the LittleFS file system ==================
  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
  }

  // ==================================== Set up webserver routes ====================================

  server.on("/", []()
            { server.send(200, "text/plain", "Hi! This is ElegantOTA from JD10"); });

  // ==================================== Set up OTA updates ====================================

  ElegantOTA.onStart([]()
                     {
                       Serial.println("OTA update process started.");
                       // Add your initialization tasks here.
                     });
  /* =============== This (below)causes a crash on the ESP8266 ===============

    ElegantOTA.onProgress([](size_t current, size_t final)
                          { Serial.printf("Progress: %u%%\n", (current * 100) / final); });

  */
  ElegantOTA.onEnd([](bool success)
                   {
  if (success) {
    Serial.println("OTA update completed successfully.");
    // Add success handling here.
  } else {
    Serial.println("OTA update failed.");
    // Add failure handling here.
  } });
  ElegantOTA.setAuth("JohnDevine", "1234567890");

  ElegantOTA.begin(&server); // Start ElegantOTA
  // ==================================== Start the web server ====================================

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  MDNS.update(); // NOTE!! this is needed each loop to make the mDns respond
  server.handleClient();
  ElegantOTA.loop(); // Necessary for reboot
}
