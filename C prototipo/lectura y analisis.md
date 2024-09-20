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



---------------------------------------------------------MODULOS--------------------------------------------------------------------------- 

## Configuraciones ##
Archivo: configuraciones.py
Descripción: Este módulo maneja las operaciones CRUD para las configuraciones de los dispositivos IoT.
• GET /configuraciones/: Obtiene todas las configuraciones.
• GET /configuraciones/int:id: Obtiene una configuración específica por ID.
• POST /configuraciones/: Crea una nueva configuración.
• PUT /configuraciones/int:id: Actualiza una configuración existente por ID.
• DELETE /configuraciones/int:id: Elimina una configuración por ID.

## Datos Dispositivos ##
Archivo: datos_dispositivos.py
Descripción: Este módulo maneja las operaciones CRUD para los datos recolectados por los dispositivos IoT.
• GET /datos_dispositivos/: Obtiene todos los datos de dispositivos.
• GET /datos_dispositivos/int:id: Obtiene un dato específico por ID.
• POST /datos_dispositivos/: Crea un nuevo dato de dispositivo.
• PUT /datos_dispositivos/int:id: Actualiza un dato de dispositivo existente por ID.
• DELETE /datos_dispositivos/int:id: Elimina un dato de dispositivo por ID.

## Dispositivos ##
Archivo: dispositivos.py
Descripción: Este módulo maneja las operaciones CRUD para los dispositivos IoT.
• GET /dispositivos/: Obtiene todos los dispositivos.
• GET /dispositivos/int:id: Obtiene un dispositivo específico por ID.
• POST /dispositivos/: Crea un nuevo dispositivo.
• PUT /dispositivos/int:id: Actualiza un dispositivo existente por ID.
• DELETE /dispositivos/int:id: Elimina un dispositivo por ID.

## Proyectos ##
Archivo: proyectos.py
Descripción: Este módulo maneja las operaciones CRUD para los proyectos de IoT.
• GET /proyectos/: Obtiene todos los proyectos.
• GET /proyectos/int:id: Obtiene un proyecto específico por ID.
• POST /proyectos/: Crea un nuevo proyecto.
• PUT /proyectos/int:id: Actualiza un proyecto existente por ID.
• DELETE /proyectos/int:id: Elimina un proyecto por ID.

## Seguridad ##
Archivo: seguridad.py
Descripción: Este módulo maneja las operaciones CRUD para la gestión de seguridad.
• GET /seguridad/: Obtiene todos los registros de seguridad.
• GET /seguridad/int:id: Obtiene un registro de seguridad específico por ID.
• POST /seguridad/: Crea un nuevo registro de seguridad.
• PUT /seguridad/int:id: Actualiza un registro de seguridad existente por ID.
• DELETE /seguridad/int:id: Elimina un registro de seguridad por ID.

## Usuarios ##
Archivo: usuarios.py
Descripción: Este módulo maneja las operaciones CRUD para los usuarios del sistema IoT.
• GET /usuarios/: Obtiene todos los usuarios.
• GET /usuarios/int:id: Obtiene un usuario específico por ID.
• POST /usuarios/: Crea un nuevo usuario.
• PUT /usuarios/int:id: Actualiza un usuario existente por ID.
• DELETE /usuarios/int:id: Elimina un usuario por ID.