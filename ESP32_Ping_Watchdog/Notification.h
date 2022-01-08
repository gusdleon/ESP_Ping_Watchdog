WiFiClient client;
HTTPClient https;

String value1;
String value2;
String value3;
bool ult_estado = false;

void sendNotification() {
  WiFiClientSecure *client = new WiFiClientSecure;
  client -> setCACert(rootCACertificate);

  https.begin(*client, "https://" IFTTT_host "/trigger/" IFTTT_Event "/with/key/" IFTTT_Maker_Key "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3); //https
  int httpCode = https.GET();
  Serial.println(httpCode);
  if (httpCode == 200) {
    Serial.println("Contactado IFTTT con exito");
  } else {
    Serial.println("Error al contactar con IFTTT :( No internet?");
  }
  Serial.println(https.getString());
}
