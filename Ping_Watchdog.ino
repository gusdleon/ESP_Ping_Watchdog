/*
  Con este Sketch un ESP8266 puede monirorear a base de ping's una maquina y saber si esta al alcance.
  y si el estado de la maquina cambia, envia una solicitud a el servicio de Webkooks de IFTTT.
*/
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <ESP8266HTTPClient.h>

#define IFTTT_host  "maker.ifttt.com"
#define IFTTT_Maker_Key "Tu_key" //Añade tus credenciales de IFTTT, Puedes encontrar tu key en https://ifttt.com/maker_webhooks/settings
#define IFTTT_Event "Tu_Evento" //Añade el nombre de tu evento, para esto tendras que haber creado primero un Applet en IFTTT con el Trigger Webhooks
String value1;
String value2;
String value3;

#define ssid  "SSID"
#define password  "password"

IPAddress ip_remota(192, 168, 1, 1); //IP a monitorear, cambiar por ip por defecto remplazando puntos por comas de la nueva IP

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(250000);
  delay(10);

  // Nos Conectamos a una Red WiFi
  Serial.println("\nConectando a WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado a WiFi con IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {


    Serial.print("Haciendo ping a: ");
    Serial.println(ip_remota);

    if (Ping.ping(ip_remota)) {
      Serial.println("¡¡EXITO!!");
      http.begin(client, "http://" IFTTT_host "/trigger/" IFTTT_Event "/with/key/" IFTTT_Maker_Key "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3); //HTTP
      int httpCode = http.GET();
      Serial.println(httpCode);
      Serial.println(http.getString());
    } else {
      Serial.println("Error :(");
      http.begin(client, "http://" IFTTT_host "/trigger/" IFTTT_Event "/with/key/" IFTTT_Maker_Key "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3); //HTTP
      int httpCode = http.GET();
      Serial.println(httpCode);
      Serial.println(http.getString());

    }
    delay(3000);
  }
}
