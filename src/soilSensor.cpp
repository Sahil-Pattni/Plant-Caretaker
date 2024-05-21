#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include <soilSensor.h>
#include <Arduino.h>

SoilSensor::SoilSensor(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

int SoilSensor::determine()
{
    return analogRead(pin) > THRESHOLD ? DRY : WET;
}


int SoilSensor::reading()
{
    return analogRead(pin);
}

#endif
