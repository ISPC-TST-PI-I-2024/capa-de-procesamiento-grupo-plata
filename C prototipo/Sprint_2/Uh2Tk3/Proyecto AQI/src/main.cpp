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
const char* ssid = "Fibertel WiFi986 2.4GHz-2.4GHz"; //"Fibertel WiFi032 2.4GHz"
const char* password = "00434990126"; //"vuelalto67"
const char* apiEndpoint = "http://192.168.0.67/data";  // Cambia según tu configuración
const char* loginEndpoint = "http://192.168.0.67/login";  // Ruta para obtener el token JWT
const char* apiKey = "plata";
const char* username = "admin";  // Cambia según tu usuario
const char* userPassword = "password";  // Cambia según tu contraseña
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
SensorDataAPI sensorAPI(ssid, password, apiEndpoint, loginEndpoint, apiKey, username, userPassword);

// --------------------- Configuración Inicial ---------------------
void setup() {
    Serial.begin(115200);
    while (!Serial);
    // Conectar a la red WiFi
    sensorAPI.connectWiFi();

    // Obtener el token JWT
    if (!sensorAPI.getAuthToken()) {
        Serial.println("Error al obtener el token JWT, reiniciando...");
        ESP.restart();  // Reiniciar si no se puede obtener el token
    }
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
    //Serial.println(touchRead(TOUCH_PIN_0));
    //Serial.println(touchRead(TOUCH_PIN_1));
    //Serial.println(menuActual);
    //Serial.println(" ");

    delay(1000); // Esperar 1 segundo antes de la siguiente lectura
    triggerAPI ++;
}
