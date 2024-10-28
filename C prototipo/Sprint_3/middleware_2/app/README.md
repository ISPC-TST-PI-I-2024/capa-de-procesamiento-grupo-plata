## Estructura de la Carpeta `app`

La carpeta `app` contiene los tres archivos principales que permiten la ejecución de la aplicación Flask, cada uno con una funcionalidad específica. A continuación se describe la función de cada archivo:

### 1. `__init__.py`

Este archivo es el punto de entrada de la aplicación Flask. Aquí se configura y se inicializa la aplicación, incluyendo la configuración del sistema de autenticación JWT. 

#### Funcionalidad:

- **Inicialización de la Aplicación**: 
  Se crea una instancia de Flask y se habilita el modo `DEBUG` para facilitar el desarrollo. Esto permite que cualquier cambio en el código se refleje automáticamente sin necesidad de reiniciar la aplicación.
  
- **JWT (JSON Web Tokens)**: 
  Se configura un sistema básico de autenticación usando JWT. Esto es útil para proteger rutas en la aplicación, asegurándose de que solo los usuarios autenticados puedan acceder a ciertas funcionalidades.
  
- **Importación de Rutas**: 
  Importa las rutas desde el archivo `routes.py` para definir los diferentes endpoints de la API.

- **Ejecución de la Aplicación**: 
  El servidor Flask se ejecuta en el puerto 5000 y está configurado para aceptar solicitudes desde cualquier dirección (`0.0.0.0`).

#### Código:
```python
from flask import Flask
from flask_jwt_extended import JWTManager

app = Flask(__name__)
app.config['DEBUG'] = True
app.config['JWT_SECRET_KEY'] = 'super-secret'  # Cambia esto por una clave segura

jwt = JWTManager(app)

from app import routes

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)
```
### 2. `middleware.py`
Este archivo define una función before_request que actúa como middleware para interceptar las solicitudes antes de que lleguen a las rutas de la aplicación. En este caso, se utiliza para normalizar los datos entrantes en solicitudes POST que contienen mediciones.

#### Funcionalidad:  

**Normalización de Datos:** Intercepta cualquier solicitud POST con datos en formato JSON, específicamente aquellas que contienen mediciones. Si alguna medición tiene la unidad en grados Celsius (C), la función la convierte automáticamente a Kelvin (K). Esto garantiza que todas las mediciones sigan un formato unificado antes de ser procesadas o enviadas a la API remota.  

#### Código:
```python
from flask import request
from app import app

@app.before_request
def normalize_data():
    if request.method == "POST" and request.json:
        mediciones = request.json.get("mediciones", [])
        for medicion in mediciones:
            if medicion['unidad'] == "C":
                medicion['valor'] += 273.15
                medicion['unidad'] = "K"
```

### 3. `routes.py`
Este archivo contiene las rutas principales de la aplicación. Implementa dos endpoints: uno para autenticación (/login) y otro para recibir y procesar datos del ESP32 (/data).

#### Funcionalidad:

**Ruta /login:**  
Implementa una autenticación básica utilizando JWT. Recibe un POST con el username y password. Si las credenciales son válidas, se genera y devuelve un token de acceso (JWT), que puede usarse para acceder a rutas protegidas.  

**Ruta /data:**  
Protegida con JWT, esta ruta recibe un JSON con las mediciones de un dispositivo ESP32. Extrae los valores enviados y los envía a una API remota utilizando una solicitud POST. Si la respuesta de la API es satisfactoria, la aplicación devuelve un mensaje de éxito, de lo contrario, devuelve un error.

#### Código:
```python
from flask import request, jsonify
from flask_jwt_extended import jwt_required, create_access_token
import requests
from app import app

@app.route('/login', methods=['POST'])
def login():
    username = request.json.get('username', None)
    password = request.json.get('password', None)
    
    if username == "admin" and password == "password":
        access_token = create_access_token(identity=username)
        return jsonify(access_token=access_token), 200
    else:
        return jsonify({"msg": "Credenciales inválidas"}), 401

@app.route('/data', methods=['POST'])
@jwt_required()
def receive_data():
    data = request.json
    dispositivo_id = data['id_dispositivo']
    fecha = data['fecha_recoleccion']
    mediciones = data['mediciones']

    for medicion in mediciones:
        valor = medicion['valor']
        unidad = medicion['unidad']

        payload = {
            "id_dispositivo": dispositivo_id,
            "fecha_recoleccion": fecha,
            "valor": valor,
            "unidad": unidad
        }

        api_url = "https://api.gonaiot.com/plata/datos_dispositivos/"
        headers = {"X-API-KEY": "plata", "Content-Type": "application/json"}
        response = requests.post(api_url, json=payload, headers=headers)
        
        if response.status_code != 201:
            return jsonify({"error": f"Error al almacenar {unidad}"}), 500

    return jsonify({"message": "Datos almacenados correctamente"}), 201
```

### Resumen de Funcionamiento  

**Inicialización:** La aplicación se inicializa en __init__.py, configurando JWT y las rutas.  

**Normalización de Datos:** Antes de procesar cualquier solicitud POST con mediciones, el middleware.py convierte los valores de temperatura de Celsius a Kelvin.  

**Autenticación y Procesamiento de Datos:** 
Los usuarios deben autenticarse en la ruta /login para obtener un token JWT.  
La ruta /data, protegida con JWT, recibe las mediciones del dispositivo ESP32, normaliza los datos (si es necesario), y los envía a una API remota para su almacenamiento.  
```python
### Cómo ejecutar la aplicación
Instala las dependencias del proyecto (indicadas en requirements.txt).  

### Ejecuta la aplicación Flask:

python app/__init__.py

### Usa herramientas como Postman para probar las rutas /login y /data
```