
void handleRoot() {
  if (server.arg("API_KEY") == api_key) {
    if (server.hasArg("powerPercentage")) {
      String pwrPercStr = server.arg("powerPercentage");
      if (String(pwrPercStr.toFloat()) = pwrPercStr) {
        powerPercentage = pwrPercStr.toFloat();
        wait_time = powerPercentage_to_wait(powerPercentage);
      }
    }


    String html = "<!DOCTYPE html><html><head> <meta name=\"color-scheme\" content=\"light dark\" /></head>";
    html += "<body><p>";
    html += "{\"cod\": 200\", \"powerPercentage\": ";
    html += powerPercentage;
    html += ", \"Tank_Temperature\": ";
    html += Temperature;
    html += "}";
    html += "</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  } else {
    String html = "<!DOCTYPE html><html><head> <meta name=\"color-scheme\" content=\"light dark\" /></head>";
    html += "<body><p>";
    html += "{\"cod\": 401\", \"message\": \"invalid api key\"}";
    html += "</p>";
    html += "</body></html>";
    server.send(401, "text/html", html);
  }
}


void Wifibegin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(Secret_ssid, Secret_password);
  Serial.println("\nConnecting to WiFi Network ..");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");


  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
