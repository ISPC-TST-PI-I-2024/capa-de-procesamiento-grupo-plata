# Capa de Procesamiento

## Subtítulo: Desarrollo de Middleware y Adaptación de la Base de Datos

### Objetivos:
1. Familiarizarse con la API RESTful proporcionada y su interacción con la base de datos.
2. Realizar prácticas de CRUD utilizando Python para manipular datos en la base de datos.
3. Implementar la conexión de dispositivos Edge (ESP32) con la API para la interacción con la base de datos.
4. Desarrollar un middleware utilizando Flask que actúe como puente entre los dispositivos Edge y la API RESTful.
5. Documentar exhaustivamente el proceso de desarrollo y adaptación del middleware.

---

## Desarrollo

Esta tarea se divide en tres etapas que tienen como objetivo guiar a los alumnos en la adaptación de la base de datos genérica proporcionada, la interacción con los dispositivos del Edge y la implementación de un middleware con Flask. La práctica está diseñada para ser realizada en tres semanas, cada una centrada en una parte específica del desarrollo.

### Guía Detallada Paso a Paso

---

#### **Semana 20: Interacción con la Base de Datos y la API RESTful**

1. **Repaso del Manual de la API RESTful:**
   - Leer el manual de la API para comprender los endpoints disponibles y su funcionamiento.
   - Identificar los endpoints relevantes para las operaciones CRUD (Create, Read, Update, Delete) en la base de datos.

2. **Prácticas CRUD con Python:**
   - Configurar un entorno de desarrollo en Python para interactuar con la API RESTful.
   - Realizar prácticas de operaciones CRUD (GET, POST, PUT, DELETE) utilizando Python y la API RESTful.
   - Asegurarse de manejar correctamente las respuestas y errores de la API.

3. **Manejo del Almacenamiento Limitado:**
   - Analizar el almacenamiento disponible en el servidor (Raspberry Pi 4B+).
   - Implementar buenas prácticas para evitar el desbordamiento del almacenamiento, como la limpieza periódica de datos innecesarios.

4. **Conexión Remota con el Servidor:**
   - Aprender a conectarse al servidor de la Raspberry Pi utilizando SSH.
   - Realizar operaciones básicas en el sistema operativo del servidor, como verificar el estado de la API y la base de datos.
   - Documentar cualquier hallazgo o ajuste realizado durante este proceso.

---

#### **Semana 21: Interacción con Dispositivos Edge (ESP32)**

1. **Configuración del Entorno de Desarrollo:**
   - Configurar el entorno de desarrollo para el ESP32 utilizando VSCode y PlatformIO.
   - Revisar el código para la conexión del ESP32 con la red y la interacción con la API RESTful.

2. **Prácticas CRUD desde el Edge:**
   - Implementar operaciones CRUD en la base de datos desde el ESP32, utilizando la API RESTful.
   - Configurar la percepción (sensores, actuadores, visualizadores) en el ESP32 para recopilar y enviar datos a la base de datos a través de la API.
   - Probar y validar la comunicación entre el ESP32 y la API.

3. **Manejo de Errores y Almacenamiento:**
   - Implementar mecanismos en el ESP32 para manejar errores de comunicación con la API.
   - Establecer un sistema de almacenamiento local temporal en caso de pérdida de conexión.

---

#### **Semana 22: Desarrollo del Middleware con Flask**

1. **Definición del Middleware:**
   - Definir las funcionalidades que el middleware debe proporcionar para adaptarse a las necesidades de los dispositivos Edge.
   - Esquematizar cómo el middleware actuará como intermediario entre los dispositivos Edge y la API RESTful.

2. **Implementación del Middleware:**
   - Desarrollar el middleware utilizando Flask.
   - Implementar funciones en el middleware para transformar y adaptar los datos enviados por los dispositivos Edge.
   - Configurar rutas en el middleware que permitan la interacción con la API RESTful.

3. **Integración y Pruebas:**
   - Integrar el middleware con los dispositivos Edge y la API RESTful.
   - Realizar pruebas exhaustivas para asegurar que el middleware cumple con su propósito y que los datos se almacenan correctamente en la base de datos.

4. **Documentación:**
   - Documentar detalladamente el proceso de desarrollo del middleware, incluyendo esquemas de arquitectura, flujos de datos y justificaciones técnicas.
   - Elaborar un manual de uso del middleware que incluya ejemplos de interacción desde el Edge.

---

## Entrega Final:
- Código del middleware desarrollado.
- Documentación completa del proceso, incluida la adaptación de la base de datos, interacción con la API y detalles técnicos del middleware.
- Informe con los resultados de las pruebas y validaciones realizadas en cada etapa del desarrollo.
- Repositorio de desarrollo: [https://classroom.github.com/a/orSi9ChT](https://classroom.github.com/a/orSi9ChT)
- **Fecha límite de presentación:** 05 de Octubre a las 23:59
