#include <Arduino.h>

const int ledPin = 2;  // Pin donde está conectado el LED
bool ledState = false; // Estado inicial del LED (apagado)

void setup() {
    // Configurar el pin del LED como salida
    pinMode(ledPin, OUTPUT);

    // Configurar la comunicación serial
    Serial.begin(115200);
}

void loop() {
    // Cambiar el estado del LED
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    // Si el LED está encendido, mostrar el mensaje "GRUPO PLATA"
    if (ledState) {
        Serial.println("GRUPO PLATA");
    }

    // Esperar 1 segundo antes de cambiar el estado del LED
    delay(1000);
}
