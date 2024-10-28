import requests
from flask import Flask, jsonify

app = Flask(__name__)

# Variables de conexión a la API
BASE_URL = "https://api.gonaiot.com/plata/datos_dispositivos/"
API_KEY = "plata"

# Ruta para obtener datos desde la API
@app.route('/obtener_datos_dispositivos')
def obtener_datos_dispositivos():
    headers = {
        'Authorization': f'Bearer {API_KEY}'  # Si la API usa este formato de autenticación
    }
    response = requests.get(BASE_URL, headers=headers)

    if response.status_code == 200:
        data = response.json()  # Suponiendo que la API responde con JSON
        return jsonify(data)
    else:
        return f"Error al conectar con la API: {response.status_code}", response.status_code

# Asegurarse de cerrar la conexión al final de cada solicitud (si se requiere cleanup en otros casos)
@app.teardown_appcontext
def teardown_db(exception):
    pass  # Puedes realizar limpieza adicional aquí si lo necesitas

if __name__ == '__main__':
    app.run(debug=True)

