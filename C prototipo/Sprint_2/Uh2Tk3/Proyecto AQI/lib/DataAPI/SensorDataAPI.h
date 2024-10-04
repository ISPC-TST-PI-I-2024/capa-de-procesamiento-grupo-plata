#ifndef SENSOR_DATA_API_H
#define SENSOR_DATA_API_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

class SensorDataAPI {
  private:
    const char* ssid;
    const char* password;
    const char* apiEndpoint;
    const char* apiKey;
    const char* loginEndpoint;
    const char* username;
    const char* userPassword;
    String jwtToken;  // Almacenar el token JWT
    const char* ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = -3;  // Ajusta según tu zona horaria
    const int daylightOffset_sec = 0;

  public:
    // Constructor para inicializar las credenciales WiFi y la API
    SensorDataAPI(const char* ssid, const char* password, const char* apiEndpoint, const char* loginEndpoint, const char* apiKey, const char* username, const char* userPassword) {
      this->ssid = ssid;
      this->password = password;
      this->apiEndpoint = apiEndpoint;
      this->loginEndpoint = loginEndpoint;
      this->apiKey = apiKey;
      this->username = username;
      this->userPassword = userPassword;
    }

    // Método para conectar a la red WiFi
    void connectWiFi() {
      WiFi.begin(ssid, password);
      Serial.print("Conectando al WiFi");
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
      }
      Serial.println("\nConectado al WiFi!");

      // Configurar el servidor NTP para sincronizar el tiempo
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      delay(2000);  // Esperar unos segundos para sincronizar el tiempo
    }

    // Método para obtener el token JWT
    bool getAuthToken() {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(loginEndpoint);
        http.addHeader("Content-Type", "application/json");
        // Establecer timeout de 30 segundos
        http.setTimeout(30000); 

        String postData = "{\"username\": \"" + String(username) + "\", \"password\": \"" + String(userPassword) + "\"}";

        int httpResponseCode = http.POST(postData);

        if (httpResponseCode == 200) {
          String response = http.getString();
          Serial.print("Respuesta POST (HTTP ");
          Serial.print(httpResponseCode);
          Serial.println("):");
          Serial.println(response);

          // Extraer el token del JSON de respuesta
          int tokenStart = response.indexOf("access_token\":\"") + 15;
          int tokenEnd = response.indexOf("\"", tokenStart);
          jwtToken = response.substring(tokenStart, tokenEnd);
          
          http.end();
          return true;
        } else {
          Serial.print("Error en la solicitud de token: ");
          Serial.println(httpResponseCode);

          http.end();
          return false;
        }
      } else {
        Serial.println("Error: No hay conexión WiFi");
        return false;
      }
    }

    // Método para obtener el timestamp actual
    String getTimestamp() {
      struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) {
        Serial.println("Fallo al obtener tiempo, usando fecha por defecto.");
        return "2024-01-01 00:00:00";  // Valor por defecto si falla
      }
      
      char timeStringBuff[20];  // Tamaño suficiente para "YYYY-MM-DD HH:MM:SS"
      strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
      return String(timeStringBuff);
    }

    // Método para enviar los datos a través del middleware
    void sendData(float temperature, float humidity, float pressure, float gasConcentration, int id_dispositivo) {
      if (WiFi.status() == WL_CONNECTED && !jwtToken.isEmpty()) {
        HTTPClient http;

        // Configuración de la URL
        http.begin(apiEndpoint);
       
        // Headers
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer " + jwtToken);
        http.addHeader("X-API-KEY", apiKey);

        // Establecer timeout de 30 segundos
        http.setTimeout(30000);  

        // Obtener el timestamp actual
        String timestamp = getTimestamp();

        // Crear el JSON con todas las mediciones en una sola solicitud
        String postData = "{\"id_dispositivo\": " + String(id_dispositivo) +
                          ", \"fecha_recoleccion\": \"" + timestamp + 
                          "\", \"mediciones\": ["
                          "{\"valor\": " + String(temperature) + ", \"unidad\": \"Celsius\"}, "
                          "{\"valor\": " + String(humidity) + ", \"unidad\": \"%\"}, "
                          "{\"valor\": " + String(pressure) + ", \"unidad\": \"hPa\"}, "
                          "{\"valor\": " + String(gasConcentration) + ", \"unidad\": \"PPM\"}"
                          "]}";

        // Enviar la solicitud POST
        sendRequest(postData, http);

        http.end();  // Cerrar la conexión HTTP
      } else {
        Serial.println("Error: No hay conexión WiFi o no se ha obtenido el token JWT");
      }
    }

  private:
    // Función auxiliar para enviar las solicitudes POST
    void sendRequest(String postData, HTTPClient &http) {
      int httpResponseCode = http.POST(postData);

      Serial.println("Enviando datos: ");
      Serial.println(postData);
      
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("Respuesta POST (HTTP ");
        Serial.print(httpResponseCode);
        Serial.println("):");
        Serial.println(response);
      } else {
        Serial.print("Error en la solicitud POST: ");
        Serial.println(httpResponseCode);
      }
    }
};

#endif
