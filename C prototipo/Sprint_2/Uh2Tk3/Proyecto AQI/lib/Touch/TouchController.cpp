#include "TouchController.h"
#include <Arduino.h>

TouchController::TouchController(int pin0, int pin1, int pin2)
    : touchPin0(pin0), touchPin1(pin1), touchPin2(pin2) {}

void TouchController::begin() {
    pinMode(touchPin0, INPUT);
    pinMode(touchPin1, INPUT);
    pinMode(touchPin2, INPUT);
    // No se necesita inicialización para TOUCH
}

int TouchController::checkTouch() {
    if (touchRead(touchPin0) < 15) return 1; // Next
    //if (touchRead(touchPin1) < 15) return 2; // Previous
    return 0; // No touch detected
}
