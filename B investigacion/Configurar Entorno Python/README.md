# Guia rapida para configurar el entorno Python y hacer un test de una API.

## Instalar Python:

### Asegúrate de tener Python instalado en tu sistema.  
Puedes verificarlo ejecutando en tu terminal:  

**python --version**  

Si no está instalado, puedes descargarlo desde la web oficial de Python.

### Crear un entorno virtual:

Abre VS Code y navega a tu proyecto o crea una nueva carpeta para el proyecto.
Abre la terminal integrada de VS Code (Ctrl + ` o Terminal > New Terminal en la barra de menús).  

Crea un entorno virtual ejecutando:  

**python -m venv venv**  

Activar el entorno virtual:

Para Windows:

**venv\Scripts\activate**  

Para Linux/macOS:  

**source venv/bin/activate**  

### Instalar las librerías necesarias:

Una vez que el entorno esté activado, instala las librerías que vas a necesitar, como **requests** y **json**:  

**pip install requests**  

Nota: La librería **json** es parte de la biblioteca estándar de Python, por lo que no es necesario instalarla.

### Probar la conexión básica con la API:

Crea un archivo Python en tu proyecto, por ejemplo, **api_test.py.**
En este archivo, añade el siguiente código para probar la conexión a una API (usando un ejemplo básico de API de prueba como **jsonplaceholder**):

```python
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

```
## Ejecutar el código:

### En la terminal, ejecuta el script con:

**python api_test.py**  

### Criterios de aceptación:

→ Entorno virtual configurado:

→ Verifica que, al activar el entorno, veas (venv) al inicio de la línea de la terminal.  
Instalación de librerías:

Ejecuta:  
**pip list**  
para verificar que la librería requests está instalada en el entorno.
Conexión con la API:

Al ejecutar el script, deberías ver una respuesta JSON formateada en la terminal, lo que indica que la conexión con la API fue exitosa.

