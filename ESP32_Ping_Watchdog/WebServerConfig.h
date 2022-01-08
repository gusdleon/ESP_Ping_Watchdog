WebServer server(80);

String GetContentType(String filename) {
  if (filename.endsWith(".htm") || filename.endsWith(".html"))return"text/html";
  else if (filename.endsWith(".css"))return"text/css";
  else if (filename.endsWith(".js"))return"application/javascript";
  else if (filename.endsWith(".png"))return"image/png";
  else if (filename.endsWith(".gif"))return"image/gif";
  else if (filename.endsWith(".jpg"))return"image/jpeg";
  else if (filename.endsWith(".ico"))return"image/x-icon";
  else if (filename.endsWith(".xml"))return"text/xml";
  else if (filename.endsWith(".pdf"))return"application/x-pdf";
  else if (filename.endsWith(".zip"))return"application/x-zip";
  else if (filename.endsWith(".gz"))return"application/x-gzip";
  else if (filename.endsWith(".mp4"))return"video/mp4";
  else return"text/plain";
}

void handleRoot() {
  Serial.println(server.uri());
  Serial.println("en Root");
  File file = fileSystem.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

void handlefile() {
  Serial.println("en handlefile");
  File file = fileSystem.open(server.uri(), "r");
  server.streamFile(file, GetContentType(server.uri()));
  file.close();
}

void handledir() {
  Serial.println("en handledir");
  File file = fileSystem.open(server.uri() + "/index.html", "r");
  server.streamFile(file, GetContentType(server.uri() + "/index.html"));
}

void handleNotFound() {
  Serial.println("y no existe");
  String message = "Error 404, Archivo no encontrado\n\n";
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

void NotFound() {
  Serial.println(server.uri());
  Serial.println("en notfound");
  if (fileSystem.exists(server.uri()) == true) {
    Serial.println("pero al direccion existe...\n\n\n");
    File file = fileSystem.open(server.uri(), "r");
    Serial.print("Es archivo: ");
    Serial.println(!file.isDirectory());
    Serial.print("Es directorio: ");
    Serial.println(file.isDirectory());
    Serial.print("Index interno Existe: ");
    Serial.println(fileSystem.exists(server.uri() + "/index.html"));
    
    if (!file.isDirectory()) {
      Serial.println("y es un archivo");
      handlefile();
    } else if (file.isDirectory() == true && fileSystem.exists(server.uri() + "/index.html") == true) {
      Serial.println("pero es un directorio, y ese directorio tiene un indext.html, enviando eso");
      handledir();
    } else {
      Serial.println("pero solo la direccion existe... por que?");
      handleNotFound();
    }
  } else {
    Serial.println("Pero recuerda que usas SPIFS y no soporta directorios");
    handleNotFound();
  }
}

void ServerHandles() {
  server.on("/", handleRoot);
  server.onNotFound(NotFound);
}
