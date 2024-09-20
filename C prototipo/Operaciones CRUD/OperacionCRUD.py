import requests

# Definir la URL base y la clave API
BASE_URL = "https://api.gonaiot.com/plata/datos_dispositivos/"
API_KEY = "plata"

# Definir los headers con la clave API
headers = {
    "X-API-KEY": API_KEY,
    "Content-Type": "application/json"
}

# Función GET
def get_datos_dispositivos():
    response = requests.get(BASE_URL, headers=headers)
    if response.status_code == 200:
        datos = response.json()
        print("Datos obtenidos:", datos)
    else:
        print(f"Error en la solicitud: {response.status_code}")

# Función POST
def post_nuevo_dato():
    nuevo_dato = {
        "id_dispositivo": 1,
        "fecha_recoleccion": "2024-09-20 14:00:00",
        "valor": 23.5,
        "unidad": "Celsius"
    }
    response = requests.post(BASE_URL, json=nuevo_dato, headers=headers)
    if response.status_code == 201:
        print("Nuevo dato insertado correctamente.")
    else:
        print(f"Error en la inserción: {response.status_code}")

# Función PUT
def put_actualizar_dato():
    url_con_id = BASE_URL + "1"  # Suponiendo que el ID del registro a actualizar es 1
    dato_actualizado = {
        "id_dispositivo": 1,
        "fecha_recoleccion": "2024-09-20 16:00:00",
        "valor": 25.0,
        "unidad": "Celsius"
    }
    response = requests.put(url_con_id, json=dato_actualizado, headers=headers)
    if response.status_code == 204:
        print("Dato actualizado correctamente.")
    else:
        print(f"Error en la actualización: {response.status_code}")

# Función DELETE
def delete_dato():
    url_con_id = BASE_URL + "1"  # Suponiendo que el ID del registro a eliminar es 1
    response = requests.delete(url_con_id, headers=headers)
    if response.status_code == 204:
        print("Dato eliminado correctamente.")
    else:
        print(f"Error en la eliminación: {response.status_code}")

# Ejecución de las funciones
if __name__ == "__main__":
    # Llamar a las funciones según lo necesites
    get_datos_dispositivos()
    post_nuevo_dato()
    put_actualizar_dato()
    delete_dato()
