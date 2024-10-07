![caratula](../../../E%20assets/caratula_princ.jfif)

## UH2TK2: Implementar operaciones CRUD desde el ESP32
Para realizar operaciones CRUD desde un ESP32 hacia una API RESTful, se puede usar la biblioteca `HTTPClient` de Arduino para gestionar las solicitudes HTTP.

## Paso 1: GET desde el ESP32
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";
const char* apiEndpoint = "https://api.gonaiot.com/plata/datos_dispositivos/";
const char* apiKey = "plata";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }
  Serial.println("Conectado al WiFi!");

  // Ejecutar la operación GET
  HTTPClient http;
  http.begin(apiEndpoint);
  http.addHeader("X-API-KEY", apiKey);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("Respuesta:");
    Serial.println(payload);
  } else {
    Serial.print("Error en la solicitud GET: ");
    Serial.println(httpResponseCode);
  }

  http.end();  // Cerrar la conexión HTTP
}

void loop() {
  // No se necesita hacer nada en el loop para este ejemplo
}  
```  

## Paso 2: POST desde el ESP32
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";
const char* apiEndpoint = "https://api.gonaiot.com/plata/datos_dispositivos/";
const char* apiKey = "plata";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }
  Serial.println("Conectado al WiFi!");

  // Ejecutar la operación POST
  HTTPClient http;
  http.begin(apiEndpoint);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-KEY", apiKey);

  // JSON de ejemplo con los datos a enviar
  String postData = "{\"id_dispositivo\": 1, \"fecha_recoleccion\": \"2024-09-20 14:00:00\", \"valor\": 23.5, \"unidad\": \"Celsius\"}";

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta POST:");
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();  // Cerrar la conexión HTTP
}

void loop() {
  // No se necesita hacer nada en el loop para este ejemplo
}  
```  

## Paso 3: PUT desde el ESP32
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";
const char* apiEndpoint = "https://api.gonaiot.com/plata/datos_dispositivos/1";  // URL con el ID del recurso
const char* apiKey = "plata";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }
  Serial.println("Conectado al WiFi!");

  // Ejecutar la operación PUT
  HTTPClient http;
  http.begin(apiEndpoint);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-KEY", apiKey);

  // JSON con los datos actualizados
  String putData = "{\"id_dispositivo\": 1, \"fecha_recoleccion\": \"2024-09-20 16:00:00\", \"valor\": 25.0, \"unidad\": \"Celsius\"}";

  int httpResponseCode = http.PUT(putData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta PUT:");
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud PUT: ");
    Serial.println(httpResponseCode);
  }

  http.end();  // Cerrar la conexión HTTP
}

void loop() {
  // No se necesita hacer nada en el loop para este ejemplo
}  
```  

## Paso 4: DELETE desde el ESP32
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";
const char* apiEndpoint = "https://api.gonaiot.com/plata/datos_dispositivos/1";  // URL con el ID del recurso
const char* apiKey = "plata";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }
  Serial.println("Conectado al WiFi!");

  // Ejecutar la operación DELETE
  HTTPClient http;
  http.begin(apiEndpoint);
  http.addHeader("X-API-KEY", apiKey);

  int httpResponseCode = http.sendRequest("DELETE");

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta DELETE:");
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud DELETE: ");
    Serial.println(httpResponseCode);
  }

  http.end();  // Cerrar la conexión HTTP
}

void loop() {
  // No se necesita hacer nada en el loop para este ejemplo
}
```  
Con estos ejemplos de codigo se puede probar la conexion hacia la API y comprobar o corregir su funcionamiento.