# Proyecto IoT: API RESTful

Este proyecto proporciona una API RESTful para gestionar datos de un proyecto IoT utilizando Flask y MySQL. La API soporta operaciones CRUD para varias entidades como usuarios, dispositivos, proyectos, configuraciones, datos de dispositivos y seguridad.

## Estructura del Proyecto

``` bash
c_capa_de_analisis/
├── app.py
├── db_config.py
├── models.py
├── routes/
│ ├── configuraciones.py
│ ├── datos_dispositivos.py
│ ├── dispositivos.py
│ ├── proyectos.py
│ ├── seguridad.py
│ └── usuarios.py
├── requirements.txt
└── Dockerfile
```

## Instalación

1. Clonar el repositorio.
2. Navegar al directorio del proyecto.
3. Ejecutar `pip install -r requirements.txt` para instalar las dependencias.
4. Configurar la base de datos en `db_config.py`.
5. Ejecutar `python app.py` para iniciar el servidor.

## Uso

### Endpoints

La API proporciona los siguientes endpoints:

#### Usuarios

1. **Obtener Usuarios**
   - **Método**: `GET`
   - **URL**: `/usuarios/`
   - **Descripción**: Devuelve una lista de todos los usuarios registrados en la base de datos.
   - **Respuesta**:
     ```json
     [
       {
         "id": 1,
         "nombre": "Juan Perez",
         "email": "juan.perez@example.com"
       },
       ...
     ]
     ```  

2. **Obtener Usuario**
   - **Método**: `GET`
   - **URL**: `/usuarios/<int:id>`
   - **Descripción**: Devuelve una lista con los datos del usuario registrado con un id específico.
   - **Respuesta**:
     ```json
     [
       {
         "id": 1,
         "nombre": "Juan Perez",
         "email": "juan.perez@example.com"
       },
     ]
     ```

3. **Crear Usuario**
    - **Método**: `POST`
    - **URL**: `/usuarios/`
    - **Descripción**: Crea un nuevo usuario en la base de datos.
    - **Cuerpo de la Solicitud**:
      ```json
      {
        "nombre": "Juan Perez",
        "email": "juan.perez@example.com",
        "rol": "admin", 
        "password": "password123"
      }
      ```
    - **Respuesta**: Código de estado `201 Created` si se crea con éxito.

4. **Actualizar usuario**
    - **Método**: `PUT`
    - **URL**: `/usuarios/<int:id>`
    - **Descripción**: Actualiza un usuario existente en la base de datos.
    - **Cuerpo de la Solicitud**:
    ```json
      {
        "nombre": "Juan Alberto Perez",
        "email": "juan.a.perez@example.com",
        "rol": "user", 
        "password": "password987"
      }
      ```
    - **Respuesta**: Código de estado `204 No Content` si se crea con éxito.

5. **Borrar usuario**
    - **Método**: `DELETE`
    - **URL**: `/usuarios/<int:id>`
    - **Descripción**: Elimina un usuario existente en la base de datos.
    - **Cuerpo de la Solicitud**:

    - **Respuesta**: Código de estado `204 No Content` si se elimina el usuario con éxito.

#### Dispositivos

1. **Obtener Dispositivos**
   - **Método**: `GET`
   - **URL**: `/dispositivos/`
   - **Descripción**: Devuelve una lista de todos los dispositivos registrados en la base de datos.
   - **Respuesta**:
     ```json
     [
       {
         "id": 1,
         "nombre": "Estation_1",
         "tipo": "Nodo medicion calidad aire",
         "ubicacion": "31°26'46.9\"S 64°10'28.8\"W",
         "id_usuario": "3"
       },
       ...
     ]
     ```  

2. **Obtener Dispositivo**
   - **Método**: `GET`
   - **URL**: `/dispositivos/<int:id>`
   - **Descripción**: Devuelve una lista con los datos del dispositivo registrado con un id específico.
   - **Respuesta**:
     ```json
     [
       {
          "id": 1,
         "nombre": "Estation_1",
         "tipo": "Nodo medicion calidad aire",
         "ubicacion": "31°26'46.9\"S 64°10'28.8\"W",
         "id_usuario": "3"
       },
     ]
     ```

3. **Crear Dispositivo**
    - **Método**: `POST`
    - **URL**: `/dispositivos/`
    - **Descripción**: Crea un nuevo dispositivo en la base de datos.
    - **Cuerpo de la Solicitud**:
      ```json
      [
        {
          "nombre": "Estation_2",
          "tipo": "Nodo medicion viento",
          "ubicacion": "31°26'46.9\"S 64°10'28.8\"W",
          "id_usuario": "2"
        },
      ]
      ```
    - **Respuesta**: Código de estado `201 Created` si se crea con éxito.

4. **Actualizar Dispositivo**
    - **Método**: `PUT`
    - **URL**: `/dispositivos/<int:id>`
    - **Descripción**: Actualiza un dispositivo existente en la base de datos.
    - **Cuerpo de la Solicitud**:
    ```json
      
      {
        "nombre": "Estation_2",
        "tipo": "Nodo medicion viento y calidad de aire",
        "ubicacion": "31°26'46.9\"S 64°10'28.8\"W",
        "id_usuario": "2"
      },
      
      ```
    - **Respuesta**: Código de estado `204 No Content` si se crea con éxito.

