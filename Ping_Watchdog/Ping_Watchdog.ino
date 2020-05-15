/*
  Con este Sketch un ESP8266 puede monirorear a base de ping's una maquina y saber si esta al alcance.
  y si el estado de la maquina cambia, envia una solicitud a el servicio de Webkooks de IFTTT.
*/
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <ESP8266HTTPClient.h>

#define ssid "SSID"
#define password "password"

char host_remoto[] = "Nombre_De_Host_Remoto_O_IP";
IPAddress ip_remota; //IP a monitorear
bool ult_estado = false;

#define IFTTT_host "maker.ifttt.com"
#define IFTTT_Maker_Key "Tu_key" //Añade tus credenciales de IFTTT, Puedes encontrar tu key en https://ifttt.com/maker_webhooks/settings
#define IFTTT_Event "Tu_Evento" //Añade el nombre de tu evento, para esto tendras que haber creado primero un Applet en IFTTT con el Trigger Webhooks
String value1;
String value2;
String value3;

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(250000);
  delay(10);

  //Nos Conectamos a una Red WiFi
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
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.hostByName(host_remoto, ip_remota); //Resolviendo el host a monitorear a IP

    Serial.print("Haciendo ping a: ");
    Serial.print(host_remoto);
    Serial.print(" con ip: ");
    Serial.println(ip_remota);

    if (Ping.ping(ip_remota) && ult_estado == false) {
      Serial.println("¡¡EXITO!!");
      http.begin(client, "http://" IFTTT_host "/trigger/" IFTTT_Event "/with/key/" IFTTT_Maker_Key "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3); //HTTP
      int httpCode = http.GET();
      Serial.println(httpCode);
      if (httpCode == 200) {
        Serial.println("Contactado IFTTT con exito");
      } else {
        Serial.println("Error al contactar con IFTTT :( No internet?");
      }
      Serial.println(http.getString());
      ult_estado = true;
    } else if (Ping.ping(ip_remota) == false && ult_estado == true) {
      Serial.println("Error :(");
      http.begin(client, "http://" IFTTT_host "/trigger/" IFTTT_Event "/with/key/" IFTTT_Maker_Key "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3); //HTTP
      int httpCode = http.GET();
      Serial.println(httpCode);
      if (httpCode == 200) {
        Serial.println("Contactado IFTTT con exito");
      } else {
        Serial.println("Error al contactar con IFTTT :( No internet?");
      }
      Serial.println(http.getString());
      ult_estado = false;
    }
    delay(3000);
  }
}
