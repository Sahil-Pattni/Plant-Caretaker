#include <Arduino.h>

// Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_WIDTH 128 // OLED display width, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Custom headers
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

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.println("Soil Sensor");
  display.display();
  delay(100);

  Serial.begin(115200);
  while (!Serial); // Wait for Serial to be ready

  // beep 3 times
  activeBuzzer.beep(3, 100);
}

void loop() {
  int reading = soilSensor.reading();
  int state = soilSensor.determine();

  // Display
  display.clearDisplay();
  display.setCursor(0, 30);
  String message = "MST: " + String(reading) + "\n" + (state == DRY ? "Dry" : "Wet");
  display.println(message);
  Serial.println(message);
  display.display();
  
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

