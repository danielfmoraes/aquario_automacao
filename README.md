# Autmoação em Aquario com Arduino
 Automação de alimentação e luzes do aquario com arduino.
Neste projeto está sendo considerado os seguintes sensores:
- Uno R3
- Micro Servo
- Relay SRD-05VDC-SL-C
- Temp and Humidity DHT11
- Button
- Display LCD OLED 12c

## Utilização

- Com o micro servo realizar a alimentação todo dia com hora marcada e possibilidade com Button de alimentação fora do horario
- Leitor de humidade e temperatura para compreensão do parametros ambientais
- Utilização do Relay para acionamento e desligamento da luz do aquario
- 
## Esquema
| Sensor | Data | SCL | SDA |
| ------ | ------ | ------ | ------ |
|Micro Servo| Pin 9|
|Relay|Pin 7|
|DHT Temperatura & Humidt|Pin2|
|Display||A5|A4|
|Button|Pin3



