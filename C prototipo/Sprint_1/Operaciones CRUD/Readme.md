# Operaciones CRUD con la API

Este proyecto implementa y prueba las operaciones CRUD (Create, Read, Update, Delete) utilizando Python para interactuar con la API RESTful alojada en `https://api.gonaiot.com/plata`.

## Explicación:  

### Encabezados (headers):   
Se añade la clave API Plata en el campo X-API-KEY dentro de los headers para todas las solicitudes.  

### Base URL:  
Definimos la URL base https://api.gonaiot.com/plata/datos_dispositivos/, la cual es utilizada en cada operación.
  
## Operaciones CRUD:  

**GET:** Obtiene todos los datos de dispositivos.
**POST:** Inserta un nuevo registro en la base de datos.
**PUT:** Actualiza un registro existente con ID 1.
**DELETE:** Elimina un registro con ID 1.

### Manejo de errores  

Se ha implementado manejo básico de errores para cada operación, verificando el código de estado de las respuestas HTTP y mostrando mensajes apropiados en caso de fallos.