import pytest

from flask import json

import sys
import os

# Agregar la ruta del proyecto al PYTHONPATH
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../')))

from app import app


@pytest.fixture
def client():
    app.config['TESTING'] = True
    with app.test_client() as client:
        yield client

def test_login_success(client):
    # Simular una solicitud POST para el login
    response = client.post('/login', data=json.dumps({
        'username': 'admin',
        'password': 'password'
    }), content_type='application/json')

    # Verificar que la respuesta es 200 OK
    assert response.status_code == 200
    json_data = response.get_json()
    assert 'access_token' in json_data

def test_login_failure(client):
    # Simular una solicitud POST para el login con credenciales incorrectas
    response = client.post('/login', data=json.dumps({
        'username': 'admin',
        'password': 'wrongpassword'
    }), content_type='application/json')

    # Verificar que la respuesta es 401 Unauthorized
    assert response.status_code == 401
    json_data = response.get_json()
    assert json_data['msg'] == 'Credenciales inválidas'

def test_receive_data(client):
    # Simular una solicitud POST para obtener el token de autenticación
    login_response = client.post('/login', data=json.dumps({
        'username': 'admin',
        'password': 'password'
    }), content_type='application/json')
    access_token = login_response.get_json()['access_token']

    # Enviar datos del ESP32 usando el token JWT
    data = {
        "id_dispositivo": 6,
        "fecha_recoleccion": "2024-10-01 12:30:00",
        "mediciones": [
            {"valor": 25.5, "unidad": "C"},
            {"valor": 65.2, "unidad": "%"},
            {"valor": 1013.25, "unidad": "hPa"}
        ]
    }

    response = client.post('/data', data=json.dumps(data), 
                           headers={
                               'Authorization': f'Bearer {access_token}',
                               'Content-Type': 'application/json'
                           })

    # Verificar que la respuesta es 201 Created
    assert response.status_code == 201
    json_data = response.get_json()
    assert json_data['message'] == 'Datos almacenados correctamente'
