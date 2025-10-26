void menu() {
  if (Serial.available() > 0) {
    int readchar = Serial.read();
    switch (readchar) {
      case '1':
        percent += 5;
        break;
      case '2':
        percent += 1;
        break;
      case '3':
        percent += 0.5;
        break;
      case '4':
        percent += 0.1;
        break;
      case '5':
        percent += 0.01;
        break;
      case '6':
        percent -= 0.01;
        break;
      case '7':
        percent -= 0.1;
        break;
      case '8':
        percent -= 0.5;
        break;
      case '9':
        percent -= 1;
        break;
      case '0':
        percent -= 5;
        break;
      default: break;
    }
    Serial.print("percent :");
    Serial.println(percent);
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
    if (percent > 100) {
      percent = 100;
    }
    if (percent < 0) {
      percent = 0;
    }
    wait_time = Percent_to_wait(percent);
  }
}