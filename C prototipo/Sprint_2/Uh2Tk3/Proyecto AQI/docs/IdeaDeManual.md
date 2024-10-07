manual_middleware.md

# Middleware del Proyecto AQI

## Introducción

Este documento describe la implementación de un middleware personalizado que intercepta las solicitudes de datos de calidad del aire enviadas por un ESP32 y las redirige a una base de datos remota a través de una API RESTful. El middleware se encarga de desglosar los datos de los sensores, autenticarlos, normalizarlos y enviarlos a la base de datos remota.

El middleware está construido con **Flask** y utiliza **JWT** para autenticación. Está diseñado para ser desplegado utilizando **Docker** y está detrás de un **proxy inverso NGINX**.

## Estructura del Proyecto
  
```lua  
middleware_project/  
| |-- app/   
| |-- init.py # Inicialización de Flask y JWT   
| |-- middleware.py # Intercepta solicitudes y normaliza datos   
| |-- routes.py # Define las rutas de autenticación y recepción de datos   
| |-- Dockerfile # Dockerfile para construir el contenedor de Flask   
|-- docker-compose.yml # Configura los servicios Flask y NGINX   
|-- requirements.txt # Dependencias de Python   
|-- nginx/   
| |-- default.conf # Configuración de NGINX como proxy inverso   
|-- tests/   
| |-- test_routes.py # Pruebas automáticas   
|-- docs/   
| |-- manual_middleware.md # Documentación del middleware  
```


## Configuración y Dependencias

El middleware se basa en las siguientes tecnologías:

- **Flask**: Framework de Python para el backend.
- **Flask-JWT-Extended**: Proporciona autenticación basada en JSON Web Tokens (JWT).
- **NGINX**: Actúa como proxy inverso para enrutar las solicitudes al middleware.
- **Docker**: Contenedoriza la aplicación para su fácil despliegue.
- **Postman o cURL**: Herramientas sugeridas para probar las rutas HTTP.

### Dependencias de Python

Las dependencias se gestionan a través de `requirements.txt`:

```text
Flask
Flask-JWT-Extended
requests  
pytest  
```
  
## Descripción de Funcionalidades
###1. Autenticación
El middleware utiliza JWT para autenticar usuarios. La autenticación se maneja en la ruta /login, donde se verifica el nombre de usuario y la contraseña para generar un token JWT.

Ruta de autenticación:

Endpoint: /login
Método: POST
Body:
```json
{
  "username": "admin",
  "password": "password"
}  
```
Respuesta exitosa:
```json
{
  "access_token": "eyJhbGciOiJIUzI1NiIsInR5..."
}  
```  

### 2. Recepción y Desglose de Datos
El middleware recibe un JSON con los datos de calidad del aire desde el ESP32 en la ruta /data. El JSON contiene el ID del dispositivo, la fecha de recolección y las mediciones. Cada medición se desglosa y se envía a la API remota para ser almacenada en la tabla Datos_Dispositivos.

Ruta de recepción de datos:

Endpoint: /data
Método: POST
Autenticación: Requiere JWT.
Body:
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

###3. Normalización de Datos
El middleware intercepta las solicitudes antes de ser procesadas y normaliza los datos. Por ejemplo, las temperaturas en grados Celsius se convierten a Kelvin si es necesario.

```python
@app.before_request
def normalize_data():
    if request.method == "POST" and request.json:
        mediciones = request.json.get("mediciones", [])
        for medicion in mediciones:
            if medicion['unidad'] == "C":
                medicion['valor'] += 273.15
                medicion['unidad'] = "K"  
```  

## Despliegue
### 1. Configuración de Docker
El middleware está preparado para ser desplegado en Docker. Se incluye un archivo Dockerfile que define la imagen de Python utilizada y las dependencias necesarias para Flask.

Dockerfile:

```dockerfile
FROM python:3.9-slim

WORKDIR /app

COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD ["flask", "run", "--host=0.0.0.0"]  
```  

### 2. Proxy Inverso NGINX
El contenedor de NGINX está configurado como proxy inverso. Esto significa que NGINX escuchará en el puerto 80 y redirigirá las solicitudes al middleware Flask que está ejecutándose en el puerto 5000 dentro de su contenedor.

nginx/default.conf:

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

### 3. Configuración de docker-compose.yml
El archivo docker-compose.yml facilita el despliegue de los contenedores Flask y NGINX. Incluye los servicios necesarios y las configuraciones de los puertos.

``` yaml
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

### 4. Iniciar los Contenedores
Para iniciar el middleware y NGINX, navega a la raíz del proyecto y ejecuta:

```bash
docker-compose up --build  
```  

Esto levantará los contenedores de Flask y NGINX. La aplicación estará disponible en http://localhost.

## Pruebas y Validación
Se incluyen pruebas automatizadas en el archivo tests/test_routes.py que verifican la correcta operación de las rutas. Las pruebas se ejecutan utilizando pytest.

Ejecución de Pruebas
```bash
pytest  
```  

## Mantenimiento y Extensibilidad
El middleware está diseñado para ser extensible, lo que permite añadir fácilmente nuevas rutas y funcionalidades. Además, los datos normalizados son ideales para ser analizados por otras aplicaciones o para detectar anomalías en tiempo real.