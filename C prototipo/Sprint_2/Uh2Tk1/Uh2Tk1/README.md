![image](../Uh2Tk1/assets/logo.PNG)
# Uh2Tk1

Este ejemplo enciende y apaga un LED conectado al ESP32. Cada vez que el LED se enciende, se muestra el mensaje "GRUPO PLATA" en el monitor serial.

## Requisitos

Para poder ejecutar este proyecto, necesitarás lo siguiente:

- **ESP32** (cualquier modelo compatible)
- **Cable USB** para conectar el ESP32 a tu computadora
- **Un LED** y una **resistencia** (recomendado: 220Ω)
- **Breadboard** y cables para conectar el LED al ESP32
- **VSCode** instalado en tu computadora
- **PlatformIO** instalado en VSCode

## Instalación y Configuración

1. **Instalar VSCode**: 
   - Puedes descargar Visual Studio Code desde [aquí](https://code.visualstudio.com/).

2. **Instalar PlatformIO**: 
   - Abre VSCode y ve a "Extensiones". Busca `PlatformIO IDE` e instálalo.
   - Una vez instalado, reinicia VSCode.

3. **Configurar el Proyecto**:
   - Abre PlatformIO en VSCode y crea un nuevo proyecto:
     - Selecciona el modelo de tu ESP32.
     - Elige "Arduino" como framework.
   - Copia y pega el código proporcionado en el archivo `src/main.cpp` de tu proyecto.

## Código del Proyecto

Este es el código que enciende y apaga un LED, mostrando el mensaje "GRUPO PLATA" en el monitor serial cada vez que el LED se enciende:

```cpp
#include <Arduino.h>

const int ledPin = 2;  // Pin donde está conectado el LED
bool ledState = false; // Estado inicial del LED (apagado)

void setup() {
    // Configurar el pin del LED como salida
    pinMode(ledPin, OUTPUT);

    // Configurar la comunicación serial
    Serial.begin(115200);
}

void loop() {
    // Cambiar el estado del LED
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    // Si el LED está encendido, mostrar el mensaje "GRUPO PLATA"
    if (ledState) {
        Serial.println("GRUPO PLATA");
    }

    // Esperar 1 segundo antes de cambiar el estado del LED
    delay(1000);
}
```

## Uso

### Subir el Código:
1. Conecta el ESP32 a tu computadora usando el cable USB.
2. En PlatformIO, selecciona el puerto serial adecuado (puedes usar el comando `pio device list` para identificarlo).
3. Haz clic en el botón "Upload" (flecha hacia arriba) para cargar el código en tu ESP32.

### Monitorear el Estado del LED:
1. Abre el monitor serial en PlatformIO para ver los mensajes.
2. Puedes usar el siguiente comando para abrir el monitor serial manualmente:
   
   ```bash
   pio device monitor
### Configuración del Monitor Serial:
1. Asegúrate de configurar el monitor serial a 115200 baudios en el archivo `platformio.ini` agregando esta línea:

    ```ini
    monitor_speed = 115200
    ```

### Prueba del LED:
1. El LED se encenderá y apagará cada segundo.
2. El mensaje **GRUPO PLATA** aparecerá en el monitor serial solo cuando el LED esté encendido.

## Solución de Problemas
1. Si no ves el mensaje en el monitor serial, verifica que:
   - El puerto serial esté configurado correctamente.
   - El baudrate del monitor esté ajustado a 115200.
   - El LED esté conectado correctamente.
2. Si el ESP32 no sube el código, asegúrate de que está en modo "bootloader" al mantener presionado el botón BOOT del ESP32 mientras subes el código.

