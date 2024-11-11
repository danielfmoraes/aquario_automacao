#include <Servo.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>

// Definições dos pinos
#define SERVO_PIN 9
#define RELAY_PIN 7
#define DHT_PIN 2
#define DHT_TYPE DHT11
#define BUTTON_PIN 3

// Inicializações
Servo myServo;
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Variáveis de contagem
int feedCount = 0;
unsigned long lastFeedTime = 0;
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Acionamento inicial do relé (luz do aquário)
  digitalWrite(RELAY_PIN, LOW);
  feedCount = 0;

  // Inicializa o tempo
  setTime(8, 0, 0, 1, 1, 2023);  // Defina a hora inicial (HH, MM, SS, DD, MM, YYYY)
  startTime = now();  // Armazena o tempo inicial
}

void loop() {
  unsigned long currentTime = now();

  // Alimentação programada às 8h
  if (hour() == 8 && minute() == 0 && second() < 10 && currentTime - lastFeedTime > 86400UL) {
    feed();
  }

  // Alimentação por botão
  if (digitalRead(BUTTON_PIN) == LOW) {
    feed();
    delay(1000);  // Debounce do botão
  }

  // Controle das luzes do aquário
  if (hour() >= 8 && hour() < 21) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  // Leitura de temperatura e umidade
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Atualização do display OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.setCursor(0, 10);
  display.print("Hum: ");
  display.print(humidity);
  display.print(" %");
  display.setCursor(0, 20);
  display.print("Feeds: ");
  display.print(feedCount);
  display.display();

  delay(2000);  // Atraso para evitar sobrecarga da tela
}

// Função de alimentação
void feed() {
  myServo.write(90);  // Girar para 90 graus
  delay(1000);        // Esperar 1 segundo
  myServo.write(0);   // Voltar à posição inicial
  feedCount++;
  lastFeedTime = now();
}
