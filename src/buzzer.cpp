#include <buzzer.h>
#include <Arduino.h>

ActiveBuzzer::ActiveBuzzer(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void ActiveBuzzer::beep(int duration)
{
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
}

void ActiveBuzzer::beep(int n, int duration)
{
    for (int i = 0; i < n; i++)
    {
        beep(duration);
        delay(50);
    }
}

void ActiveBuzzer::beep() { beep(100); }