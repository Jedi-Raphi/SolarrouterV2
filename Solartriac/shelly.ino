
JsonDocument doc;

void shelly_update() {
  if (WiFi.status() == WL_CONNECTED) {  // Vérifier si connecté au WiFi




    WiFiClient client;
    String url = "/emeter/" + String(voie);
    String host = String(Shelly_addr);
    if (client.connect(Shelly_addr, 80)) {  // Connexion à l'IP de Shelly sur le port 80
      client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

      unsigned long timeout = millis();
      while (client.available() == 0) {
        if (millis() - timeout > 5000) {
          client.stop();
          return;
        }
      }


      //Serial.println(millis() - timeout);
      String response = "";
      while (client.available()) {
        char character = client.read();
        response += String(character);
      }

      String Shelly_data = response.substring(response.indexOf("{"));
      Serial.println(Shelly_data);
      client.stop();
      if (Shelly_data.indexOf("true") > 0) {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, Shelly_data);
        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }
        power = doc["power"];                           // 0
        double reactive = doc["reactive"];              // 0
        double voltage = doc["voltage"];                // 239.96
        bool is_valid = doc["is_valid"];                // true
        double total = doc["total"];                    // 252
        double total_returned = doc["total_returned"];  // 0

        // Serial.println(power);
      }
    } else {
      Serial.println("Echec connexion Shelly");
      delay(10000);  // Attendez 10 secondes avant la prochaine lecture
    }
  } else {
    Serial.println("WiFi non connecté");
  }
}