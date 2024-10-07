from flask import Flask
from flask_jwt_extended import JWTManager

app = Flask(__name__)

# Configura el JWT
app.config['JWT_SECRET_KEY'] = 'super-secret-key'
jwt = JWTManager(app)

from app import routes
