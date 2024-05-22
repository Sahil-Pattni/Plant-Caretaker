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

// Percentage of water in the soil
int SoilSensor::reading()
{
    int rawValue = analogRead(pin);
    // return map(rawValue, 0, 4095, 100, 0);
    return rawValue;
}

#endif
