ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "esp8266 Ping Watchdog listo!");
}

void handleNotFound() {
  String message = "Archivo no encontrado\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMetodo: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArgumentos: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void ServerHandles() {
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
}