5. **Borrar Dispositivo**
    - **Método**: `DELETE`
    - **URL**: `/dispositivos/<int:id>`
    - **Descripción**: Elimina un dispositivo existente en la base de datos.
    - **Cuerpo de la Solicitud**:

    - **Respuesta**: Código de estado `204 No Content` si se elimina el usuario con éxito.

#### Datos de Dispositivos

1. **Obtener Datos de Dispositivos**
   - **Método**: `GET`
   - **URL**: `/datos_dispositivos/`
   - **Descripción**: Devuelve una lista de los datos registrados para los dispositivos.
   - **Respuesta**:
     ```json
     [
       {
         "id": 1,
         "dispositivo_id": 1,
         "timestamp": "2024-06-24T00:00:00Z",
         "valor": 23.5,
         "unidad": "C"
       },
       ...
     ]
     ```

2. **Obtener Dato de Dispositivo**
   - **Método**: `GET`
   - **URL**: `/datos_dispositivos/<int:id>`
   - **Descripción**: Devuelve una lista con los datos registrados para un dispositivo específico.
   - **Respuesta**:
     ```json
     [
       {
         "id": 1,
         "dispositivo_id": 1,
         "timestamp": "2024-06-24T00:00:00Z",
         "valor": 23.5,
         "unidad": "C"
       },
     ]
     ```

3. **Enviar Datos de Dispositivo**
   - **Método**: `POST`
   - **URL**: `/datos_dispositivos/`
   - **Descripción**: Envia nuevos datos para un dispositivo.
   - **Cuerpo de la Solicitud**:
     ```json
     {
       "dispositivo_id": 1,
       "valor": 23.5,
       "unidad": "C"
     }
     ```
   - **Respuesta**: Código de estado `201 Created` si se envía con éxito.  

4. **Actualizar Dato de Dispositivo**
    - **Método**: `PUT`
    - **URL**: `/datos_dispositivos/<int:id>`
    - **Descripción**: Actualiza el dato cargado por un dispositivo existente en la base de datos.
    - **Cuerpo de la Solicitud**:
    ```json
      
      {
        "dispositivo_id": 1,
       "valor": 27.5,
       "unidad": "C"
      },
      
      ```
    - **Respuesta**: Código de estado `204 No Content` si se crea con éxito.

5. **Borrar Dato de Dispositivo**
    - **Método**: `DELETE`
    - **URL**: `/datos_dispositivos/<int:id>`
    - **Descripción**: Elimina un dato cargado por un dispositivo existente en la base de datos.
    - **Cuerpo de la Solicitud**:

    - **Respuesta**: Código de estado `204 No Content` si se elimina el usuario con éxito.

#### Configuraciones

1. **Obtener Configuraciones**
   - **Método**: `GET`
   - **URL**: `/configuraciones/`
   - **Descripción**: Devuelve una lista de todas las configuraciones registradas.
   - **Respuesta**:
     ```json
     [
       {
         "id_configuracion": 1,
         "id_dispositivo": 1,
         "parametro": "intervalo_muestreo",
         "valor": "10s"
       },
       ...
     ]
     ```

2. **Obtener Configuración**
   - **Método**: `GET`
   - **URL**: `/configuraciones/<int:id>`
   - **Descripción**: Devuelve la configuración específica correspondiente al ID proporcionado.
   - **Respuesta**:
     ```json
     {
       "id_configuracion": 1,
       "id_dispositivo": 1,
       "parametro": "intervalo_muestreo",
       "valor": "10s"
     }
     ```

3. **Enviar Configuración**
   - **Método**: `POST`
   - **URL**: `/configuraciones/`
   - **Descripción**: Envía una nueva configuración para un dispositivo.
   - **Cuerpo de la Solicitud**:
     ```json
     {
       "id_dispositivo": 1,
       "parametro": "intervalo_muestreo",
       "valor": "10s"
     }
     ```
   - **Respuesta**: Código de estado `201 Created` si se envía con éxito.

4. **Actualizar Configuración**
    - **Método**: `PUT`
    - **URL**: `/configuraciones/<int:id>`
    - **Descripción**: Actualiza la configuración existente para el ID proporcionado.
    - **Cuerpo de la Solicitud**:
      ```json
      {
        "id_dispositivo": 1,
        "parametro": "intervalo_muestreo",
        "valor": "15s"
      }
      ```
    - **Respuesta**: Código de estado `204 No Content` si se actualiza con éxito.

5. **Borrar Configuración**
    - **Método**: `DELETE`
    - **URL**: `/configuraciones/<int:id>`
    - **Descripción**: Elimina la configuración correspondiente al ID proporcionado.
    - **Respuesta**: Código de estado `204 No Content` si se elimina con éxito.


#### Proyectos

