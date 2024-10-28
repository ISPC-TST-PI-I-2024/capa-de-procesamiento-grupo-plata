## Objetivos del Middleware  

**Intercepción de solicitudes desde el ESP32:** El middleware recibirá un JSON con las mediciones de calidad del aire y desglosará estos datos para almacenarlos adecuadamente en la base de datos remota.
**Autenticación:** Autenticación basada en usuarios, utilizando JWT para asegurar que tanto los dispositivos ESP32 como los usuarios estén correctamente autenticados.
**Normalización de datos:** Garantizar que los datos enviados estén estandarizados antes de almacenarse, asegurando que tengan una estructura y formato consistentes.
**Análisis en tiempo real:** Detectar patrones y anomalías en la calidad del aire.
**Interfaz de acceso a la base de datos:** Proveer una interfaz para acceder a los datos de la API remota, adaptando la información según el esquema de la base de datos.
**Proporcionar datos procesados:** Hacer que los datos estén disponibles para otras aplicaciones que deseen realizar análisis adicionales o presentarlos visualmente.  

## Árbol de Desarrollo
### El proyecto seguirá esta estructura:

```lua

middleware_project/
|
|-- app/
|    |-- __init__.py
|    |-- middleware.py
|    |-- routes.py
|
|-- Dockerfile
|-- docker-compose.yml
|-- requirements.txt
|-- nginx/
|    |-- default.conf
|-- tests/
|    |-- test_routes.py
|-- docs/
|    |-- manual_middleware.md  
```
  
## Paso 1: Configuración Inicial
Vamos a construir la base del middleware con Flask y JWT para la autenticación, que luego desplegaremos en Docker junto con NGINX como proxy inverso.

### 1. app/__init__.py
Inicializa la aplicación Flask, JWT, y añade la configuración necesaria para el middleware.

```python

from flask import Flask
from flask_jwt_extended import JWTManager

app = Flask(__name__)

# Configuración de la clave secreta para JWT
app.config['JWT_SECRET_KEY'] = 'super-secret'  # Cambia esto por una clave segura

# Inicialización de JWT
jwt = JWTManager(app)

from app import routes  
```  

### 2. app/routes.py
Definimos las rutas principales para el middleware, que manejarán la autenticación, la recepción de los datos del ESP32, y la comunicación con la base de datos remota a través de la API.

```python

from flask import request, jsonify
from flask_jwt_extended import jwt_required, create_access_token
import requests
from app import app

# Ruta de autenticación
@app.route('/login', methods=['POST'])
def login():
    # Ejemplo básico de autenticación con JWT
    username = request.json.get('username', None)
    password = request.json.get('password', None)
    
    # Validar credenciales con la base de datos remota (ejemplo simplificado)
    if username == "admin" and password == "password":
        access_token = create_access_token(identity=username)
        return jsonify(access_token=access_token), 200
    else:
        return jsonify({"msg": "Credenciales inválidas"}), 401

# Ruta para recibir datos del ESP32 y desglosar el JSON
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

        # Construir payload para la API remota
        payload = {
            "id_dispositivo": dispositivo_id,
            "fecha_recoleccion": fecha,
            "valor": valor,
            "unidad": unidad
        }

        # Enviar cada medición a la API remota
        api_url = "https://api.gonaiot.com/plata/datos_dispositivos/"
        headers = {"X-API-KEY": "plata", "Content-Type": "application/json"}
        response = requests.post(api_url, json=payload, headers=headers)
        
        if response.status_code != 201:
            return jsonify({"error": f"Error al almacenar {unidad}"}), 500

    return jsonify({"message": "Datos almacenados correctamente"}), 201  
	```  
	
Este código maneja la autenticación y el desglose de los datos enviados por el ESP32, que luego se envían a la base de datos remota a través de la API RESTful.

### 3. app/middleware.py
El middleware interceptará las solicitudes y normalizará los datos.

```python

from flask import request
from app import app

@app.before_request
def normalize_data():
    if request.method == "POST" and request.json:
        # Normalización de datos, por ejemplo, asegurarse de que todas las unidades están en el mismo formato
        mediciones = request.json.get("mediciones", [])
        for medicion in mediciones:
            if medicion['unidad'] == "C":
                # Convertir a Kelvin como ejemplo
                medicion['valor'] += 273.15
                medicion['unidad'] = "K"  
```  

Este middleware normaliza las unidades antes de enviarlas a la API remota.

### 4. Dockerfile
El Dockerfile configurará el contenedor para la aplicación Flask.

```dockerfile

FROM python:3.9

WORKDIR /app

COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD ["flask", "run", "--host=0.0.0.0"]  
```  

### 5. docker-compose.yml
Este archivo configurará el entorno para ejecutar la aplicación Flask junto con NGINX.

