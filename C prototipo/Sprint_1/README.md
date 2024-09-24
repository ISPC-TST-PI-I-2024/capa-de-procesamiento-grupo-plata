[![imagen-G-P-procesamiento.jpg](https://i.postimg.cc/nrJfB93H/imagen-G-P-procesamiento.jpg)](https://postimg.cc/sQwLRxF8)      
  
# Manejo de Endpoints de la API RESTful con Python  
El siguiente es un resumen a modo de ejemplo para e manejo de una API RESTful con python a traves de la libreria `requests`.   
  
# Estructura General
```python

import requests

# Base URL de la API
BASE_URL = "https://api.gonaiot.com/plata/{endpoint}/"

# Headers con la clave API
  
HEADERS = {
    "X-API-KEY": "Plata",  # Reemplazar con la clave API que estés usando
    "Content-Type": "application/json"
}  
```
## 1. GET: Obtener todos los recursos de un endpoint
```python  

def get_all(endpoint):
    url = BASE_URL.format(endpoint=endpoint)
    response = requests.get(url, headers=HEADERS)
    if response.status_code == 200:
        datos = response.json()
        print("Datos obtenidos:", datos)
    else:
        print(f"Error {response.status_code}: {response.text}")  

# Ejemplo: Obtener todos los dispositivos  
get_all("dispositivos")  
```  

## 2. GET: Obtener un recurso por ID
```python

def get_by_id(endpoint, resource_id):
    url = f"{BASE_URL.format(endpoint=endpoint)}{resource_id}"
    response = requests.get(url, headers=HEADERS)
    if response.status_code == 200:
        dato = response.json()
        print(f"Recurso {resource_id} obtenido:", dato)
    else:
        print(f"Error {response.status_code}: {response.text}")

# Ejemplo: Obtener el dispositivo con ID 1  

get_by_id("dispositivos", 1)  
```  

## 3. POST: Crear un nuevo recurso  

```python  

def create_resource(endpoint, data):
    url = BASE_URL.format(endpoint=endpoint)
    response = requests.post(url, json=data, headers=HEADERS)
    if response.status_code == 201:
        print("Recurso creado con éxito.")
    else:
        print(f"Error {response.status_code}: {response.text}")

# Ejemplo: Crear un nuevo dispositivo  
nuevo_dispositivo = {
    "nombre": "Nuevo dispositivo",
    "tipo": "sensor",
    "ubicacion": "Oficina",
    "id_usuario": 1
}
create_resource("dispositivos", nuevo_dispositivo)  
```  

## 4. PUT: Actualizar un recurso por ID
```python  

def update_resource(endpoint, resource_id, data):
    url = f"{BASE_URL.format(endpoint=endpoint)}{resource_id}"
    response = requests.put(url, json=data, headers=HEADERS)
    if response.status_code == 204:
        print(f"Recurso {resource_id} actualizado con éxito.")
    else:
        print(f"Error {response.status_code}: {response.text}")

# Ejemplo: Actualizar el dispositivo con ID 1  

dispositivo_actualizado = {
    "nombre": "Dispositivo actualizado",
    "tipo": "sensor",
    "ubicacion": "Laboratorio",
    "id_usuario": 1
}
update_resource("dispositivos", 1, dispositivo_actualizado)  
```  

## 5. DELETE: Eliminar un recurso por ID
```python  

def delete_resource(endpoint, resource_id):
    url = f"{BASE_URL.format(endpoint=endpoint)}{resource_id}"
    response = requests.delete(url, headers=HEADERS)
    if response.status_code == 204:
        print(f"Recurso {resource_id} eliminado con éxito.")
    else:
        print(f"Error {response.status_code}: {response.text}")  


# Ejemplo: Eliminar el dispositivo con ID 1
delete_resource("dispositivos", 1)  
```  


# Cheatsheet de Endpoints (basado en el manual)
| Método | Endpoint | Descripción |  
|--------|----------|-------------|
| `GET` |	/configuraciones/ |	Obtiene todas las configuraciones |
| `GET` |	/configuraciones/{id} |	Obtiene una configuración específica |
| `POST` | /configuraciones/ | Crea una nueva configuración |
| `PUT` |	/configuraciones/{id} |	Actualiza una configuración existente|
| `DELETE` | /configuraciones/{id} | Elimina una configuración |
| `GET` |	/datos_dispositivos/ | Obtiene todos los datos de dispositivos |
| `GET` |	/datos_dispositivos/{id} | Obtiene un dato de dispositivo por ID|
| `POST` | /datos_dispositivos/ | Crea un nuevo dato de dispositivo |
| `PUT` |	/datos_dispositivos/{id}| Actualiza un dato de dispositivo existente |
| `DELETE` | /datos_dispositivos/{id} | Elimina un dato de dispositivo por ID |
| `GET` |	/dispositivos/ | Obtiene todos los dispositivos |
| `GET` |	/dispositivos/{id} | Obtiene un dispositivo por ID |
| `POST` | /dispositivos/ | Crea un nuevo dispositivo |
| `PUT` |	/dispositivos/{id} | Actualiza un dispositivo existente |
| `DELETE` | /dispositivos/{id} |	Elimina un dispositivo por ID |
| `GET` |	/proyectos/ | Obtiene todos los proyectos |
| `GET` |	/proyectos/{id} | Obtiene un proyecto por ID |
| `POST` | /proyectos/ | Crea un nuevo proyecto |
| `PUT` |	/proyectos/{id}	| Actualiza un proyecto existente |
| `DELETE` | /proyectos/{id} | Elimina un proyecto por ID |
  
## Ejemplos de uso del codigo  

### 1. Obtener todos los dispositivos:
```python

get_all("dispositivos")  
```  

### 2. Obtener un dispositivo por ID:
```python
  

get_by_id("dispositivos", 1)  
```  

### 3. Crear un nuevo dispositivo:
```python
 
nuevo_dispositivo = {
    "nombre": "Sensor de Temperatura",
    "tipo": "sensor",
    "ubicacion": "Oficina",
    "id_usuario": 1
}
create_resource("dispositivos", nuevo_dispositivo)  
```

## 4. Actualizar un dispositivo por ID:
```python
 
dispositivo_actualizado = {
    "nombre": "Sensor de Humedad",
    "tipo": "sensor",
    "ubicacion": "Laboratorio",
    "id_usuario": 1
}
update_resource("dispositivos", 1, dispositivo_actualizado)  
```
## 5. Eliminar un dispositivo por ID:
```python
 
delete_resource("dispositivos", 1)  
```