1. **Obtener Proyectos**
   - **Método**: `GET`
   - **URL**: `/proyectos/`
   - **Descripción**: Devuelve una lista de todos los proyectos registrados.
   - **Respuesta**:
     ```json
     [
       {
         "id_proyecto": 1,
         "nombre": "Proyecto Iot",
         "descripcion": "Medicion de calidad del aire",
         "id_usuario": 1,
         "fecha_inicio": "2024-01-01",
         "fecha_fin": "2024-12-31"
       },
       ...
     ]
     ```

2. **Obtener Proyecto**
   - **Método**: `GET`
   - **URL**: `/proyectos/<int:id>`
   - **Descripción**: Devuelve el proyecto específico correspondiente al ID proporcionado.
   - **Respuesta**:
     ```json
     {
        "id_proyecto": 1,
        "nombre": "Proyecto Iot",
        "descripcion": "Medicion de calidad del aire",
        "id_usuario": 1,
        "fecha_inicio": "2024-01-01",
        "fecha_fin": "2024-12-31"
     }
     ```

3. **Enviar Proyecto**
   - **Método**: `POST`
   - **URL**: `/proyectos/`
   - **Descripción**: Envía un nuevo proyecto.
   - **Cuerpo de la Solicitud**:
     ```json
     {
       "nombre": "Proyecto IoT",
       "descripcion": "Medicion de calidad del aire",
       "id_usuario": 1,
       "fecha_inicio": "2024-01-01",
       "fecha_fin": "2024-12-31"
     }
     ```
   - **Respuesta**: Código de estado `201 Created` si se envía con éxito.

4. **Actualizar Proyecto**
    - **Método**: `PUT`
    - **URL**: `/proyectos/<int:id>`
    - **Descripción**: Actualiza el proyecto existente para el ID proporcionado.
    - **Cuerpo de la Solicitud**:
      ```json
      {
        "nombre": "Proyecto Iot ",
        "descripcion": "Red de Alerta de Calidad del Aire",
        "id_usuario": 1,
        "fecha_inicio": "2024-01-01",
        "fecha_fin": "2024-12-31"
      }
      ```
    - **Respuesta**: Código de estado `204 No Content` si se actualiza con éxito.

5. **Borrar Proyecto**
    - **Método**: `DELETE`
    - **URL**: `/proyectos/<int:id>`
    - **Descripción**: Elimina el proyecto correspondiente al ID proporcionado.
    - **Respuesta**: Código de estado `204 No Content` si se elimina con éxito.

#### Seguridad

1. **Obtener Informacion de Seguridad**
   - **Método**: `GET`
   - **URL**: `/seguridad/`
   - **Descripción**: Devuelve una lista de todas las entradas de seguridad registradas.
   - **Respuesta**:
     ```json
     [
       {
         "id_seguridad": 1,
         "id_usuario": 1,
         "id_dispositivo": 1,
         "permisos": "admin"
       },
       ...
     ]
     ```

2. **Obtener registro de Seguridad**
   - **Método**: `GET`
   - **URL**: `/seguridad/<int:id>`
   - **Descripción**: Devuelve el registro de seguridad específico correspondiente al ID proporcionado.
   - **Respuesta**:
     ```json
     {
       "id_seguridad": 1,
       "id_usuario": 1,
       "id_dispositivo": 1,
       "permisos": "admin"
     }
     ```

3. **Enviar Registro de Seguridad**
   - **Método**: `POST`
   - **URL**: `/seguridad/`
   - **Descripción**: Envía una nueva entrada de seguridad para un dispositivo.
   - **Cuerpo de la Solicitud**:
     ```json
     {
       "id_usuario": 1,
       "id_dispositivo": 1,
       "permisos": "admin"
     }
     ```
   - **Respuesta**: Código de estado `201 Created` si se envía con éxito.

4. **Actualizar Registro de Seguridad**
    - **Método**: `PUT`
    - **URL**: `/seguridad/<int:id>`
    - **Descripción**: Actualiza la entrada de seguridad existente para el ID proporcionado.
    - **Cuerpo de la Solicitud**:
      ```json
      {
        "id_usuario": 1,
        "id_dispositivo": 1,
        "permisos": "user"
      }
      ```
    - **Respuesta**: Código de estado `204 No Content` si se actualiza con éxito.

5. **Borrar Registro de Seguridad**
    - **Método**: `DELETE`
    - **URL**: `/seguridad/<int:id>`
    - **Descripción**: Elimina la entrada de seguridad correspondiente al ID proporcionado.
    - **Respuesta**: Código de estado `204 No Content` si se elimina con éxito.

### Autenticación

Se requiere una clave de API para todas las solicitudes. La clave debe ser incluida en el encabezado `X-API-KEY`. Claves válidas incluyen `jade`, `opalo`, `rubi`, `topaz`, y `plata`.

```bash
curl -H "X-API-KEY: jade" https://api.gonaiot.com/plata/usuarios/
```	

## Licencia

Este proyecto está licenciado bajo los términos de la licencia MIT. Ver el archivo LICENSE para más detalles.