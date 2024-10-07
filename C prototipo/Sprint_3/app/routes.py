from flask import request, jsonify
from flask_jwt_extended import jwt_required
from app import app

@jwt_required()
@app.route('/data', methods=['POST'])
def handle_data():
    datos = request.json.get("mediciones", [])
    return jsonify({"message": "Datos recibidos correctamente", "data": datos}), 200
