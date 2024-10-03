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
