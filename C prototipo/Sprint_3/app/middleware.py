from flask import request, jsonify
from app import app

@app.before_request
def normalize_data():
    if request.method == "POST" and request.json:
        mediciones = request.json.get("mediciones", [])
        for medicion in mediciones:
            if medicion['unidad'] == "C":
                medicion['valor'] += 273.15
                medicion['unidad'] = "K"
