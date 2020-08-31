void OTA() {
  // El puerto por defecto es 8266
  // ArduinoOTA.setPort(8266);

  // El Hostname por defecto es esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // Sin autenticación por defecto
  // ArduinoOTA.setPassword("admin");

  // La contraseña poede ser configurada con su valor md5 value tambien.
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "Sistema de Archivos";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Iniciando actualización " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nCompletado");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progreso: %u%%\n", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Autenticacion Fallida");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Inicio Fallido");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Conexión fallida");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Recepción Fallida");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Finalización Fallida");
    }
  });

  ArduinoOTA.begin();
  Serial.println("Listo");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}