```yaml

version: '3.9'
services:
  web:
    build: .
    ports:
      - "5000:5000"
    environment:
      FLASK_ENV: development
    volumes:
      - .:/app

  nginx:
    image: nginx:latest
    ports:
      - "80:80"
    volumes:
      - ./nginx/default.conf:/etc/nginx/conf.d/default.conf
    depends_on:
      - web  
```  
	  
### 6. nginx/default.conf
Configura NGINX para actuar como proxy inverso entre el cliente y el middleware Flask.

```nginx

server {
    listen 80;

    location / {
        proxy_pass http://web:5000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
}  
```  

### 7. requirements.txt
```txt

Flask
Flask-JWT-Extended
requests
pytest  
```
  
## Paso 2: Despliegue y Pruebas en Docker
### 1. Asegurarte de que Docker esté corriendo
Antes de iniciar las pruebas, asegúrate de que tu aplicación y el servidor NGINX están ejecutándose correctamente. Desde la raíz de tu proyecto, ejecuta:

```bash
docker-compose up --build  
```
Esto construirá los contenedores y los levantará.

Para verificar que todo esté en funcionamiento:

```bash
docker-compose ps  
```
Se deberia ver algo como:

```markdown
Name                Command               State           Ports
--------------------------------------------------------------------------------------
middleware_web_1    flask run --host=0.0.0.0       Up      0.0.0.0:5000->5000/tcp
middleware_nginx_1  nginx -g daemon off;           Up      0.0.0.0:80->80/tcp  
```  

### 2. Probar la Autenticación (POST a /login)
Primero, probaremos la autenticación mediante JWT. Usaremos una herramienta como Postman o cURL para enviar solicitudes HTTP al servidor Flask.

#### Ejemplo con cURL:
```bash
curl -X POST http://localhost:80/login \
-H "Content-Type: application/json" \
-d '{"username":"admin", "password":"password"}'  
```
#### Ejemplo con Postman:
Selecciona el método POST.
URL: http://localhost:80/login
Body: En formato JSON, añade lo siguiente:
```json
{
  "username": "admin",
  "password": "password"
}  
```
Haz clic en Send.
#### Respuesta Esperada:
Si las credenciales son correctas, deberías recibir un token JWT en la respuesta. Algo como:

```json

{
  "access_token": "eyJhbGciOiJIUzI1NiIsInR..."
}  
```  

Este token será usado para autenticar solicitudes posteriores, como cuando enviemos los datos del ESP32.

## 3. Probar la Recepción de Datos desde el ESP32 (POST a /data)
Ahora que tenemos el token de autenticación, podemos enviar una solicitud desde el ESP32 (simulado en Postman o cURL) con las lecturas de los sensores.

#### Ejemplo con cURL:
Asumiendo que ya tienes el token access_token de la solicitud anterior, lo usarás en el encabezado Authorization.

```bash
curl -X POST http://localhost:80/data \
-H "Authorization: Bearer <tu_access_token>" \
-H "Content-Type: application/json" \
-d '{
  "id_dispositivo": 1,
  "fecha_recoleccion": "2024-10-01 12:00:00",
  "mediciones": [
    {"valor": 25.5, "unidad": "C"},
    {"valor": 65.2, "unidad": "%"},
    {"valor": 1013.25, "unidad": "hPa"}
  ]
}'  
```  

#### Ejemplo con Postman:
Selecciona el método POST.  

URL: http://localhost:80/data
Headers:
Authorization: Bearer <tu_access_token>
Content-Type: application/json
Body: En formato JSON, añade lo siguiente:
```json
{
  "id_dispositivo": 1,
  "fecha_recoleccion": "2024-10-01 12:00:00",
  "mediciones": [
    {"valor": 25.5, "unidad": "C"},
    {"valor": 65.2, "unidad": "%"},
    {"valor": 1013.25, "unidad": "hPa"}
  ]
}  
```
Haz clic en Send.
#### Respuesta Esperada:
Si los datos son recibidos correctamente, deberías obtener una respuesta similar a:

```json
{
  "message": "Datos almacenados correctamente"
}  
```
El middleware habrá desglosado cada medición y las habrá enviado a la API remota para almacenarlas en la tabla Datos_Dispositivos.

## Verificando el Desglose de Datos
Cada medición enviada en la solicitud será desglosada y almacenada como un registro separado en la tabla Datos_Dispositivos en la base de datos remota a través de la API.

Se Puede realizar una solicitud GET a la API remota para verificar que los datos han sido almacenados correctamente, si tiene acceso a endpoints como /datos_dispositivos.

## Paso 3: Documentación del Middleware
La documentación detallará los siguientes aspectos:

- Descripción General: Explicación de las funcionalidades del middleware.
- Rutas: Descripción de las rutas implementadas (/login, /data, etc.).
- Normalización de Datos: Explicación sobre cómo se procesan los datos enviados.
- Despliegue: Instrucciones para desplegar el middleware usando Docker y NGINX.
- Pruebas y Casos de Uso: Explicación de cómo probar las funcionalidades.