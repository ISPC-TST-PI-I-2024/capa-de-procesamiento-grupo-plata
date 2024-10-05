middleware_project/
|-- app/
|   |-- __init__.py           # Inicializa la app Flask y JWT
|   |-- middleware.py         # Contiene la lógica de normalización y manejo de datos
|   |-- routes.py             # Define las rutas para autenticación y manejo de datos
|-- Dockerfile                # Para construir el contenedor de Flask
|-- docker-compose.yml        # Para configurar Flask y NGINX
|-- requirements.txt          # Dependencias de Python
|-- nginx/
|   |-- default.conf          # Configuración del proxy inverso NGINX
|-- tests/
|   |-- test_routes.py        # Pruebas automatizadas con pytest
|-- docs/
|   |-- funcMiddleware.md      # Documentación sobre el middleware
