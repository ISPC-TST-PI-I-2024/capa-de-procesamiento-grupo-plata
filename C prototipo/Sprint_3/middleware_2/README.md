### Este repositorio contiene el código de middleware y firmware para la integración de un sistema basado en ESP32, junto con el entorno de trabajo necesario para su despliegue y pruebas.

## Estructura del proyecto

- **.venv/**: 
  Contiene el entorno virtual de Python para el proyecto, lo que asegura que todas las dependencias se manejen de manera aislada. Se recomienda activarlo antes de trabajar en el proyecto.
  
- **.vscode/**: 
  Configuraciones específicas del editor de código [Visual Studio Code](https://code.visualstudio.com/). Incluye configuraciones como la definición del entorno de desarrollo y las extensiones necesarias para el proyecto.

- **app/**: 
  Aquí reside el código principal de la aplicación. Incluye el middleware y las integraciones con el ESP32.

- **docs/**: 
  Documentación del proyecto, incluyendo guías de uso, configuración, y cualquier información relevante sobre la estructura y el desarrollo del proyecto.

- **nginx/**: 
  Contiene las configuraciones de Nginx, que actúa como servidor web para el despliegue de la aplicación.

- **tests/**: 
  En este directorio se encuentran las pruebas unitarias y de integración. Asegúrate de correrlas antes de cualquier cambio importante en el código.

- **Dockerfile**: 
  Archivo utilizado para construir una imagen Docker del proyecto. Define el entorno y los pasos necesarios para desplegar la aplicación en un contenedor.

- **docker-compose.yml**: 
  Permite orquestar múltiples servicios utilizando [Docker Compose](https://docs.docker.com/compose/). Facilita la configuración y gestión de contenedores como Nginx y la aplicación misma.

- **requirements.txt**: 
  Lista de dependencias de Python necesarias para ejecutar el proyecto. Puedes instalarlas con el comando:
  ```bash
  pip install -r requirements.txt
  ```

## Cómo comenzar
### Clona este repositorio.

**Crea y activa el entorno virtual:**
```bash
python -m venv .venv
.venv\Scripts\activate      # En Windows
```
**Instala las dependencias:**  

```bash
pip install -r requirements.txt
```

**Levanta los servicios usando Docker Compose:**
```bash
docker-compose up
```