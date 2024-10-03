from flask import Flask
from flask_jwt_extended import JWTManager

app = Flask(__name__)

# Configuración de la clave secreta para JWT
app.config['JWT_SECRET_KEY'] = 'super-secret'  # Cambia esto por una clave segura

# Inicialización de JWT
jwt = JWTManager(app)

from app import routes
