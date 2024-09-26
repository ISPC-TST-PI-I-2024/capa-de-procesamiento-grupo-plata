#include <WiFi.h>
#include <HTTPClient.h>

// Definir las credenciales Wi-Fi
const char* ssid = "tu_SSID";
const char* password = "tu_PASSWORD";

// URL del servidor donde se envían los datos
const char* serverName = "https://api.gonaiot.com/plata/datos_dispositivos";

// Variables de prueba (simulando datos de sensores)
float temperatura = 24.5;  // Ejemplo de valor de temperatura
float humedad = 60.2;      // Ejemplo de valor de humedad

void setup() {
  // Inicializar la comunicación serie
  Serial.begin(115200);

  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Conectando a WiFi...");

  // Esperar a que se conecte al Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Intentando conectarse...");
  }

  Serial.println("Conectado a la red WiFi");
}

void loop() {
  // Verificar si está conectado a Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    // Crear una instancia HTTP
    HTTPClient http;

    // Configurar la URL del servidor
    http.begin(serverName);

    // Configurar el encabezado de la solicitud (JSON)
    http.addHeader("Content-Type", "application/json");

    // Crear los datos en formato JSON
    String httpRequestData = "{\"temperatura\":" + String(temperatura) + ", \"humedad\":" + String(humedad) + "}";

    // Enviar solicitud POST con los datos JSON
    int httpResponseCode = http.POST(httpRequestData);

    // Mostrar el código de respuesta
    if (httpResponseCode > 0) {
      String response = http.getString();  // Obtener la respuesta del servidor
      Serial.println(httpResponseCode);    // Mostrar el código de respuesta
      Serial.println(response);            // Mostrar el contenido de la respuesta
    } else {
      // Manejar errores si la solicitud falló
      Serial.print("Error en la solicitud POST: ");
      Serial.println(httpResponseCode);
    }

    // Terminar la conexión HTTP
    http.end();
  } else {
    Serial.println("Error en la conexión Wi-Fi");
  }

  // Esperar antes de la siguiente solicitud
  delay(10000);
}
