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
    const char* ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = -3;  // Ajusta según tu zona horaria
    const int daylightOffset_sec = 0;

  public:
    // Constructor para inicializar las credenciales WiFi y la API
    SensorDataAPI(const char* ssid, const char* password, const char* apiEndpoint, const char* apiKey) {
      this->ssid = ssid;
      this->password = password;
      this->apiEndpoint = apiEndpoint;
      this->apiKey = apiKey;
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

    // Método para enviar los datos a la API RESTful
    void sendData(float temperature, float humidity, float pressure, float gasConcentration, int id_dispositivo) {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Configuración de la URL
        http.begin(apiEndpoint);

        // Headers
        http.addHeader("Content-Type", "application/json");
        http.addHeader("X-API-KEY", apiKey);

        // Obtener el timestamp actual
        String timestamp = getTimestamp();

        // Enviar las solicitudes POST con el mismo timestamp para cada sensor
        String postDataTemp = "{\"id_dispositivo\": " + String(id_dispositivo) +
                              ", \"fecha_recoleccion\": \"" + timestamp + 
                              "\", \"valor\": " + String(temperature) + 
                              ", \"unidad\": \"Celsius\"}";
        sendRequest(postDataTemp, http);

        String postDataHumidity = "{\"id_dispositivo\": " + String(id_dispositivo) +
                                  ", \"fecha_recoleccion\": \"" + timestamp + 
                                  "\", \"valor\": " + String(humidity) + 
                                  ", \"unidad\": \"%\"}";
        sendRequest(postDataHumidity, http);

        String postDataPressure = "{\"id_dispositivo\": " + String(id_dispositivo) +
                                  ", \"fecha_recoleccion\": \"" + timestamp + 
                                  "\", \"valor\": " + String(pressure) + 
                                  ", \"unidad\": \"hPa\"}";
        sendRequest(postDataPressure, http);

        String postDataGas = "{\"id_dispositivo\": " + String(id_dispositivo) +
                             ", \"fecha_recoleccion\": \"" + timestamp + 
                             "\", \"valor\": " + String(gasConcentration) + 
                             ", \"unidad\": \"PPM\"}";
        sendRequest(postDataGas, http);

        http.end();  // Cerrar la conexión HTTP
      } else {
        Serial.println("Error: No hay conexión WiFi");
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
