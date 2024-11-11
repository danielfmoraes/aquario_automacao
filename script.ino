#include <M5StickC.h>
#include <Wire.h>
#include "RTClib.h"

// Defina o pino do relé
#define RELAY_PIN 26

RTC_DS3231 rtc;

void setup() {
  M5.begin();
  Wire.begin();
  
  // Configurar o pino do relé como saída
  pinMode(RELAY_PIN, OUTPUT);

  if (!rtc.begin()) {
    M5.Lcd.print("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    M5.Lcd.print("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  
  // Ligar a luz às 8h e desligar às 21h
  if (now.hour() >= 8 && now.hour() < 21) {
    digitalWrite(RELAY_PIN, HIGH); // Liga o relé
  } else {
    digitalWrite(RELAY_PIN, LOW); // Desliga o relé
  }

  // Atualizar o display do M5StickCPlus2 com o horário atual
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Hora atual: %02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  delay(1000); // Esperar um segundo antes de verificar novamente
}
