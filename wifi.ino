void handleRoot() {
  String Spercent = server.arg(0);
  percent = Spercent.toFloat();
   wait_time = Percent_to_wait(percent);
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  html += ".button2 { background-color: #555555; }</style></head>";
  html += "<body><p>test ";
  html += percent;
  html += " %<p>";

  html += "</body></html>";
  server.send(200, "text/html", html);
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

