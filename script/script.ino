#include <M5StickCPlus2.h>
#include <Wire.h>
#include <SPI.h>
#include <ESP32Servo.h> // Use the ESP32-compatible Servo library

#define SERVO_PIN 26 // Pino do Servo

Servo servo;
int feedCount = 0; // Contador de alimentações
unsigned long lastFeedTime = 0;
unsigned long startTime = 0;

void setup() {
  M5.begin();
  Wire.begin();
  SPI.begin();
  servo.attach(SERVO_PIN);

  M5.Lcd.clear();
  M5.Lcd.println("Iniciado");

  startTime = millis(); // Registrar o tempo de início
}

void loop() {
  // Calcular o tempo desde o início
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;

  // Calcular horas, minutos e segundos desde o início
  int hours = (elapsedTime / 3600000) % 24;
  int minutes = (elapsedTime / 60000) % 60;
  int seconds = (elapsedTime / 1000) % 60;

  // Acionar o servo ao pressionar o botão A
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.setCursor(0, 40);
    M5.Lcd.println("Servo acionado");
    servo.write(90); // Girar para 90 graus
    delay(1000); // Esperar 1 segundo
    servo.write(0); // Voltar à posição inicial

    // Incrementar o contador de alimentações
    feedCount++;
    lastFeedTime = millis();
  }

  // Exibir a contagem de alimentações na tela
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Alimentacoes hoje: %d", feedCount);

  // Zerando a contagem de alimentações a cada 24 horas
  if (hours == 0 && minutes == 0 && seconds < 10 && millis() - lastFeedTime > 10000) {
    feedCount = 0;
    M5.Lcd.setCursor(0, 80);
    M5.Lcd.println("Contagem zerada");
  }

  // Atualizar o display do M5StickCPlus2 com o horário desde o início
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Tempo: %02d:%02d:%02d", hours, minutes, seconds);

  // Atualizar o estado do botão
  M5.update();
  delay(100); // Pequeno atraso para evitar leitura múltipla do botão
}
