# Explicación del Test :  
**Importaciones de librerías:**

* **pytest:** Una herramienta para realizar pruebas unitarias en Python.  

* **json (de Flask):** Permite manejar datos en formato JSON en las solicitudes HTTP.  

* **sys y os:** Se utilizan para modificar el PYTHONPATH y permitir la importación de módulos del proyecto.  

* **from app import app:** Importa la aplicación Flask desde el archivo principal del proyecto.  

```python
# Fixture client():

Configura el entorno de pruebas para la aplicación Flask. Usamos app.test_client() para simular solicitudes HTTP a la API sin necesidad de levantar un servidor real. app.config['TESTING'] = True habilita el modo de pruebas en Flask.  

# test_login_success():

Simula una solicitud POST a la ruta /login con credenciales correctas. Verifica que la respuesta tenga el código de estado 200 OK y que en el JSON de respuesta haya un token de acceso (access_token).  

# test_login_failure():

Simula una solicitud POST a la ruta /login con credenciales incorrectas. Verifica que la respuesta tenga el código de estado 401 Unauthorized y que el mensaje de error sea "Credenciales inválidas".  

# test_receive_data():

Realiza primero una solicitud POST para obtener un access_token mediante un login exitoso. Luego, envía datos simulados de un dispositivo (ESP32) a la ruta /data, utilizando el token JWT. Verifica que la respuesta sea 201 Created y que los datos hayan sido almacenados correctamente.  
```

## Explicación de las Pruebas  
```python  
# 1. Fixture client()  

Esta función crea un entorno de pruebas para la aplicación Flask. Al utilizar app.test_client(), podemos simular peticiones a la API sin necesidad de ejecutar un servidor.

@pytest.fixture
def client():
    app.config['TESTING'] = True
    with app.test_client() as client:
        yield client


# 2. test_login_success()

Esta prueba simula una solicitud POST a la ruta /login con credenciales correctas (admin y password). Verifica que la respuesta sea 200 OK y que en el cuerpo de la respuesta JSON se incluya un access_token.


def test_login_success(client):
    response = client.post('/login', data=json.dumps({
        'username': 'admin',
        'password': 'password'
    }), content_type='application/json')

    assert response.status_code == 200
    json_data = response.get_json()
    assert 'access_token' in json_data


# 3. test_login_failure()

Esta prueba simula una solicitud POST a la ruta /login con credenciales incorrectas. Se espera que la API responda con un código de estado 401 Unauthorized y que el mensaje devuelto sea "Credenciales inválidas".


def test_login_failure(client):
    response = client.post('/login', data=json.dumps({
        'username': 'admin',
        'password': 'wrongpassword'
    }), content_type='application/json')

    assert response.status_code == 401
    json_data = response.get_json()
    assert json_data['msg'] == 'Credenciales inválidas'



# 4. test_receive_data()

Esta prueba primero realiza un inicio de sesión exitoso para obtener un token JWT (access_token). Luego, simula el envío de datos desde un dispositivo ESP32 a la ruta /data, utilizando el token JWT en los encabezados de la solicitud. Verifica que los datos sean almacenados correctamente y que la respuesta sea 201 Created.


def test_receive_data(client):
    # Realizar login para obtener el token
    login_response = client.post('/login', data=json.dumps({
        'username': 'admin',
        'password': 'password'
    }), content_type='application/json')
    access_token = login_response.get_json()['access_token']

    # Enviar datos simulados del ESP32
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

    assert response.status_code == 201
    json_data = response.get_json()
    assert json_data['message'] == 'Datos almacenados correctamente'
```


