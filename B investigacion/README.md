# Investigación del Proyecto de Monitoreo de Calidad del Aire

Este proyecto está diseñado siguiendo la metodología de **Aprendizaje Basado en Problemas (ABP)**, cuyo objetivo es desarrollar un sistema IoT para monitorear la calidad del aire a nivel de ciudad. La capa de procesamiento se centra en la recolección, filtrado y normalización de los datos provenientes de diferentes sensores, así como su transmisión para análisis en la nube.

## Estructura del Proyecto

- **requisitos/**: Contiene la recopilación de los requisitos del proyecto.
- **investigacion/**: En esta carpeta se documentan los aspectos investigados para la implementación del sistema, especialmente en la capa de procesamiento.
- **prototipo/**: Desarrollo del prototipo del sistema, que incluye la implementación física y simulada.
- **presentacion/**: Documentación final y presentaciones del proyecto.

## Capa de Procesamiento

En esta sección se exploran las soluciones investigadas para procesar los datos localmente, incluyendo el uso de dispositivos edge para aplicar filtros y lógicas de normalización. La capa de procesamiento es crítica para la toma de decisiones en tiempo real antes de transmitir los datos a la nube.

### Objetivos de la Capa de Procesamiento

- **Recolección de Datos**: Utilizar sensores de temperatura, humedad, y niveles de luz para medir la calidad del aire.
- **Filtrado y Normalización**: Procesar los datos localmente para garantizar su precisión y coherencia.
- **Automatización de Tareas**: Implementar decisiones en tiempo real, como el control automático de riego en áreas verdes de la ciudad.

## Documentos de Investigación

Los siguientes documentos contienen información clave sobre la implementación de la capa de procesamiento:

1. **Manual de API RESTful**: Este documento describe el proyecto de una API RESTful diseñada para
gestionar datos de un sistema IoT (Internet de las Cosas). La API está construida utilizando el framework Flask en Python y se integra con una base de datos MySQL.
2. **Metodologías de Procesamiento Local**: Exploración de técnicas para el procesamiento de datos en dispositivos edge.
3. **Filtrado y Normalización de Datos**: Técnicas aplicadas para limpiar y preparar los datos antes de su transmisión a la nube o Servidor.
4. **API RESTful Parte 1 y 2**: Aprender a construir y usar APIs REST te permitirá estructurar la comunicación entre el frontend y el backend de tu aplicación. JSON es el formato de datos más comúnmente usado para este propósito.
5. **Configurar Entorno Python**: Guia rapida para configurar el entorno Python y hacer un test de una API.

## Resultado

La capa de procesamiento juega un rol vital en el proyecto, ya que garantiza la calidad de los datos procesados y permite que las decisiones automatizadas mejoren la eficiencia de la gestión ambiental de la ciudad.


