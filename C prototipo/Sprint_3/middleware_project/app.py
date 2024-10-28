from flask import Flask, request, jsonify
import requests
from flask_jwt_extended import JWTManager, create_access_token, jwt_required

app = Flask(__name__)

# Clave secreta para la autenticación JWT
app.config['JWT_SECRET_KEY'] = 'clave_secreta'  
jwt = JWTManager(app)

# URL de la API remota
api_url = "https://api.gonaiot.com/plata/datos_dispositivos"

# Base de datos simulada (esto sería reemplazado por la conexión a una real)
datos_dispositivos = []

# Ruta para autenticar el dispositivo y obtener un token JWT
@app.route('/api/auth', methods=['POST'])
def auth():
    # Obtener credenciales del dispositivo (en la vida real, verifica estos datos)
    auth_data = request.get_json()
    device_id = auth_data.get("device_id")
    device_password = auth_data.get("device_password")

    # Autenticación simplificada (verifica las credenciales del dispositivo)
    if device_id == "ESP32_001" and device_password == "password123":
        # Crear un token de acceso JWT para el dispositivo
        access_token = create_access_token(identity={"device_id": device_id})
        return jsonify(access_token=access_token), 200
    else:
        return jsonify({"msg": "Credenciales inválidas"}), 401

# Ruta POST para recibir datos desde el ESP32
@app.route('/api/recibir-datos', methods=['POST'])
@jwt_required()  # Autenticación requerida para esta ruta
def recibir_datos():
    try:
        datos = request.get_json()

        # Validación de datos
        if 'temperatura' not in datos or 'humedad' not in datos or 'presion' not in datos or 'calidad_aire' not in datos:
            return jsonify({"error": "Faltan datos"}), 400
        
        # Validación específica de cada campo
        temperatura = datos['temperatura']
        humedad = datos['humedad']
        presion = datos['presion']
        calidad_aire = datos['calidad_aire']

        # Validar que la temperatura sea un número dentro de un rango plausible
        if not isinstance(temperatura, (int, float)) or not (-50 <= temperatura <= 60):
            return jsonify({"error": "Temperatura fuera de rango o no válida"}), 400

        # Validar que la humedad sea un número entre 0 y 100
        if not isinstance(humedad, (int, float)) or not (0 <= humedad <= 100):
            return jsonify({"error": "Humedad fuera de rango o no válida"}), 400

        # Validar que la presión sea un número dentro de un rango plausible
        if not isinstance(presion, (int, float)) or not (300 <= presion <= 1100):
            return jsonify({"error": "Presión fuera de rango o no válida"}), 400

        # Validar que la calidad del aire sea un número positivo
        if not isinstance(calidad_aire, (int, float)) or calidad_aire < 0:
            return jsonify({"error": "Calidad del aire no válida"}), 400

        # Enviar los datos a la API remota
        response = requests.post(api_url, json=datos)

        # Verificar la respuesta de la API
        if response.status_code == 200:
            return jsonify({"msg": "Datos enviados correctamente"}), 200
        else:
            return jsonify({"error": "Error al enviar datos a la API"}), response.status_code

    except Exception as e:
        return jsonify({"error": str(e)}), 500

# Ruta GET para verificar el estado de los dispositivos conectados
@app.route('/api/estado', methods=['GET'])
@jwt_required()
def estado_dispositivo():
    # Devolver la lista de datos recibidos (simulando el estado de los dispositivos)
    return jsonify(datos_dispositivos), 200

if __name__ == '__main__':
    app.run(debug=True)
