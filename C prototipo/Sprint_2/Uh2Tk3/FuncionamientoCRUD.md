![caratula](../../../E%20assets/caratula_princ.jfif)  

## Actividad:Crear la clase SensorDataAPI para el envío de datos
Diseño de la clase SensorDataAPI  

La clase SensorDataAPI se encargará de:

Gestionar la conexión WiFi.
Construir el JSON con los datos de los sensores.
Realizar las solicitudes POST a la API RESTful.
Manejar las respuestas del servidor.

```cpp  
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
    const long gmtOffset_sec = 0;  // Ajusta según tu zona horaria
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
  
```  
## Explicación de la Clase `SensorDataAPI`    
## Introducción
La clase `SensorDataAPI` está diseñada para gestionar la conexión WiFi, la sincronización de tiempo mediante NTP y el envío de datos de sensores a una API RESTful. Este documento describe el funcionamiento de la clase, sus métodos principales y la integración en un proyecto basado en el ESP32.

## Funcionamiento de la Clase `SensorDataAPI`

### **Encabezado de la Clase**
La clase incluye bibliotecas esenciales como `WiFi.h`, `HTTPClient.h`, y `time.h` para gestionar la conectividad y las solicitudes HTTP.

```cpp
#ifndef SENSOR_DATA_API_H
#define SENSOR_DATA_API_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>  
```  
## Variables Privadas
La clase define varias variables privadas:

* `ssid y password`: Las credenciales de WiFi.
* `apiEndpoint y apiKey`: La URL de la API y la clave de la API.
* `ntpServer, gmtOffset_sec, daylightOffset_sec`: Parámetros para la sincronización de tiempo mediante NTP.    

```cpp

class SensorDataAPI {
  private:
    const char* ssid;
    const char* password;
    const char* apiEndpoint;
    const char* apiKey;
    const char* ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = -3;  // Ajusta zona horaria para Argentina
    const int daylightOffset_sec = 0;  
```  
## Constructor
El constructor inicializa las credenciales WiFi y la configuración de la API.

```cpp

public:
    SensorDataAPI(const char* ssid, const char* password, const char* apiEndpoint, const char* apiKey) {
      this->ssid = ssid;
      this->password = password;
      this->apiEndpoint = apiEndpoint;
      this->apiKey = apiKey;
    }  
```  

## Método `connectWiFi()`
Este método conecta el ESP32 a la red WiFi y también configura el servidor NTP para sincronizar el tiempo. Si la conexión WiFi es exitosa, el ESP32 intenta sincronizar la hora mediante NTP.

```cpp

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
```  

## Método `getTimestamp()`
Este método obtiene la fecha y hora actuales desde el servidor NTP. Si la sincronización falla, retorna una fecha por defecto.

```cpp

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
```
## Método `sendData()`
Este método envía los datos de los sensores a la API RESTful. Se generan solicitudes POST individuales para cada medición (temperatura, humedad, presión y concentración de gases), todas agrupadas bajo el mismo timestamp.

```cpp

void sendData(float temperature, float humidity, float pressure, float gasConcentration, int id_dispositivo) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Configuración de la URL
    http.begin(apiEndpoint);

    // Desactivar redirecciones automáticas
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

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
```  

## Método `sendRequest()`
Este método auxiliar envía las solicitudes POST a la API y muestra los detalles en el monitor serial para facilitar la depuración.

```cpp

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
```  

## Cierre del Encabezado
Finalmente, se cierra la declaración del encabezado para evitar múltiples inclusiones.

```cpp

#endif  
```  
## Integración de la Clase `SensorDataAPI` en el Proyecto
A continuación se presenta cómo integrar la clase `SensorDataAPI` en un Proyecto AQI, de la capa de preprocesamiento, que recopila datos de sensores (AHT25, BMP280 y MQ135) y los envía a una API RESTful.

