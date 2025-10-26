#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

WebServer server(80);


// def des Pin digitaux
const int Pin_ZC = 21, Pin_Trig = 23;
// marge Triac
const int marge_min = 400, marge_max = 10000 - 400;  // marge pour le declenchement du triac en us
//------------Interuptions------------//
// Timer interupt trig
hw_timer_t* Timer_Trig_on = NULL;   //creation compteur pour l'allumage
hw_timer_t* Timer_Trig_off = NULL;  //creation compteur pour l'extinction
void IRAM_ATTR Timer_Trig_on_ISR() {
  digitalWrite(Pin_Trig, HIGH);                // allumer trig
  timerRestart(Timer_Trig_off);                // preparer compteur pour l'extinction
  timerAlarm(Timer_Trig_off, 1000, false, 3);  // eteindre apres 1 000 cycles : 1000 / 10 MHz = 100us
}
void IRAM_ATTR Timer_Trig_off_ISR() {
  digitalWrite(Pin_Trig, LOW);  // allumer trig
}
// interupt ZC
int wait_time = 10000;
unsigned long ZC = 0;
void IRAM_ATTR zeroCrossing() {
  if (micros() - ZC > 2000) {            //debounce du ZC
    if (wait_time < marge_min) {         //Si temps d'attente trop proche limte (tot)
      digitalWrite(Pin_Trig, HIGH);      // laisser Trig allumé
    } else if (wait_time > marge_max) {  //Si temps d'attente trop proche limte (tardive)
      digitalWrite(Pin_Trig, LOW);       // laisser Trig eteint
    } else {
      timerRestart(Timer_Trig_on);                          // preparer compteur pour le delay
      timerAlarm(Timer_Trig_on, wait_time * 10, false, 3);  // eteindre apres wait_time x10 cycles : wait_time * 10 / 10 MHz = wait_time (en us)
    }
    ZC = micros();  //debounce du ZC
  }
}
//------------Fin Interuptions------------//

//------------int------------//
void setup() {
  Serial.begin(115200);  //debuter la com série
  pinMode(Pin_Trig, OUTPUT);
  pinMode(Pin_ZC, INPUT_PULLUP);

  Wifibegin();
  Timer_Trig_on = timerBegin(10000000);  // demarage compteurs
  Timer_Trig_off = timerBegin(10000000);
  timerAttachInterrupt(Timer_Trig_on, &Timer_Trig_on_ISR);  // attacher compteurs aux fonction d'interuption
  timerAttachInterrupt(Timer_Trig_off, &Timer_Trig_off_ISR);
  attachInterrupt(digitalPinToInterrupt(Pin_ZC), zeroCrossing, RISING);
  //printMenu();
}
//------------Fin int------------//

double percent = 0.0;  //pourcentage de dump au demarrage
unsigned long last = 0;
void loop() {
  server.handleClient();
  menu();
}

//math:
int Percent_to_wait(double pers) {
  pers = max(min(pers, 100.0), 0.0);
  return arcos(pers / 50 - 1) / 3.1415 * 10000;
}
float arcos(float x) {
  float negate = float(x < 0);
  float ret = -0.0187293;
  x = abs(x);
  ret = x * -0.0187293;
  ret += 0.0742610;
  ret *= x;
  ret -= 0.2121144;
  ret *= x;
  ret += 1.5707288;
  ret *= sqrt(1.0 - x);
  ret = ret - 2.0 * negate * ret;
  return negate * 3.14159265358979 + ret;
}
