from flask import Flask
from flask_jwt_extended import JWTManager

app = Flask(__name__)

app.config['DEBUG'] = True

# Configuración de la clave secreta para JWT
app.config['JWT_SECRET_KEY'] = 'super-secret'  # Cambia esto por una clave segura



# Inicialización de JWT
jwt = JWTManager(app)

from app import routes

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)
