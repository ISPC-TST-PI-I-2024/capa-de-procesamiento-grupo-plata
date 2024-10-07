### Manual de Uso

#### 1. **Requisitos Previos**

Antes de comenzar, asegúrate de tener instaladas las siguientes herramientas en tu máquina:

- **Docker**: para crear y ejecutar contenedores.
- **Docker Compose**: para orquestar los servicios que componen el middleware.
- **Python 3.9**: si deseas ejecutar el proyecto de manera local fuera de Docker.
- **Postman** o **cURL**: para probar las rutas y la API.

* * *

#### 2. **Estructura del Proyecto**

El proyecto sigue esta estructura:
```lua  
middleware_project/  
|  |-- app/   
|  |-- init.py # Inicialización de Flask y JWT   
|  |-- middleware.py # Intercepta solicitudes y normaliza datos   
|  |-- routes.py # Define las rutas de autenticación y recepción de datos   
|  |-- Dockerfile # Dockerfile para construir el contenedor de Flask   
|  -- docker-compose.yml # Configura los servicios Flask y NGINX   
|  -- requirements.txt # Dependencias de Python   
|  -- nginx/   
|  |-- default.conf # Configuración de NGINX como proxy inverso   
|   -- tests/   
|  |-- test_routes.py # Pruebas automáticas   
|-- docs/   
| |-- manual_middleware.md # Documentación del middleware  
```
* * *

#### 3. **Configuración y Ejecución**

##### 3.1 **Configuración con Docker**

El proyecto está preparado para ejecutarse dentro de contenedores de **Docker**. A continuación, se describen los pasos para poner en marcha el middleware con **Docker Compose**.

**Dockerfile**: define la imagen de Python y las dependencias necesarias para ejecutar Flask.
```dockerfile
FROM python:3.9-slim

WORKDIR /app

COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD ["flask", "run", "--host=0.0.0.0"]
```

**docker-compose.yml**: orquesta los servicios del middleware (Flask) y del proxy inverso (NGINX). Ejecuta los servicios en los puertos adecuados y gestiona las dependencias.

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
**nginx/default.conf**: archivo de configuración de **NGINX** que establece cómo se manejarán las solicitudes hacia el middleware.

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

* * *

##### 3.2 **Ejecución del Proyecto**

1. Clona el repositorio del middleware a tu máquina.
2. En la terminal, navega a la carpeta raíz del proyecto.
3. Ejecuta el siguiente comando para levantar los servicios:

```bash
codedocker-compose up --build
```

Esto levantará los contenedores de **Flask** y **NGINX**. El servicio estará disponible en **[http://localhost](http://localhost)**.

* * *

#### 4. **Rutas y Funcionalidades Principales**

##### 4.1 **Autenticación con JWT**

El middleware ofrece autenticación con **JWT**. Los usuarios deben autenticarse mediante la ruta `/login` proporcionando un nombre de usuario y una contraseña. 

- **Endpoint**: `/login`
- **Método**: `POST`
- **Body** (ejemplo):
```json
{ 
"username": "admin",
"password": "password"
}
``` 

**Respuesta exitosa**: devuelve un `access_token` que debe ser utilizado para autenticar las solicitudes posteriores.

 ```json
{ 
"access_token": "eyJhbGciOiJIUzI1NiIsInR5..."
}
```
##### 4.2 **Recepción de Datos**

El ESP32 envía datos de calidad del aire en la ruta `/data`. Esta ruta está protegida y requiere el token JWT obtenido durante el proceso de autenticación.

- **Endpoint**: `/data`
- **Método**: `POST`
- **Autenticación**: Requiere JWT.
- **Body** (ejemplo):

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

##### 4.3 **Normalización de Datos**

Antes de que los datos sean enviados a la base de datos remota, se normalizan en el middleware. Por ejemplo, si los datos vienen en grados Celsius, se convertirán a Kelvin.

**Ejemplo** de la función en Python para normalización de datos:
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
* * *

#### 5. **Pruebas Automatizadas**

Las pruebas automatizadas están definidas en el archivo `tests/test_routes.py` y se ejecutan usando `pytest`. Estas pruebas verifican que las rutas de autenticación y recepción de datos funcionen correctamente.

Para ejecutar las pruebas, usa el siguiente comando:

 ```bash
codepytest
 ```

* * *

#### 6. **Despliegue y Extensibilidad**

El middleware está diseñado para ser fácilmente desplegado y ampliado. Puedes agregar nuevas rutas y funcionalidades conforme el proyecto crezca. El diseño modular y el uso de Docker hacen que sea sencillo desplegar nuevas versiones y actualizar las existentes sin complicaciones.

* * *
