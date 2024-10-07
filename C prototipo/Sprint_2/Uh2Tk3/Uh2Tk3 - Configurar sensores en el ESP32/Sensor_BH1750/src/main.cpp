#include <Wire.h>
#include <BH1750.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Definir las credenciales Wi-Fi
const char* ssid = "Tu_SSID";
const char* password = "Tu_CONTRASEÑA";

// URL de la API
const char* serverName = "https://api.gonaiot.com/plata/datos_dispositivos";

// Inicializar el sensor BH1750
BH1750 lightMeter;

void setup() {
  Serial.begin(115200);

  // Conectar a Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  // Inicializar BH1750
  Wire.begin();
  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Error al inicializar BH1750");
    while (1);
  } else {
    Serial.println("BH1750 iniciado correctamente");
  }
}

void loop() {
  // Leer intensidad de luz en lux
  float lux = lightMeter.readLightLevel();

  Serial.print("Intensidad de luz: ");
  Serial.print(lux);
  Serial.println(" lx");

  // Enviar datos a la API
  sendData(lux);

  delay(60000); // Esperar 1 minuto antes de la próxima lectura
}

void sendData(float lux) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Formato JSON
    String jsonPayload = "{\"sensor\":\"bh1750\",\"intensidad_luz\":" + String(lux) + "}";

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
