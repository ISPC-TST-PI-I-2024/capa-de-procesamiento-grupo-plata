from flask import request
from app import app

@app.before_request
def normalize_data():
    if request.method == "POST" and request.json:
        # Normalización de datos, por ejemplo, asegurarse de que todas las unidades están en el mismo formato
        mediciones = request.json.get("mediciones", [])
        for medicion in mediciones:
            if medicion['unidad'] == "C":
                # Convertir a Kelvin como ejemplo
                medicion['valor'] += 273.15
                medicion['unidad'] = "K"
