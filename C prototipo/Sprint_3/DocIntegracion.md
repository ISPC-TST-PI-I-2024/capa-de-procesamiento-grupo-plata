# Documento Técnico: Integración entre ESP32, Middleware Flask, y API RESTful Remota  

## 1. Introducción
Este documento detalla cómo se realizó la integración entre un ESP32 que mide la calidad del aire (AQI), un middleware construido en Flask que actúa como intermediario, y una API RESTful remota alojada en un servidor. También se explica el uso de contenedores con Docker para asegurar la escalabilidad y portabilidad del proyecto. La implementación permite que el ESP32 recopile datos de varios sensores, los envíe al middleware para procesamiento, y luego se almacenen en una base de datos remota mediante la API.

### Objetivos
- Integrar un ESP32 con varios sensores para medir la calidad del aire.
- Enviar estos datos a través de un middleware en Flask.
- Gestionar la autenticación y transformación de datos en el middleware.
- Almacenar los datos en una base de datos remota a través de una API RESTful.
- Utilizar Docker para encapsular los servicios y facilitar la replicación del entorno.  

## 2. Arquitectura General
El sistema se divide en tres componentes principales:

1. **ESP32**: Dispositivo IoT que recoge datos de sensores.
2. **Middleware Flask**: Intermediario que recibe, transforma y reenvía los datos a la API remota.
3. **API y Base de Datos Remota**: El backend que almacena y procesa los datos enviados por el ESP32 a través del middleware.  

El flujo general es el siguiente:

1. El ESP32 recopila datos de varios sensores de calidad del aire (temperatura, humedad, presión, y concentración de gases).  

2. Estos datos se envían al middleware Flask, donde se realiza la autenticación (JWT), procesamiento y normalización de datos.  

3. Finalmente, los datos procesados se envían a una API RESTful remota que los almacena en una base de datos.  

## Diagrama de Flujo
```plaintext
ESP32 -> Middleware Flask -> API RESTful Remota -> Base de Datos  
```  

## 3. ESP32: Adquisición y Envío de Datos
El ESP32 es el dispositivo de borde que interactúa con varios sensores (como AHT25 para temperatura/humedad, MQ135 para gases, y BMP280 para presión atmosférica). Este dispositivo toma lecturas periódicas y las envía al middleware Flask a través de solicitudes HTTP POST.

### Código del ESP32
En el código del ESP32, usamos las bibliotecas de Arduino y ESP para manejar las conexiones Wi-Fi y las solicitudes HTTP. A continuación, se explica la lógica básica del código.

### Conexión Wi-Fi y Configuración del API
El ESP32 se conecta a una red Wi-Fi y, a través de HTTP, realiza peticiones POST al middleware. Se usa autenticación basada en JWT para asegurar que las solicitudes sean válidas.

```cpp
sensorAPI.connectWiFi();  // Conectar a la red Wi-Fi
if (!sensorAPI.getAuthToken()) {
    ESP.restart();  // Reiniciar si no se puede obtener el token JWT
}  
```  

### Proceso de Envío de Datos
Cada 60 segundos, el ESP32 recopila los datos de los sensores y los empaqueta en un objeto JSON para enviarlos al middleware.

```cpp
sensorAPI.sendData(temperature, humidity, pressure, gasConcentration, id_dispositivo);  
```  

El JSON enviado contiene todas las lecturas de los sensores con un formato como este:

```json
{
    "id_dispositivo": 6,
    "fecha_recoleccion": "2024-10-01 12:00:00",
    "mediciones": [
        {"valor": 25.5, "unidad": "Celsius"},
        {"valor": 65.2, "unidad": "%"},
        {"valor": 1013.25, "unidad": "hPa"},
        {"valor": 200.0, "unidad": "PPM"}
    ]
}  
```  

### Gestión de Autenticación JWT
Para asegurar la autenticación, el ESP32 primero obtiene un token JWT del middleware Flask. Este token es luego utilizado en cada solicitud posterior en el encabezado HTTP.

## 4. Middleware Flask: Procesamiento y Normalización
El middleware es el componente central que actúa como intermediario entre el ESP32 y la API remota. Fue implementado utilizando Flask y encapsulado en un contenedor Docker para facilitar su despliegue.

