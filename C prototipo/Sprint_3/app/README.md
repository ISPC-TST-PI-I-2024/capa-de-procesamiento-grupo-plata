
Esta práctica es una API básica para la gestión de usuarios utilizando **Flask** y **SQLAlchemy** para la base de datos. Permite realizar operaciones **CRUD (Crear, Leer, Actualizar, Eliminar)** sobre los usuarios almacenados en la base de datos.

## Archivos Principales

### `app.py`

Este archivo es el punto de entrada de la aplicación Flask. Su función es inicializar el servidor y registrar el **Blueprint** que maneja las rutas relacionadas con los usuarios.

```python
from flask import Flask
from routes.usuarios import usuarios_bp

app = Flask(__name__)

# Registrar el Blueprint
app.register_blueprint(usuarios_bp)

if __name__ == '__main__':
    app.run(debug=True)


from flask import Flask: Importa la clase Flask que se usa para crear la aplicación web.  

from routes.usuarios import usuarios_bp: Importa el blueprint usuarios_bp desde el archivo usuario.py.Un blueprint en Flask permite organizar el código en módulos para mantener la estructura limpia y escalable.  

app = Flask(__name__): Crea una instancia de la aplicación Flask, que es la base del servidor web.  

app.register_blueprint(usuarios_bp): Registra el blueprint usuarios_bp, que maneja todas las rutas relacionadas con los usuarios.  

if __name__ == '__main__': Verifica si el archivo app.py se está ejecutando directamente. Si es así, arranca el servidor Flask con el modo debug activado (útil para desarrollo).  
```

### `usuario.py`

Este archivo define las rutas relacionadas con los usuarios mediante el uso de un Blueprint (usuarios_bp). Contiene varias rutas para obtener, crear y manipular usuarios en la base de datos.

```python
from flask import Blueprint, request, jsonify
from models import Usuario  # Suponiendo que tu modelo de usuarios esté definido en models.py
from db_config import db  # Conexión a la base de datos

usuarios_bp = Blueprint('usuarios', __name__)
from flask import Blueprint, request, jsonify: Importa Blueprint para organizar las rutas, request para recibir datos enviados por el cliente, y jsonify para devolver respuestas en formato JSON.
from models import Usuario: Importa el modelo Usuario (asumiendo que está definido en models.py), que representa la tabla de usuarios en la base de datos.
from db_config import db: Importa la instancia de conexión a la base de datos desde db_config.py.  



##   Rutas Definidas  



## Ruta GET para obtener todos los usuarios  

@usuarios_bp.route('/usuarios', methods=['GET'])
def obtener_usuarios():
    usuarios = Usuario.query.all()
    usuarios_lista = [{"id": u.id, "nombre": u.nombre, "email": u.email} for u in usuarios]
    return jsonify(usuarios_lista), 200
Esta ruta permite obtener todos los usuarios de la base de datos. Utiliza el modelo Usuario para hacer una consulta (query.all()) que obtiene todos los registros de la tabla usuarios. Luego, construye una lista de diccionarios con los detalles de cada usuario y los retorna en formato JSON.



##  Ruta GET para obtener un usuario por su ID

@usuarios_bp.route('/usuarios/<int:id>', methods=['GET'])
def obtener_usuario(id):
    usuario = Usuario.query.get(id)
    if usuario:
        return jsonify({"id": usuario.id, "nombre": usuario.nombre, "email": usuario.email}), 200
    else:
        return jsonify({"mensaje": "Usuario no encontrado"}), 404
Esta ruta permite obtener un usuario específico por su ID. Si el usuario se encuentra en la base de datos, se devuelven sus datos; si no, se responde con un mensaje de "Usuario no encontrado" y un código de estado 404.



## Ruta POST para crear un nuevo usuario

@usuarios_bp.route('/usuarios', methods=['POST'])
def crear_usuario():
    data = request.get_json()
    nuevo_usuario = Usuario(
        nombre=data['nombre'],
        email=data['email'],
        rol=data['rol'],
        password=data['password']  # Asegúrate de encriptar la contraseña antes de guardarla
    )
    db.session.add(nuevo_usuario)
    db.session.commit()
    return jsonify({"mensaje": "Usuario creado con éxito"}), 201  
```
Esta ruta permite crear un nuevo usuario. Los datos se envían en formato JSON desde el cliente, se capturan con request.get_json(), y se crea una nueva instancia del modelo Usuario. Después de agregar el nuevo usuario a la base de datos y guardar los cambios, se devuelve un mensaje de éxito.

**Nota:** Es importante manejar la encriptación de contraseñas, ya que en este ejemplo se están guardando en texto plano, lo cual no es recomendado para aplicaciones reales.

## Resumen del Flujo
**app.py:** Inicializa el servidor y registra las rutas definidas en usuario.py.

**usuario.py:** Define las rutas para manejar la obtención y creación de usuarios. Cada ruta interactúa con la base de datos mediante el modelo Usuario y la conexión db.
Este proyecto utiliza Flask para manejar el servidor web y las rutas, y SQLAlchemy (a través de db) para manejar las interacciones con la base de datos.

