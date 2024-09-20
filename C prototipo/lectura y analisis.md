## Analisis ##
La API está organizada en diferentes módulos para manejar usuarios, dispositivos, datos de dispositivos, configuraciones, proyectos y seguridad. Cada módulo tiene endpoints CRUD (Crear, Leer, Actualizar, Eliminar) bien definidos.

# Autenticación #
-Se requiere una clave de API para acceder a los recursos, lo que asegura que solo los usuarios autorizados puedan hacer solicitudes.

# Usuarios #
-Permite gestionar la información de los usuarios, incluyendo la creación, actualización y eliminación.

# Dispositivos #
-Proporciona endpoints para gestionar dispositivos, permitiendo registrar, modificar y eliminar dispositivos en la base de datos.

# Datos de Dispositivos #
-Facilita la gestión de los datos que los dispositivos recopilan, permitiendo registrar nuevos datos y actualizar los existentes.

# Configuraciones #
-Permite gestionar las configuraciones de los dispositivos, asegurando que se puedan ajustar parámetros de funcionamiento.

# Proyectos #
Maneja la creación y modificación de proyectos, asociando a los usuarios y dispositivos relevantes.

# Seguridad #
Administra los permisos de acceso de los usuarios a los dispositivos, asegurando que cada usuario tenga los permisos adecuados.


## MODULO 1 ##
# Usuarios #

Obtener Usuarios 
Método: GET
URL: /usuarios/
Descripción: Obtiene una lista de todos los usuarios.
Respuesta: Lista de usuarios con id, nombre, y email.
Obtener Usuario

Método: GET
URL: /usuarios/<int:id>
Descripción: Obtiene los detalles de un usuario específico por id.
Respuesta: Datos del usuario correspondiente.
Crear Usuario

Método: POST
URL: /usuarios/
Descripción: Crea un nuevo usuario.
Cuerpo: nombre, email, rol, password.
Respuesta: 201 Created.
Actualizar Usuario

Método: PUT
URL: /usuarios/<int:id>
Descripción: Actualiza los datos de un usuario existente.
Cuerpo: nombre, email, rol, password.
Respuesta: 204 No Content.
Borrar Usuario

Método: DELETE
URL: /usuarios/<int:id>
Descripción: Elimina un usuario.
Respuesta: 204 No Content.

## MODULO 2 ##
# Dispositivos #

Obtener Dispositivos 
Método: GET
URL: /dispositivos/
Descripción: Obtiene una lista de todos los dispositivos.
Respuesta: Lista de dispositivos con id, nombre, tipo, ubicacion, y id_usuario.
Obtener Dispositivo

Método: GET
URL: /dispositivos/<int:id>
Descripción: Obtiene los detalles de un dispositivo específico por id.
Respuesta: Datos del dispositivo correspondiente.
Crear Dispositivo

Método: POST
URL: /dispositivos/
Descripción: Crea un nuevo dispositivo.
Cuerpo: nombre, tipo, ubicacion, id_usuario.
Respuesta: 201 Created.
Actualizar Dispositivo

Método: PUT
URL: /dispositivos/<int:id>
Descripción: Actualiza un dispositivo existente.
Cuerpo: nombre, tipo, ubicacion, id_usuario.
Respuesta: 204 No Content.
Borrar Dispositivo

Método: DELETE
URL: /dispositivos/<int:id>
Descripción: Elimina un dispositivo.
Respuesta: 204 No Content.

## modulo 3 ##
# Datos de Dispositivos #

Obtener Datos de Dispositivos
Método: GET
URL: /datos_dispositivos/
Descripción: Obtiene una lista de datos registrados para dispositivos.
Respuesta: Lista de datos con id, dispositivo_id, timestamp, valor, y unidad.
Obtener Dato de Dispositivo

Método: GET
URL: /datos_dispositivos/<int:id>
Descripción: Obtiene los datos de un dispositivo específico por id.
Respuesta: Datos correspondientes.
Enviar Datos de Dispositivo

