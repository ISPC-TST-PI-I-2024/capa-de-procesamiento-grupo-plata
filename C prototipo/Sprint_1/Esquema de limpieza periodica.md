# Esquema para la Limpieza Periódica de Datos
## Introducción  
La limpieza periódica de datos es una práctica fundamental para mantener la salud y eficiencia de una base de datos. Al eliminar datos innecesarios o antiguos, se optimiza el rendimiento, se reduce el almacenamiento y se mejora la calidad de la información.  
--- 

## Definición de Datos a Eliminar
1. Datos duplicados: Identificar y eliminar registros idénticos o casi idénticos (se define unmbral de variacion en funcion del sensor utilizado).
2. Datos obsoletos: Establecer criterios de antigüedad para eliminar registros que hayan superado su utilidad (ej: logs de más de 12 meses).
3. Datos incorrectos: Eliminar registros con información errónea o inconsistente.
4. Datos redundantes: Identificar y eliminar datos que se encuentran duplicados en diferentes tablas o sistemas.

## Proceso de Limpieza
### Análisis de los datos:
- Identificar las fuentes de datos: Determinar todas las bases de datos y archivos que contienen los datos a limpiar.
- Evaluar la calidad de los datos: Analizar la integridad, consistencia y precisión de los datos.
- Definir los criterios de eliminación: Establecer reglas claras y objetivas para determinar qué datos se eliminarán.
### Desarrollo de scripts o consultas:
- Crear scripts SQL: Desarrollar consultas SQL para identificar y eliminar los datos según los criterios establecidos.
- Utilizar herramientas de ETL: Emplear herramientas de extracción, transformación y carga (ETL) para automatizar el proceso de limpieza.
### Pruebas:
- Ejecutar los scripts en un entorno de pruebas: Verificar que los scripts eliminen los datos correctos y no afecten a otros datos.
- Realizar copias de seguridad: Crear copias de seguridad antes de ejecutar los scripts en producción.
### Ejecución de la limpieza:
* Programar la ejecución: Establecer una frecuencia para ejecutar los scripts de limpieza (diario, semanal, mensual).
* Monitorear el proceso: Supervisar la ejecución de los scripts y verificar que se completen correctamente.
### Documentación:

- Registrar los criterios de eliminación: Documentar las reglas y criterios utilizados para identificar los datos a eliminar.
- Describir los scripts: Documentar los scripts SQL o las herramientas ETL utilizadas.
- Registrar el historial de limpieza: Mantener un registro de las fechas de ejecución, los datos eliminados y cualquier incidencia ocurrida.

### Ejemplo de bloque SQL 
``` SQL
SQL
DELETE FROM mediciones
WHERE id IN (
    SELECT id
    FROM (
        SELECT id, valor,
               LAG(valor) OVER (ORDER BY fecha_hora) AS valor_anterior
        FROM mediciones
    ) AS subquery
    WHERE ABS(valor - valor_anterior) < 0.5  -- Umbral de variación
      AND fecha_hora BETWEEN NOW() - INTERVAL '7 days' AND NOW()
);
```


### Ejemplo para identificar y eliminar datos duplicados.

``` Python
import psycopg2

def eliminar_duplicados(conn, cursor, tabla, columna_valor, umbral):
    """Elimina registros duplicados en una tabla, considerando un umbral de variación.

    Args:
        conn: Conexión a la base de datos.
        cursor: Cursor de la conexión.
        tabla: Nombre de la tabla.
        columna_valor: Nombre de la columna con el valor a comparar.
        umbral: Valor máximo de diferencia permitida entre valores consecutivos.
    """

    cursor.execute(f"""
        DELETE FROM {tabla}
        WHERE id IN (
            SELECT id
            FROM (
                SELECT id, {columna_valor},
                       LAG({columna_valor}) OVER (ORDER BY fecha_hora) AS valor_anterior
                FROM {tabla}
            ) AS subquery
            WHERE ABS({columna_valor} - valor_anterior) < {umbral}
        )
    """)

# Ejemplo de uso:
conn = psycopg2.connect(database="mydatabase", user="myuser", password="mypassword", host="myhost")
cursor = conn.cursor()

eliminar_duplicados(conn, cursor, 'mediciones', 'temperatura', 1)  # Elimina registros con temperatura que varíe menos de 1 grado Cº
conn.commit()
conn.close()

```

### Ejemplo Eliminar datos obsoletos
```Python
def eliminar_datos_obsoletos(conn, cursor, tabla, columna_fecha, meses):
    """Elimina registros de una tabla con una fecha anterior a un número determinado de meses.

    Args:
        conn: Conexión a la base de datos.
        cursor: Cursor de la conexión.
        tabla: Nombre de la tabla.
        columna_fecha: Nombre de la columna con la fecha.
        meses: Número de meses para considerar como obsoleto.
    """

    cursor.execute(f"""
        DELETE FROM {tabla}
        WHERE {columna_fecha} < NOW() - INTERVAL '{meses} month'
    """)

# Ejemplo de uso:
eliminar_datos_obsoletos(conn, cursor, 'logs', 'fecha_registro', 12)
```
### Ejemplo Identificar y eliminar datos incorrectos, fuera de rango.

``` Python
def eliminar_datos_incorrectos(conn, cursor, tabla, columna_valor, rango_min, rango_max):
    """Elimina registros con valores fuera de un rango especificado.

    Args:
        conn: Conexión a la base de datos.
        cursor: Cursor de la conexión.
        tabla: Nombre de la tabla.
        columna_valor: Nombre de la columna con el valor a validar.
        rango_min: Valor mínimo permitido.
        rango_max: Valor máximo permitido.
    """

    cursor.execute(f"""
        DELETE FROM {tabla}
        WHERE {columna_valor} < {rango_min} OR {columna_valor} > {rango_max}
    """)

# Ejemplo de uso:
eliminar_datos_incorrectos(conn, cursor, 'mediciones', 'humedad', 0, 100)
```