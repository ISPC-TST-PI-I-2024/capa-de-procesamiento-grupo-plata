#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Credenciales Wi-Fi
const char* ssid = "tu_SSID";
const char* password = "tu_password";

// Dirección de la API
const char* serverName = "https://api.gonaiot.com/plata/datos_dispositivos";

// Instancia del sensor AM2320
Adafruit_AM2320 am2320 = Adafruit_AM2320();

void setup() {
  // Iniciar el monitor serie
  Serial.begin(115200);

  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a la red Wi-Fi");

  // Iniciar el sensor
  if (!am2320.begin()) {
    Serial.println("No se pudo encontrar el sensor AM2320");
    while (1);
  }
}

void loop() {
  // Leer la temperatura y la humedad del sensor AM2320
  float temperature = am2320.readTemperature();
  float humidity = am2320.readHumidity();

  // Verificar si la lectura fue correcta
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error al leer el sensor AM2320");
    return;
  }

  // Imprimir los valores en el monitor serie
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Enviar los datos a la API
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Crear URL para la solicitud
    http.begin(serverName);

    // Crear el cuerpo de la solicitud con los datos
    String httpRequestData = "{\"temperatura\":" + String(temperature) + ", \"humedad\":" + String(humidity) + "}";
    http.addHeader("Content-Type", "application/json");

    // Enviar solicitud POST
    int httpResponseCode = http.POST(httpRequestData);

    // Imprimir el código de respuesta
    if (httpResponseCode > 0) {
      Serial.print("Código de respuesta HTTP: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error en la solicitud: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    // Cerrar la conexión
    http.end();
  } else {
    Serial.println("Error en la conexión Wi-Fi");
  }

  // Esperar antes de la siguiente lectura
  delay(10000);  // Esperar 10 segundos entre lecturas
}