Método: POST
URL: /datos_dispositivos/
Descripción: Envía nuevos datos para un dispositivo.
Cuerpo: dispositivo_id, valor, unidad.
Respuesta: 201 Created.
Actualizar Dato de Dispositivo

Método: PUT
URL: /datos_dispositivos/<int:id>
Descripción: Actualiza un dato existente para un dispositivo.
Cuerpo: dispositivo_id, valor, unidad.
Respuesta: 204 No Content.
Borrar Dato de Dispositivo

Método: DELETE
URL: /datos_dispositivos/<int:id>
Descripción: Elimina un dato específico para un dispositivo.
Respuesta: 204 No Content.

## MODULO 4 ##
# Configuraciones #

Obtener Configuraciones 
Método: GET
URL: /configuraciones/
Descripción: Obtiene una lista de todas las configuraciones.
Respuesta: Lista de configuraciones con id_configuracion, id_dispositivo, parametro, y valor.
Obtener Configuración

Método: GET
URL: /configuraciones/<int:id>
Descripción: Obtiene una configuración específica por id.
Respuesta: Datos de configuración correspondientes.
Enviar Configuración

Método: POST
URL: /configuraciones/
Descripción: Envía una nueva configuración.
Cuerpo: id_dispositivo, parametro, valor.
Respuesta: 201 Created.
Actualizar Configuración

Método: PUT
URL: /configuraciones/<int:id>
Descripción: Actualiza una configuración existente.
Cuerpo: id_dispositivo, parametro, valor.
Respuesta: 204 No Content.
Borrar Configuración

Método: DELETE
URL: /configuraciones/<int:id>
Descripción: Elimina una configuración.
Respuesta: 204 No Content.

## MODULO 5 ##
# Proyectos #

Obtener Proyectos 
Método: GET
URL: /proyectos/
Descripción: Obtiene una lista de todos los proyectos.
Respuesta: Lista de proyectos con id_proyecto, nombre, descripcion, id_usuario, fecha_inicio, y fecha_fin.
Obtener Proyecto

Método: GET
URL: /proyectos/<int:id>
Descripción: Obtiene un proyecto específico por id.
Respuesta: Datos del proyecto correspondiente.
Enviar Proyecto

Método: POST
URL: /proyectos/
Descripción: Envía un nuevo proyecto.
Cuerpo: nombre, descripcion, id_usuario, fecha_inicio, fecha_fin.
Respuesta: 201 Created.
Actualizar Proyecto

Método: PUT
URL: /proyectos/<int:id>
Descripción: Actualiza un proyecto existente.
Cuerpo: nombre, descripcion, id_usuario, fecha_inicio, fecha_fin.
Respuesta: 204 No Content.
Borrar Proyecto

Método: DELETE
URL: /proyectos/<int:id>
Descripción: Elimina un proyecto específico por id.
Respuesta: 204 No Content.

## MODULO 6 ##
# Seguridad #

Obtener Información de Seguridad 
Método: GET
URL: /seguridad/
Descripción: Obtiene una lista de entradas de seguridad.
Respuesta: Lista de entradas con id_seguridad, id_usuario, id_dispositivo, y permisos.
Obtener Registro de Seguridad

Método: GET
URL: /seguridad/<int:id>
Descripción: Obtiene un registro de seguridad específico.
Respuesta: Datos del registro correspondiente.
Enviar Registro de Seguridad

Método: POST
URL: /seguridad/
Descripción: Envía una nueva entrada de seguridad.
Cuerpo: id_usuario, id_dispositivo, permisos.
Respuesta: 201 Created.
Actualizar Registro de Seguridad

Método: PUT
URL: /seguridad/<int:id>
Descripción: Actualiza una entrada de seguridad existente.
Cuerpo: id_usuario, id_dispositivo, permisos.
Respuesta: 204 No Content.
Borrar Registro de Seguridad

Método: DELETE
URL: /seguridad/<int:id>
Descripción: Elimina una entrada de seguridad.
Respuesta: 204 No Content.