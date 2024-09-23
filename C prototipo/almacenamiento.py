import requests
import logging
from datetime import datetime, timedelta

# Configuración
BASE_URL = "https://api.gonaiot.com/plata/{endpoint}/"
API_KEY = "Plata"  # Reemplazar con la clave API real
LOG_FILE = "api_interactions.log"
CLEANING_INTERVAL = 7  # Días entre limpiezas (ajustar según tu esquema)
logging.basicConfig(filename=LOG_FILE, level=logging.INFO)

# Excepción personalizada
class APIError(Exception):
    pass


# Función auxiliar para hacer una solicitud HTTP
def make_request(method, endpoint, data=None, params=None):
    url = BASE_URL.format(endpoint=endpoint)
    headers = {"X-API-KEY": API_KEY, "Content-Type": "application/json"}
    response = requests.request(method, url, json=data, params=params, headers=headers)
    response.raise_for_status()  # Levantar una excepción para errores HTTP
    return response.json()


# Funciones para limpieza de datos (ajustar según tus tablas)
def limpiar_datos_sensores(umbral_variacion=0.5):
    """Elimina registros de mediciones con valores idénticos o con poca variación.

    Args:
        umbral_variacion (float, optional): Valor máximo de diferencia permitida entre valores consecutivos. Defaults to 0.5.
    """

    try:
        # Obtener últimos datos (ajustar endpoint y parámetros)
        ultimos_datos = make_request("GET", "datos_dispositivos")

        for dato in ultimos_datos:
            # Identificar y eliminar datos con poca variación (ejemplo)
            if dato["valor"] == get_valor_anterior(dato["sensor_id"]):
                delete_resource("datos_dispositivos", dato["id"])
            else:
                # Almacenar el nuevo valor como referencia para la próxima limpieza
                set_valor_anterior(dato["sensor_id"], dato["valor"])

        logging.info("Limpieza de datos de sensores realizada con éxito.")

    except APIError as e:
        logging.error(f"Error al limpiar datos de sensores: {str(e)}")


def get_valor_anterior(sensor_id):
    # Implementar lógica para obtener el valor anterior del sensor (ej: base de datos local)
    # En este ejemplo simulado, se retorna un valor fijo
    return 0.0


def set_valor_anterior(sensor_id, valor):
    # Implementar lógica para almacenar el valor actual como referencia (ej: base de datos local)
    # En este ejemplo simulado, no se almacena
    pass


def limpiar_datos_obsoletos(tabla="mediciones", columna_fecha="fecha_hora", meses=12):
    """Elimina registros de una tabla con una fecha anterior a un número determinado de meses.

    Args:
        tabla (str, optional): Nombre de la tabla. Defaults to "mediciones".
        columna_fecha (str, optional): Nombre de la columna con la fecha. Defaults to "fecha_hora".
        meses (int, optional): Número de meses para considerar como obsoleto. Defaults to 12.
    """

    try:
        fecha_limite = datetime.now() - timedelta(days=meses * 30)
        params = {"fecha_desde": fecha_limite.isoformat()}
        datos_obsoletos = make_request("GET", tabla, params=params)

        for dato in datos_obsoletos:
            delete_resource(tabla, dato["id"])

        logging.info(f"Limpieza de datos obsoletos de la tabla '{tabla}' realizada con éxito.")

    except APIError as e:
        logging.error(f"Error al limpiar datos obsoletos: {str(e)}")


# ... (resto de las funciones, utilizando make_request)


# Ejemplo de uso (incluye llamada a la función de limpieza)
try:
    devices = get_all("dispositivos")
    print(devices)

    # Ejecutar la limpieza periódicamente (ajustar según CLEANING_INTERVAL)
    if (datetime.now().weekday() == 0):  # Limpiar solo los domingos
        limpiar_datos_sensores