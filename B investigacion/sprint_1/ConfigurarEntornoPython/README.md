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

# Explicación del Entorno Virtual (venv)

Este proyecto utiliza un entorno virtual de Python (`venv`) para aislar y gestionar las dependencias y librerías necesarias para su correcto funcionamiento. A continuación, se describe la estructura y el propósito de los archivos y carpetas que componen el entorno virtual.

## ¿Qué es un entorno virtual?

Un entorno virtual en Python es un espacio aislado donde se pueden instalar librerías y dependencias sin afectar el entorno de Python instalado globalmente en el sistema. Esto permite tener diferentes proyectos con distintas versiones de librerías y paquetes sin que entren en conflicto entre sí.

## Estructura del entorno virtual

Cuando creas un entorno virtual utilizando `python -m venv <nombre-del-entorno>`, se genera una carpeta llamada `venv` (o el nombre que hayas elegido). Esta carpeta contiene varios archivos y directorios importantes:

### 1. `venv/Include`

Este directorio contiene los archivos de cabecera (headers) de Python que pueden ser necesarios si se quieren compilar extensiones de Python. Aunque es menos común que se utilicen directamente, son importantes cuando instalas librerías que requieren compilación adicional.

### 2. `venv/Lib`

Aquí es donde se almacenan todas las librerías y dependencias que instalas dentro del entorno virtual. Por ejemplo, si instalas la librería `requests` con el comando `pip install requests`, esta librería se ubicará dentro de este directorio. Es importante señalar que estas librerías solo están disponibles dentro de este entorno virtual y no afectan las librerías instaladas a nivel global en tu sistema.

### 3. `venv/Scripts` (Windows) o `venv/bin` (Linux/Mac)

Este directorio contiene los ejecutables que permiten activar y utilizar el entorno virtual. En Windows, por ejemplo, el archivo `activate` está dentro de esta carpeta, y al ejecutarlo (con el comando `.\Scripts\activate`), el entorno virtual se activa.

Además, también contiene el intérprete de Python específico del entorno virtual. Cada entorno virtual tiene su propio intérprete de Python que ejecuta los scripts y comandos mientras el entorno está activo.

### 4. `pyvenv.cfg`

Este archivo es una configuración interna del entorno virtual. Contiene información sobre la versión de Python utilizada y las opciones con las que fue creado el entorno virtual. Por lo general, no necesitas modificar este archivo.

## ¿Por qué usar un entorno virtual?

- **Aislamiento**: Cada proyecto puede tener sus propias dependencias y versiones de paquetes, lo que evita conflictos entre proyectos.
- **Gestión de dependencias**: Puedes instalar exactamente las librerías que necesitas sin afectar otros proyectos.
- **Compatibilidad**: Aseguras que el entorno sea consistente en diferentes entornos de desarrollo o producción.

## ¿Cómo activar el entorno virtual?

1. **En Windows**: Ejecuta el siguiente comando en la terminal desde la carpeta donde está ubicado el entorno virtual:
   ```
   .\venv\Scripts\activate

## ¿Cómo desactivar el entorno virtual?  

Para desactivar el entorno virtual, solo debes ejecutar el comando:

``` 
 deactivate
