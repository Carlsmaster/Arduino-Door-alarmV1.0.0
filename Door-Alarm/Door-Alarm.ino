/*
Simple Door alarm V1.0.0
Overview
This Arduino Door Alarm project is designed to enhance security by providing a simple and effective solution for monitoring doors. 
The alarm system detects door openings and triggers an alert, making it suitable for home security applications.
Hardware Requirements
Arduino Board
Magnetic Contact Sensor
Buzzer/Alarm Module
LED Indicator
Resistors and Wiring

Usage:
1. Connect a switch/button to the input GPIO pin.
2. Connect an LED to the output GPIO pin via a current-limiting resistor.
3. Run this script to read the input state and toggle the output state.

Note: Adjust  pin numbers according to your hardware configuration.

Author: [Eduardo Valdez]*/


// Incluye las librerías necesarias
#include <Arduino.h>

// Define los pines a utilizar
const int sensorPin = 15;    // Pin donde está conectado el sensor de estado
const int buzzerPin = 12;    // Pin donde está conectado el buzzer

// Variable para rastrear si el buzzer está sonando
bool isBuzzerSounding = false;

void setup() {
  pinMode(sensorPin, INPUT); // Configura el pin del sensor como entrada con resistencia pull-up interna
  pinMode(buzzerPin, OUTPUT);       // Configura el pin del buzzer como salida
}

// Función para activar el buzzer durante un tiempo específico
void activateBuzzer() {
  isBuzzerSounding = true;  // Marca el buzzer como sonando
  digitalWrite(buzzerPin, HIGH); // Activa el buzzer
  delay(100);                   // Pequeño retardo entre pitidos
  digitalWrite(buzzerPin, LOW);  // Desactiva el buzzer
  delay(100);                   // Pequeño retardo entre pitidos
  isBuzzerSounding = false; // Marca el buzzer como no sonando
}

void loop() {
  // Lee el estado actual del sensor (recuerda que es lógica inversa)
  int currentSensorState = !digitalRead(sensorPin);

  // Si la puerta se abre (se detecta un cambio de 1 a 0 en el sensor)
  if (currentSensorState == LOW) {
    if (!isBuzzerSounding) {
      activateBuzzer(); // Activa el buzzer si no está sonando actualmente
    }
  } else {
    // Si la puerta se cierra (se detecta un cambio de 0 a 1 en el sensor)
    if (isBuzzerSounding) {
      // Si la puerta se cerró mientras el buzzer estaba sonando, detén el sonido
      digitalWrite(buzzerPin, LOW);
      isBuzzerSounding = false; // Marca el buzzer como no sonando
    }
  }

  // Puedes agregar otras acciones o lógica en tu programa aquí
}
