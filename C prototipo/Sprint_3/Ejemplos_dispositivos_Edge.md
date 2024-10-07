# Ejemplos de Interacciones desde los Dispositivos Edge

En esta sección se presentan ejemplos prácticos de cómo los dispositivos Edge, específicamente los ESP32, interactúan con el middleware. 
Estos ejemplos incluyen el envío de datos al middleware y la recepción de respuestas para asegurar una comunicación efectiva y segura.


### 1. Envío de Datos desde un ESP32 al Middleware

A continuación, se muestra un ejemplo de cómo un dispositivo ESP32 puede enviar datos de calidad del aire al middleware utilizando HTTP POST.


- **Código de Ejemplo en Arduino (ESP32)**:

    ```cpp
    #include <WiFi.h>
    #include <HTTPClient.h>
    #include <ArduinoJson.h>
    
    // Configuración de la red WiFi
    const char* ssid = "SSID";
    const char* password = "PASSWORD";
    
    // URL del middleware
    const char* serverUrl = "http://dominio.com/data";
    
    // Credenciales para autenticación
    const char* username = "admin";
    const char* passwordAuth = "password";
    
    // Variables para almacenar el token JWT
    String jwtToken = "";
    
    // Función para obtener el token JWT
    String getJwtToken() {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(String(serverUrl) + "/login");
        http.addHeader("Content-Type", "application/json");
    
        // Crear el JSON de autenticación
        StaticJsonDocument<200> doc;
        doc["username"] = username;
        doc["password"] = passwordAuth;
        String requestBody;
        serializeJson(doc, requestBody);
    
        // Enviar la solicitud POST
        int httpResponseCode = http.POST(requestBody);
    
        if (httpResponseCode == 200) {
          String response = http.getString();
          StaticJsonDocument<200> responseDoc;
          deserializeJson(responseDoc, response);
          return responseDoc["access_token"].as<String>();
        } else {
          Serial.println("Error en la autenticación");
          return "";
        }
      }
      return "";
    }
    
    void setup() {
      Serial.begin(115200);
      WiFi.begin(ssid, passwordAuth);
    
      // Conexión a la red WiFi
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
      }
      Serial.println("Conectado a la red WiFi");
    
      // Obtener el token JWT
      jwtToken = getJwtToken();
      if (jwtToken != "") {
        Serial.println("Token JWT obtenido exitosamente");
      }
    }
    
    void loop() {
      if (WiFi.status() == WL_CONNECTED && jwtToken != "") {
        HTTPClient http;
        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer " + jwtToken);
    
        // Crear el JSON de datos
        StaticJsonDocument<500> doc;
        doc["id_dispositivo"] = 1;
        doc["fecha_recoleccion"] = "2024-10-06 15:30:00";
        JsonArray mediciones = doc.createNestedArray("mediciones");
        mediciones.add({{"valor", 25.5}, {"unidad", "C"}});
        mediciones.add({{"valor", 65.2}, {"unidad", "%"}});
        mediciones.add({{"valor", 1013.25}, {"unidad", "hPa"}});
    
        String requestBody;
        serializeJson(doc, requestBody);
    
        // Enviar la solicitud POST con los datos
        int httpResponseCode = http.POST(requestBody);
    
        if (httpResponseCode > 0) {
          String response = http.getString();
          Serial.println("Respuesta del servidor: " + response);
        } else {
          Serial.println("Error en el envío de datos");
        }
    
        http.end();
      }
    
      // Esperar 10 minutos antes de enviar nuevos datos
      delay(600000);
    }
    ```

### Explicación del Código

1. **Conexión a la Red WiFi**: El ESP32 se conecta a la red WiFi especificada utilizando las credenciales proporcionadas.

2. **Autenticación**: Se realiza una solicitud POST a la ruta `/login` del middleware para obtener un token JWT válido. Este token se utiliza para autenticar las solicitudes posteriores.

3. **Envío de Datos**: Una vez obtenido el token, el ESP32 construye un JSON con los datos de calidad del aire y lo envía a la ruta `/data` del middleware, incluyendo el token JWT en el encabezado `Authorization`.

4. **Manejo de Respuestas**: El ESP32 maneja las respuestas del servidor, imprimiendo mensajes de éxito o error según corresponda.

# 2. Recepción de Confirmación desde el Middleware

Después de enviar los datos, el middleware puede responder con una confirmación de recepción o con información adicional. A continuación, se muestra cómo manejar la respuesta en el ESP32.

#### Respuesta Exitosa del Middleware

```json
{
  "message": "Datos recibidos y procesados correctamente",
  "timestamp": "2024-10-06T15:30:05Z"
}
```
#### Ejemplo de Solicitud de Datos desde el Middleware al Dispositivo Edge

Aunque el flujo principal es que los dispositivos Edge envíen datos al middleware, también es posible que el middleware solicite datos adicionales al dispositivo Edge si es necesario.

## Endpoint en el Middleware para Solicitar Datos
```python
@app.route('/request_data/<int:id_dispositivo>', methods=['GET'])
@jwt_required()
def request_data(id_dispositivo):
    # Lógica para solicitar datos al dispositivo Edge
    # Esto podría implicar enviar una señal al dispositivo para que envíe datos adicionales
    return jsonify({"message": "Solicitud de datos enviada al dispositivo Edge"}), 200
```
## Código de Ejemplo en el ESP32 para Escuchar Solicitudes

// Suponiendo que el ESP32 tiene un servidor HTTP para recibir solicitudes del middleware
```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

WebServer server(80);

// Función para manejar la solicitud de datos
void handleRequestData() {
  // Recopilar datos adicionales si es necesario
  StaticJsonDocument<200> doc;
  doc["id_dispositivo"] = 1;
  doc["fecha_recoleccion"] = "2024-10-06 15:35:00";
  JsonArray mediciones = doc.createNestedArray("mediciones");
  mediciones.add({{"valor", 26.0}, {"unidad", "C"}});
  mediciones.add({{"valor", 64.8}, {"unidad", "%"}});
  mediciones.add({{"valor", 1012.50}, {"unidad", "hPa"}});

  String responseBody;
  serializeJson(doc, responseBody);

  // Enviar la respuesta al middleware
  server.send(200, "application/json", responseBody);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, passwordAuth);

  // Conexión a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a la red WiFi");

  // Configurar el servidor para manejar la ruta de solicitud de datos
  server.on("/request_data", HTTP_GET, handleRequestData);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}
```

## Explicación del Código
Servidor HTTP en el ESP32: El ESP32 actúa como un servidor HTTP que escucha en el puerto 80 para recibir solicitudes del middleware.

Manejo de Solicitudes: Cuando el middleware solicita datos adicionales mediante una solicitud GET a /request_data/<id_dispositivo>, el ESP32 recopila los datos necesarios y los envía de vuelta en formato JSON.

