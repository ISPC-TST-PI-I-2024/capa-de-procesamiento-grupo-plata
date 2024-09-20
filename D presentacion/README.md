
# Capa de Procesamiento

Este directorio está dedicado a la presentación de la **Capa de Procesamiento** en el contexto de nuestro proyecto IoT para el monitoreo y análisis de la calidad del aire. Esta capa es fundamental para el tratamiento y manejo de los datos obtenidos por los dispositivos distribuidos en distintas ubicaciones de la ciudad o interiores.

## Objetivo de la Capa de Procesamiento

La **Capa de Procesamiento** se encarga de recibir, procesar y almacenar los datos enviados por los sensores IoT a través de las capas de percepción y almacenamiento. El propósito principal es transformar los datos en bruto en información útil, facilitando su análisis y permitiendo la toma de decisiones en tiempo real o con base en tendencias históricas.

## Prácticas a Realizar

Durante el desarrollo de esta capa, se llevarán a cabo las siguientes prácticas:

1. **Interacción con APIs RESTful:** Configuración de una API RESTful que permita la comunicación entre los dispositivos Edge (ESP32) y la base de datos. Esto permitirá gestionar las operaciones CRUD (Crear, Leer, Actualizar, Eliminar) sobre los datos recopilados por los sensores.
   
2. **Procesamiento de Datos:** Implementación de un middleware basado en **Flask** que actuará como un puente entre los dispositivos Edge y la API RESTful. Este middleware procesará los datos en tiempo real antes de enviarlos a la base de datos para su almacenamiento.
   
3. **Manejo de Bases de Datos:** Uso de **MySQL** para la manipulación y almacenamiento de los datos provenientes de los sensores. Se realizarán consultas y prácticas de optimización de la base de datos.

4. **Integración con Dispositivos Edge:** Conexión de dispositivos ESP32 a la API para la transferencia de datos de manera eficiente y segura.

5. **Documentación Exhaustiva:** Cada paso del desarrollo y la adaptación del middleware será documentado de manera exhaustiva para garantizar un flujo de trabajo claro y replicable.

## Stack Tecnológico

El desarrollo de esta capa utilizará las siguientes herramientas y tecnologías:

- **Lenguaje de Programación:** Python
- **Framework Backend:** Flask (para la creación de la API RESTful y el middleware)
- **Bases de Datos Relacionales:** MySQL
- **Microcontroladores IoT:** ESP32
- **Entorno de Desarrollo:** Visual Studio Code con integración de entornos virtuales de Python
- **Herramientas de Gestión de Dependencias:** Pipenv o entornos virtuales (`venv`)