### Función Principal del Middleware
1. **Autenticación con JWT**: El middleware autentica las solicitudes que recibe del ESP32 a través de tokens JWT. Esto asegura que solo dispositivos autorizados puedan enviar datos.
2. **Procesamiento y Normalización**: Los datos recibidos del ESP32 son procesados y, si es necesario, se normalizan para asegurar consistencia antes de enviarlos a la API remota.
3. **Redirección a la API Remota**: Después de procesar los datos, el middleware los envía a la API remota para que se almacenen en la base de datos.  

### Código del Middleware
El middleware está configurado para recibir los datos del ESP32, procesarlos y reenviarlos. Un ejemplo de una ruta que maneja los datos sería:

```python
@app.route('/data', methods=['POST'])
@jwt_required()
def receive_data():
    data = request.json
    for medicion in data['mediciones']:
        # Redirige cada medición a la API remota
        payload = {
            "id_dispositivo": data['id_dispositivo'],
            "fecha_recoleccion": data['fecha_recoleccion'],
            "valor": medicion['valor'],
            "unidad": medicion['unidad']
        }
        response = requests.post(api_url, json=payload, headers=headers)
        if response.status_code != 201:
            return jsonify({"error": "Error al almacenar datos"}), 500
    return jsonify({"message": "Datos almacenados correctamente"}), 201  
```  

### NGINX como Proxy Inverso
NGINX se utiliza como un proxy inverso delante del servidor Flask. Su función principal es recibir las solicitudes HTTP y redirigirlas al contenedor Flask que ejecuta la lógica del middleware. NGINX también puede manejar la compresión y el manejo de cargas más grandes, mejorando la eficiencia y seguridad.  


## 5. API RESTful y Base de Datos Remota
La API RESTful está alojada en un servidor externo (gonaiot) y recibe las solicitudes POST desde el middleware Flask. Esta API realiza la inserción de datos en una base de datos relacional (MySQL) que almacena cada medición.

### Estructura de la Base de Datos
La base de datos contiene una tabla principal llamada Datos_Dispositivos, que tiene la siguiente estructura:

```sql
CREATE TABLE Datos_Dispositivos (
    id_dato INT AUTO_INCREMENT PRIMARY KEY,
    id_dispositivo INT,
    fecha_recoleccion TIMESTAMP,
    valor FLOAT,
    unidad VARCHAR(20)
);  
```
Cada vez que el middleware envía un conjunto de mediciones, se almacena un nuevo registro en esta tabla.

## 6. Uso de Contenedores (Docker)
El uso de Docker para contenerizar los servicios permite que el proyecto sea portable, replicable y escalable. Cada componente (middleware Flask y NGINX) se ejecuta en su propio contenedor. Esto asegura que el entorno de desarrollo y producción sea consistente.

### Ventajas del Uso de Contenedores
- **Portabilidad**: El proyecto puede ejecutarse en cualquier máquina que tenga Docker instalado, sin necesidad de preocuparse por las dependencias locales.
- **Escalabilidad**: Podemos escalar los servicios fácilmente añadiendo más contenedores si la carga aumenta.
- **Aislamiento**: Cada componente del sistema está aislado en su propio contenedor, lo que evita conflictos entre dependencias.  

### Docker Compose
`docker-compose.yml` se utiliza para definir y ejecutar múltiples contenedores. En nuestro caso, define dos servicios principales:

1- `web`: El contenedor que ejecuta Flask (middleware).
2- `nginx`: El contenedor que ejecuta NGINX como proxy inverso.
El archivo `docker-compose.yml` permite levantar ambos servicios simultáneamente con un solo comando:

```bash
docker-compose up --build  
```  

## 7. Conclusión
La integración entre el ESP32, el middleware Flask y la API remota se ha logrado exitosamente mediante el uso de estándares de la industria, como **autenticación JWT, contenedorización con Docker**, y la utilización de **NGINX** como proxy inverso. Este enfoque garantiza que el sistema sea escalable, seguro y replicable en otros entornos.

El ESP32 actúa como el dispositivo de borde, recopilando datos de los sensores, mientras que el middleware maneja la autenticación y procesamiento de los datos, y finalmente la API remota almacena esos datos en la base de datos.

El uso de contenedores asegura que todo el sistema pueda ser desplegado en cualquier entorno sin problemas de compatibilidad.