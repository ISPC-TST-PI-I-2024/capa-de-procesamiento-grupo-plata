#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Definir las credenciales Wi-Fi
const char* ssid = "Tu_SSID";
const char* password = "Tu_CONTRASEÑA";

// URL de la API
const char* serverName = "https://api.gonaiot.com/plata/datos_dispositivos";

// Inicializar el sensor BMP280
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  
  // Conectar a Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  // Inicializar BMP280
  if (!bmp.begin(0x76)) { // 0x76 es la dirección I2C predeterminada del BMP280
    Serial.println("Error al inicializar BMP280");
    while (1);
  }
}

void loop() {
  // Leer presión y temperatura del BMP280
  float temperatura = bmp.readTemperature();
  float presion = bmp.readPressure() / 100.0F; // Convertir a hPa

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Presión: ");
  Serial.print(presion);
  Serial.println(" hPa");

  // Enviar datos a la API
  sendData(temperatura, presion);

  delay(60000); // Esperar 1 minuto antes de la próxima lectura
}

void sendData(float temp, float press) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Formato JSON
    String jsonPayload = "{\"sensor\":\"bmp280\",\"temperatura\":" + String(temp) + ",\"presion\":" + String(press) + "}";

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error en la conexión: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error en la conexión WiFi");
  }
}

