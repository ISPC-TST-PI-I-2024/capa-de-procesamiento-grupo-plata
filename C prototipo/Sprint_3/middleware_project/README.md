# API para Autenticación de Dispositivos y Recolección de Datos

Este proyecto implementa una API con **Flask** que permite la autenticación de dispositivos mediante **JWT** (JSON Web Token) y la recepción de datos desde un dispositivo (como un **ESP32**). Los datos incluyen parámetros ambientales como temperatura, humedad, presión y calidad del aire, y se validan antes de ser enviados a una API remota.

## Descripción del Código

### 1. Dependencias

El código utiliza las siguientes librerías:
- **Flask**: Un framework de microservicios en Python.
- **flask_jwt_extended**: Proporciona soporte para autenticación basada en JWT.
- **requests**: Para enviar solicitudes HTTP a una API externa.
  
Asegúrate de instalar las dependencias ejecutando:
```bash
pip install flask flask_jwt_extended requests
```

### 2. Configuración de la Aplicación
```python
app = Flask(__name__)
app.config['JWT_SECRET_KEY'] = 'clave_secreta'
jwt = JWTManager(app)

## La aplicación Flask se configura con una clave secreta que será usada para generar y verificar los tokens JWT. Estos tokens permiten que los dispositivos se autentiquen y accedan a rutas protegidas
```
### 3. Simulación de Base de Datos
```python
datos_dispositivos = []

## Esta lista simula una base de datos que en un escenario real sería reemplazada por una base de datos verdadera (como MySQL o MongoDB). Aquí se almacenan temporalmente los datos recibidos.
```
### 4. Rutas de la API
**Autenticación del Dispositivo (/api/auth)**  
```python
@app.route('/api/auth', methods=['POST'])
def auth():
    auth_data = request.get_json()
    device_id = auth_data.get("device_id")
    device_password = auth_data.get("device_password")

    if device_id == "ESP32_001" and device_password == "password123":
        access_token = create_access_token(identity={"device_id": device_id})
        return jsonify(access_token=access_token), 200
    else:
        return jsonify({"msg": "Credenciales inválidas"}), 401

## Esta ruta recibe las credenciales de un dispositivo y devuelve un token de acceso JWT si las credenciales son correctas.
```
**device_id:** El identificador del dispositivo (por ejemplo, ESP32_001).  

**device_password:** La contraseña del dispositivo.  

Si las credenciales son correctas, se genera un token JWT que el dispositivo debe usar para acceder a rutas protegidas. En caso de credenciales inválidas, se devuelve un error 401.

### Recepción de Datos del Dispositivo (/api/recibir-datos)  

```python
@app.route('/api/recibir-datos', methods=['POST'])
@jwt_required()
def recibir_datos():
    datos = request.get_json()

    # Validación de datos (temperatura, humedad, presión, calidad del aire)
    # ...
    
    response = requests.post(api_url, json=datos)
    if response.status_code == 200:
        return jsonify({"msg": "Datos enviados correctamente"}), 200
    else:
        return jsonify({"error": "Error al enviar datos a la API"}), response.status_code  

## Esta ruta recibe los datos del dispositivo y valida los valores de temperatura, humedad, presión y calidad del aire:

Temperatura: Debe ser un número entre -50°C y 60°C.
Humedad: Debe ser un número entre 0% y 100%.
Presión: Debe estar entre 300 y 1100 hPa.
Calidad del aire: Debe ser un valor positivo.  

## Si los datos son válidos, se envían a una API remota definida por api_url. Si la API remota acepta los datos, se devuelve un mensaje de éxito. En caso de error, se maneja de manera adecuada con los códigos de estado correspondientes.
```

### Verificación del Estado del Dispositivo (/api/estado)  
```python
@app.route('/api/estado', methods=['GET'])
@jwt_required()
def estado_dispositivo():
    return jsonify(datos_dispositivos), 200

## Esta ruta devuelve el estado de los dispositivos conectados, mostrando los datos recibidos. Dado que la ruta está protegida por JWT, solo los dispositivos autenticados pueden acceder a esta información.
```
## 5. Ejecución de la Aplicación

```python
if __name__ == '__main__':
    app.run(debug=True)

## El siguiente bloque de código es el encargado de ejecutar la aplicación Flask en modo debug, lo cual facilita el desarrollo, ya que recarga la aplicación en caso de cambios en el código.
```
## 6. Seguridad
La autenticación con JWT garantiza que solo los dispositivos que hayan iniciado sesión correctamente y tengan un token válido pueden enviar y recibir datos. Es importante no exponer la clave secreta **(JWT_SECRET_KEY)** y en un entorno de producción usar una clave fuerte y almacenar las credenciales de manera segura.

## 7. Validación de Datos
Cada vez que el dispositivo envía datos, se valida que:
```bash
→ Los campos estén presentes.  
→ Los valores estén dentro de un rango plausible. Esto evita errores de datos corruptos o no confiables antes de enviarlos a la API remota.
```