# Test de la Ruta `/data`

Este archivo contiene una prueba que valida el correcto funcionamiento de la ruta `/data` de nuestra aplicación Flask. A continuación, se detalla el funcionamiento y el propósito de este test.

## Descripción del test

El test verifica el comportamiento de la ruta `/data` al enviar un conjunto de mediciones en formato JSON. Este test evalúa que la ruta:

1. Reciba un `POST` con datos en formato JSON.
2. Devuelva una respuesta con un código de estado `200`, indicando que la solicitud fue procesada correctamente.

### Estructura del Test

1. **`client()`**: 
    - Esta es una función fixture de `pytest`. Se encarga de crear un cliente de pruebas para la aplicación usando el método `app.test_client()` de Flask.
    - Este cliente simula el comportamiento de la aplicación en un entorno de pruebas y se utiliza para hacer solicitudes HTTP (como `GET`, `POST`, etc.) sin necesidad de ejecutar el servidor de Flask.

2. **`test_data_route(client)`**: 
    - Este es el test principal que se ejecuta para probar la ruta `/data`.
    - Hace una solicitud `POST` a la ruta `/data`, enviando un JSON con un conjunto de mediciones (una de temperatura en grados Celsius y otra de humedad en porcentaje).
    - **Datos enviados en el `POST`**:
      ```json
      {
          "mediciones": [
              {"valor": 25.5, "unidad": "C"},
              {"valor": 65.2, "unidad": "%"}
          ]
      }
      ```
    - El test luego verifica que la respuesta del servidor tiene un código de estado `200`, lo que indica que el servidor ha procesado la solicitud correctamente.

## Cómo ejecutar el test

Para ejecutar este test, asegúrate de tener instalado `pytest` y las dependencias de tu aplicación. Luego, simplemente ejecuta el siguiente comando en la terminal desde la raíz del proyecto:

```bash
pytest
```

## Requisitos previos  

### Flask:
Este proyecto utiliza Flask para manejar las rutas y el servidor web. Asegúrate de que tu aplicación esté correctamente configurada en el archivo app.py.
### Pytest:
Pytest es un marco de pruebas utilizado para ejecutar los tests en este proyecto. Instálalo usando pip si aún no lo tienes:
```bash
pip install pytest
```