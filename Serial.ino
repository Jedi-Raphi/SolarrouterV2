void menu() {
  if (Serial.available() > 0) {
    int readchar = Serial.read();
    switch (readchar) {
      case '1':
        powerPercentage += 5;
        break;
      case '2':
        powerPercentage += 1;
        break;
      case '3':
        powerPercentage += 0.5;
        break;
      case '4':
        powerPercentage += 0.1;
        break;
      case '5':
        powerPercentage += 0.01;
        break;
      case '6':
        powerPercentage -= 0.01;
        break;
      case '7':
        powerPercentage -= 0.1;
        break;
      case '8':
        powerPercentage -= 0.5;
        break;
      case '9':
        powerPercentage -= 1;
        break;
      case '0':
        powerPercentage -= 5;
        break;
      default: break;
    }
    Serial.print("powerPercentage :");
    Serial.println(powerPercentage);
    Serial.println("1 +5");
    Serial.println("2 +1");
    Serial.println("3 +0.5");
    Serial.println("4 +0.1");
    Serial.println("5 +0.01");
    Serial.println("6 -0.01");
    Serial.println("7 -0.1");
    Serial.println("8 -0.5");
    Serial.println("9 -1");
    Serial.println("0 -5");
    Serial.println();
    if (powerPercentage > 100) {
      powerPercentage = 100;
    }
    if (powerPercentage < 0) {
      powerPercentage = 0;
    }
    wait_time = powerPercentage_to_wait(powerPercentage);
  }
}