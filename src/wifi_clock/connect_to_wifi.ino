void connectToWiFi() {
  wifiManager.setDebugOutput(true);

  // по каким-то условиям, понадобится сбрасывать настройки
  // пока не знаю по каким
  if (false) {
    wifiManager.resetSettings();
  }

  wifiManager.autoConnect(AC_SSID, AC_PASS);
  clock_ip = WiFi.localIP().toString();

//  Serial.print("Connected! IP address: ");
//  Serial.println(clock_ip);
}
