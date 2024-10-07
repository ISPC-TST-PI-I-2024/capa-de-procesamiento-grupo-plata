import pytest
from app import app

@pytest.fixture
def client():
    with app.test_client() as client:
        yield client

def test_data_route(client):
    response = client.post('/data', json={
        "mediciones": [
            {"valor": 25.5, "unidad": "C"},
            {"valor": 65.2, "unidad": "%"}
        ]
    })
    assert response.status_code == 200
