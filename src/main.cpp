#include <Arduino.h>
#include <soilSensor.h>
#include <buzzer.h>

// Pin management
namespace Pins
{
  const int soilSensor = 36;

  // Needs initialization
  const int activeBuzzer = 4;
  const int redLED = 19;
  const int greenLED = 18;

  void init()
  {
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(activeBuzzer, OUTPUT);
    pinMode(soilSensor, INPUT);
   
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(activeBuzzer, LOW);
  }
};

// Objects
SoilSensor soilSensor(Pins::soilSensor);
ActiveBuzzer activeBuzzer(Pins::activeBuzzer);

int lastState = -1;

void setup() {
  Pins::init();


  Serial.begin(115200);
  while (!Serial); // Wait for Serial to be ready

  // beep 3 times
  activeBuzzer.beep(3, 100);
}

void loop() {
  int reading = soilSensor.reading();
  Serial.println(reading);
  int state = soilSensor.determine();
  
  // Update LED
  if (state == DRY)
  {
    digitalWrite(Pins::redLED, HIGH);
    digitalWrite(Pins::greenLED, LOW);
  }
  else if (state == WET)
  {
    digitalWrite(Pins::redLED, LOW);
    digitalWrite(Pins::greenLED, HIGH);
  }

  if (state != lastState)
  {
    // Serial.println(state);
    // Beep
    activeBuzzer.beep();
    lastState = state;
  }
  delay(1000);
}