## Agregados al código del Archivo `main.cpp`
Al archivo main exitente se le sumaron las siguientes instrucciones para manejar el envio de datos hacia la API cada 60 segundos
```cpp
#include <Arduino.h>
#include <Wire.h>
#include "BH1750Sensor.h"
#include "ML8511Sensor.h"
#include "MQ135Sensor.h"
#include "AHT25Sensor.h"
#include "BMP280Sensor.h"
#include "LCDDisplay.h"
#include "TouchController.h"
#include "WS2812Controller.h"
#include "SensorDataAPI.h"
#include "time.h"

// Credenciales WiFi y API
const char* ssid = "Fibertel WiFi032 2.4GHz";
const char* password = "*********";
const char* apiEndpoint = "https://api.gonaiot.com/plata/datos_dispositivos/";
const char* apiKey = "plata";
const int id_disp = 6;

// --------------------- Configuración de Pines ---------------------
#define MQ135_PIN 34 // GPIO34 (ADC1_CH6)
#define TOUCH_PIN_0 4 // TOUCH0 GPIO4
#define TOUCH_PIN_1 0 // TOUCH1 GPIO0
#define TOUCH_PIN_2 2 // TOUCH2 GPIO2
#define WS2812_PIN 32  // Pin para la tira WS2812


// --------------------- Inicialización de Sensores y Periféricos ---------------------
MQ135Sensor mq135(MQ135_PIN);
AHT25Sensor aht25;
BMP280Sensor bmp280;
//BH1750Sensor bh1750;
//ML8511Sensor ml8511;
LCDDisplay lcd;
TouchController touch(TOUCH_PIN_0, TOUCH_PIN_1, TOUCH_PIN_2);
WS2812Controller ws2812(WS2812_PIN);

int menuActual = 0;
const int numMenus = 3;
int triggerAPI = 0;

// Instancia de la clase SensorDataAPI
SensorDataAPI sensorAPI(ssid, password, apiEndpoint, apiKey);

// --------------------- Configuración Inicial ---------------------
void setup() {
    Serial.begin(115200);
    while (!Serial);
    // Conectar a la red WiFi
    sensorAPI.connectWiFi();
    
    Wire.begin();
    
    // Inicializar sensores y perifericos
    mq135.begin();
    aht25.begin();
    bmp280.begin();
    //bh1750.begin();
    //ml8511.begin();
    lcd.begin();
    touch.begin();
    ws2812.begin();

    lcd.displayMenu(menuActual); // Mostrar el menú inicial
}
// --------------------- Lógica del Menú ---------------------
void navegarMenu() {
    int touchPressed = touch.checkTouch();
    
    if (touchPressed != 0){
        if (touchPressed == 1) { // Next
            if (menuActual <= 2)
                menuActual += 1;
            else
                menuActual = 0; 

        lcd.displayMenu(menuActual);
        } 
        if (touchPressed == 2) { // Next
            if (menuActual >= 0)
                menuActual -= 1;
            else
                menuActual = 2; 

        lcd.displayMenu(menuActual);
        } 
    }
    else 
        menuActual = menuActual;
}

// --------------------- Bucle Principal ---------------------
void loop() {
    navegarMenu();
    
    // Lectura de Sensores
    float mq135Data = mq135.readFilteredData();
    float ahtTemp, ahtHumidity;
    aht25.readData(ahtTemp, ahtHumidity);
    float bmpTemp, bmpPressure;
    bmp280.readData(bmpTemp, bmpPressure);
    float lightIntensity = 3.5;
    float indiceUV = 2525;

    // Actualizar el menú y mostrar en el LCD
    lcd.updateMenu(menuActual, mq135Data, ahtTemp, ahtHumidity, bmpTemp, bmpPressure, lightIntensity, indiceUV);
    //Pasaron 60 segundos?
    if (triggerAPI == 60){
        triggerAPI = 0;
        Serial.println("Procedemos a enviar las lecturas a la base de datos!");
        // Enviar datos a la API
        sensorAPI.sendData(ahtTemp, ahtHumidity, bmpPressure, mq135Data, id_disp);
        Serial.println("Enviaremos nuevas lecturas dentro de 60 segundos.");
    }

    // Actualizar la tira LED según el AQI calculado (esto es un ejemplo)
    int aqi = (int)(mq135Data); // Simplificación del AQI usando solo MQ135
    ws2812.updateLED(aqi);

    delay(1000); // Esperar 1 segundo antes de la siguiente lectura
    triggerAPI ++;
}  
```
## Explicación de las modificaciones agregadas al Código
* **Instancia de `SensorDataAPI`**: Se crea un objeto sensorAPI con las credenciales WiFi, la URL de la API y la clave de la API.  

* **Conexión WiFi**: En el setup(), se conecta a la red WiFi y sincroniza la hora usando el servidor NTP.    
```cpp  
// Credenciales WiFi y API
const char* ssid = "Fibertel WiFi032 2.4GHz";
const char* password = "*********";
const char* apiEndpoint = "https://api.gonaiot.com/plata/datos_dispositivos/";
const char* apiKey = "plata";
const int id_disp = 6;  
```

* **Lectura de Sensores y Envío de Datos**: En el loop(), se leen los valores de los sensores cada 1 segundo a forma de ejemplo de preprocesamiento, donde se podria hacer alguna correccion de errores o alguna clase de tratamiento a las mediciones.   
* **El contador `triggerAPI`**: se incrementa cada un segundo y cuando llega a 60 se envían la lectura del momento a la API con el mismo timestamp para agrupar las lecturas como una sola recolección.    
```cpp  
// Lectura de Sensores
    float mq135Data = mq135.readFilteredData();
    float ahtTemp, ahtHumidity;
    aht25.readData(ahtTemp, ahtHumidity);
    float bmpTemp, bmpPressure;
    bmp280.readData(bmpTemp, bmpPressure);
    float lightIntensity = 3.5;
    float indiceUV = 2525;

    // Actualizar el menú y mostrar en el LCD
    lcd.updateMenu(menuActual, mq135Data, ahtTemp, ahtHumidity, bmpTemp, bmpPressure, lightIntensity, indiceUV);
    //Pasaron 60 segundos?
    if (triggerAPI == 60){
        triggerAPI = 0;
        Serial.println("Procedemos a enviar las lecturas a la base de datos!");
        // Enviar datos a la API
        sensorAPI.sendData(ahtTemp, ahtHumidity, bmpPressure, mq135Data, id_disp);
        Serial.println("Enviaremos nuevas lecturas dentro de 60 segundos.");
    }  
```

## Conclusión
La clase `SensorDataAPI` encapsula eficazmente la lógica de conectividad WiFi, sincronización de tiempo y envío de datos a la API RESTful. Esto permite que los datos de sensores se registren de manera consistente y eficiente en la base de datos remota. El código es modular y fácilmente adaptable para otros tipos de sensores y APIs.
