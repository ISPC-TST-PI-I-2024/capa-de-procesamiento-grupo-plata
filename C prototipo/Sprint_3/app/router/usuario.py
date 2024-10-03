from flask import Blueprint, request, jsonify
from models import Usuario  # Suponiendo que tu modelo de usuarios esté definido en models.py
from db_config import db  # Conexión a la base de datos

usuarios_bp = Blueprint('usuarios', __name__)

# Ruta GET para obtener todos los usuarios
@usuarios_bp.route('/usuarios', methods=['GET'])
def obtener_usuarios():
    usuarios = Usuario.query.all()
    usuarios_lista = [{"id": u.id, "nombre": u.nombre, "email": u.email} for u in usuarios]
    return jsonify(usuarios_lista), 200

# Ruta GET para obtener un usuario por su ID
@usuarios_bp.route('/usuarios/<int:id>', methods=['GET'])
def obtener_usuario(id):
    usuario = Usuario.query.get(id)
    if usuario:
        return jsonify({"id": usuario.id, "nombre": usuario.nombre, "email": usuario.email}), 200
    else:
        return jsonify({"mensaje": "Usuario no encontrado"}), 404

# Ruta POST para crear un nuevo usuario
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