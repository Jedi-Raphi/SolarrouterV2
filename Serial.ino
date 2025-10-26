void menu() {  // utile pour simuler valeurs pour les tests
  if (Serial.available() > 0) {
    int readchar = Serial.read();
    switch (readchar) {
      case '1':
        Temperature += 5;
        break;
      case '2':
        Temperature += 1;
        break;
      case '3':
        Temperature += 0.5;
        break;
      case '4':
        Temperature += 0.1;
        break;
      case '5':
        Temperature += 0.01;
        break;
      case '6':
        Temperature -= 0.01;
        break;
      case '7':
        Temperature -= 0.1;
        break;
      case '8':
        Temperature -= 0.5;
        break;
      case '9':
        Temperature -= 1;
        break;
      case '0':
        Temperature -= 5;
        break;
      default: break;
    }
    Serial.print("Temperature :");
    Serial.println(Temperature);
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
    if (Temperature > 100) {
      Temperature = 100;
    }
    if (Temperature < 0) {
      Temperature = 0;
    }
  }
}