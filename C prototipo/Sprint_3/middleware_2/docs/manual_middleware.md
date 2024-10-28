```python
from flask import Flask
from flask_jwt_extended import JWTManager

app = Flask(__name__)

# Configuración de la clave secreta para JWT
app.config['JWT_SECRET_KEY'] = 'super-secret'  # Cambia esto por una clave segura

# Inicialización de JWT
jwt = JWTManager(app)

from app import routes
```

## Importaciones:

**Flask:** La clase base para crear aplicaciones web en Flask.  

**JWTManager (de flask_jwt_extended):** Un gestor para manejar tokens JWT, que se utilizan para autenticar usuarios en aplicaciones web.  

## Creación de la aplicación Flask:

**app = Flask(__name__)**  

Esto inicializa la aplicación Flask, donde __name__ es el nombre del módulo actual, y permite que Flask determine la ruta base para cargar los recursos y las rutas asociadas.  

## Configuración de la clave secreta para JWT:


**app.config['JWT_SECRET_KEY'] = 'super-secret'**  

El token JWT necesita una clave secreta para ser creado y validado. En este ejemplo, la clave secreta es 'super-secret', pero en una aplicación de producción debe ser única y más segura. Esta clave es fundamental para proteger la integridad de los tokens JWT y evitar que se manipulen.  

## Inicialización de JWT:

**jwt = JWTManager(app)**  

Se crea una instancia de JWTManager, que se conecta a la aplicación Flask (app). Esto activa la funcionalidad de JWT para la aplicación, permitiendo que se puedan crear, manejar y verificar tokens JWT.

## Importación de las rutas:

**from app import routes**  

Esta línea importa el archivo o módulo que contiene las rutas de la aplicación **routes.py**. Este archivo es donde estarán las definiciones de las rutas de la API (por ejemplo, la ruta para el login y el manejo de datos). Importarlo después de la inicialización del JWT es importante para que todas las rutas tengan acceso al sistema de autenticación.

## ¿Qué es JWT (JSON Web Token)?
JWT es un estándar para crear tokens de acceso que se utilizan para autenticar usuarios en aplicaciones web. Es un formato de token seguro y compacto, que se compone de tres partes: header (encabezado), payload (carga) y signature (firma).

## Cómo funciona en este contexto:
Un usuario se autentica (por ejemplo, con nombre de usuario y contraseña).
Si las credenciales son correctas, la API devuelve un JWT firmado con la clave secreta (JWT_SECRET_KEY).
Este token se almacena en el cliente (navegador o dispositivo) y se envía en cada solicitud posterior para autenticar al usuario.
En el servidor, el token es validado usando la misma clave secreta. Si es válido, la solicitud se procesa; si no, se rechaza.  


