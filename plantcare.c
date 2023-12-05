#include <avr/io.h>
#include <util/delay.h>

// Define pin numbers
#define MOISTURE_SENSOR_PIN 0 // A0 
#define WATER_LEVEL_SENSOR_PIN 5 // A5 

// Define threshold values
#define EMPTY_WATER_CONTAINER_THRESHOLD 300
#define FULL_WATER_CONTAINER_THRESHOLD 600
#define MOISTURE_THRESHOLD 970

#define BLUETOOTH_TX_PIN 1 // TX pin of Bluetooth module connected to Arduino's RX (D1)
#define BLUETOOTH_RX_PIN 0 // RX pin of Bluetooth module connected to Arduino's TX (D0)

// Pump control pins
#define PUMP_CONTROL_PIN 7

void setup() {
  Serial.begin(9600);
  pinMode(BLUETOOTH_TX_PIN, OUTPUT);
  pinMode(BLUETOOTH_RX_PIN, INPUT);
  pinMode(PUMP_CONTROL_PIN, OUTPUT);
}

void loop() {
  int moistureReading = readSensor();
  bool notEnoughWater = false;
  unsigned int waterLevelReading = analogRead(WATER_LEVEL_SENSOR_PIN);

  Serial.println(moistureReading);

  if (moistureReading > MOISTURE_THRESHOLD) {
    if (waterLevelReading <= EMPTY_WATER_CONTAINER_THRESHOLD) {
      digitalWrite(PUMP_CONTROL_PIN, HIGH);
      sendBluetoothSignal("No water!"); 
      _delay_ms(1000);
      digitalWrite(PUMP_CONTROL_PIN, LOW);
      _delay_ms(1000);
    } else {
    
      int waterToPump = receiveBluetoothSignal();
      if (waterToPump > 0) {
        digitalWrite(PUMP_CONTROL_PIN, HIGH);
        _delay_ms(waterToPump * 40); 
        digitalWrite(PUMP_CONTROL_PIN, LOW);
        _delay_ms(1000);
      }
    }
  } else {
    sendBluetoothSignal("Plant needs water!");
    _delay_ms(5000); 
  }
}

// This function returns the analog soil moisture measurement
int readSensor() {
  _delay_ms(10); 
  ADMUX = (1 << REFS0) | MOISTURE_SENSOR_PIN; 
  ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
  while (ADCSRA & (1 << ADSC)); 
  int val = ADC; 
  return val; 
}

void sendBluetoothSignal(const char* message) {
  for (int i = 0; message[i] != '\0'; i++) {
    Serial.write(message[i]);
    while (!(UCSR0A & (1 << UDRE0))); 
  }
  Serial.write('\n'); 
  while (!(UCSR0A & (1 << UDRE0))); 
}

int receiveBluetoothSignal() {
  char receivedChar;
  int waterToPump = 0;
  
  while (Serial.available() > 0) {
    receivedChar = Serial.read();
    if (receivedChar >= '0' && receivedChar <= '9') {
      waterToPump = waterToPump * 10 + (receivedChar - '0');
    }
  }

  return waterToPump;
}