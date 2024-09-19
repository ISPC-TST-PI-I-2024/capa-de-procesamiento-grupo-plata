import requests
import json

# URL de la API a la que quieres hacer la petición
url = "https://jsonplaceholder.typicode.com/posts/1"

try:
    # Hacer una petición GET
    response = requests.get(url)

    # Comprobar que la respuesta fue exitosa (status code 200)
    if response.status_code == 200:
        # Convertir la respuesta en JSON
        data = response.json()
        print(json.dumps(data, indent=4))
    else:
        print(f"Error: {response.status_code}")

except Exception as e:
    print(f"Error al conectar con la API: {e}")
