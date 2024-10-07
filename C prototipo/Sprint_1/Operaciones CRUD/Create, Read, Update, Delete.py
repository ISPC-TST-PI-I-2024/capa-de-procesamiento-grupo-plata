import requests
from flask import Flask, jsonify, request

app = Flask(__name__)

# Variables de conexión a la API
BASE_URL = "https://api.gonaiot.com/plata/datos_dispositivos/"
API_KEY = "plata"

# Ruta para obtener datos desde la API (Read)
@app.route('/obtener_datos_dispositivos', methods=['GET'])
def obtener_datos_dispositivos():
    headers = {
        'Authorization': f'Bearer {API_KEY}'
    }
    response = requests.get(BASE_URL, headers=headers)

    if response.status_code == 200:
        data = response.json()
        return jsonify(data)
    else:
        return f"Error al conectar con la API: {response.status_code}", response.status_code

# Ruta para enviar nuevos datos a la API (Create)
@app.route('/enviar_datos_dispositivos', methods=['POST'])
def enviar_datos_dispositivos():
    datos = request.json  # Se espera que los datos lleguen en formato JSON
    headers = {
        'Authorization': f'Bearer {API_KEY}',
        'Content-Type': 'application/json'
    }
    
    response = requests.post(BASE_URL, headers=headers, json=datos)

    if response.status_code == 201:
        return jsonify({"mensaje": "Datos enviados con éxito"}), 201
    else:
        return f"Error al enviar datos: {response.status_code}", response.status_code

# Ruta para actualizar datos de un dispositivo específico (Update)
@app.route('/actualizar_datos_dispositivos/<int:id>', methods=['PUT'])
def actualizar_datos_dispositivos(id):
    datos_actualizados = request.json  # Se espera que los datos a actualizar lleguen en formato JSON
    headers = {
        'Authorization': f'Bearer {API_KEY}',
        'Content-Type': 'application/json'
    }
    
    url = f"{BASE_URL}{id}/"  # Incluye el ID del dispositivo a actualizar en la URL
    response = requests.put(url, headers=headers, json=datos_actualizados)

    if response.status_code == 204:
        return jsonify({"mensaje": "Datos actualizados con éxito"}), 204
    else:
        return f"Error al actualizar datos: {response.status_code}", response.status_code

# Ruta para eliminar datos de un dispositivo específico (Delete)
@app.route('/eliminar_datos_dispositivos/<int:id>', methods=['DELETE'])
def eliminar_datos_dispositivos(id):
    headers = {
        'Authorization': f'Bearer {API_KEY}'
    }
    
    url = f"{BASE_URL}{id}/"  # Incluye el ID del dispositivo a eliminar en la URL
    response = requests.delete(url, headers=headers)

    if response.status_code == 204:
        return jsonify({"mensaje": "Datos eliminados con éxito"}), 204
    else:
        return f"Error al eliminar datos: {response.status_code}", response.status_code

# Final del archivo: asegurarse de cerrar la conexión
@app.teardown_appcontext
def teardown_db(exception):
    pass  # Puedes realizar limpieza adicional aquí si lo necesitas

if __name__ == '__main__':
    app.run(debug=True)
