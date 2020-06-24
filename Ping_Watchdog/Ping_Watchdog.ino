/*
  Con este Sketch un ESP8266 puede monitorear a base de ping's un equipo y saber si esta al alcance.
  Si el estado del equipo cambia, envia una solicitud a el servicio de Webkooks de IFTTT.
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266Ping.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoOTA.h>
#include "Config.h"
#include "WebServer.h"
#include "Notification.h"
#include "OTA.h"


IPAddress ip_remota; //IP a monitorear
bool FirstRun = true;



unsigned long previousMillis = 0;


void setup() {
  Serial.begin(250000);
  delay(10);

  //Nos Conectamos a una Red WiFi
  Serial.println("\nConectando a WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado a: ");
  Serial.println(ssid);
  Serial.print("con IP: ");
  Serial.println(WiFi.localIP());

  ServerHandles();
  server.begin();
  Serial.println("Servidor HTTP iniciado");

  if (!MDNS.begin("watchdog")) {
    Serial.println("Error configurando el servidor MDNS!");
    delay(1000);
    ESP.restart();
  }
  Serial.println("Servidor mDNS iniciado");
  MDNS.addService("http", "tcp", 80);

  OTA();
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  MDNS.update();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo || FirstRun == true ) {
    FirstRun = false;
    previousMillis = currentMillis;

    if (WiFi.status() == WL_CONNECTED) {
      WiFi.hostByName(host_remoto, ip_remota); //Resolviendo el host a monitorear a IP

      Serial.print("Haciendo ping a: ");
      Serial.print(host_remoto);
      Serial.print(" con ip: ");
      Serial.println(ip_remota);

      if (Ping.ping(ip_remota)) {
        Serial.println("¡¡EXITO!!");
        value1 = host_remoto;
        value2 = "ONLINE";
        if (ult_estado == false) {
          sendNotification();
        }
        ult_estado = true;
      } else if (!Ping.ping(ip_remota)) {
        Serial.println("Error :(");
        value1 = host_remoto;
        value2 = "OFFLINE";
        if (ult_estado == true) {
          sendNotification();
        }
        ult_estado = false;
      }
    }
  }
}
