import requests
import json

# URL de la API a la que quieres hacer la petición POST
url = "https://jsonplaceholder.typicode.com/posts"

# Solicitar datos al usuario
title = input("Ingresa el título del post: ")
body = input("Ingresa el contenido del post: ")

# Crear el payload (cuerpo de la petición)
payload = {
    "title": title,
    "body": body,
    "userId": 1
}

try:
    # Hacer una petición POST con los datos ingresados
    response = requests.post(url, json=payload)
    
    # Comprobar si la respuesta fue exitosa (status code 201 para creación)
    if response.status_code == 201:
        print("Post creado exitosamente!")
        # Mostrar la respuesta de la API
        data = response.json()
        print(json.dumps(data, indent=4))
    else:
        print(f"Error: {response.status_code}")

except Exception as e:
    print(f"Error al conectar con la API: {e}")
