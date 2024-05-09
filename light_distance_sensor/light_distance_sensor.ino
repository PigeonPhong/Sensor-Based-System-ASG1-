/*********
  Name:Phiraphong A/L A Watt
  Matric.No:288584
  Light & Distance Sensor
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 12;
const int echoPin = 14;
const int ldrPin = A0; // LDR sensor connected to analog pin A0

// Define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
int distanceCm;
int lightLevel;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(500);
  display.clearDisplay();

  display.setTextSize(1); // Set text size to small
  display.setTextColor(WHITE);
}

void loop() {
  // Read the LDR sensor's analog value
  lightLevel = analogRead(ldrPin);

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distanceCm = duration * SOUND_SPEED / 2;

  // Prints the distance and light level in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  // Clear the display
  display.clearDisplay();

  // Display light level progress bar and value
  int lightBarWidth = map(lightLevel, 0, 1023, 0, SCREEN_WIDTH - 4);
  display.drawRect(2, 8, SCREEN_WIDTH - 4, 6, WHITE); // Outline of progress bar
  display.fillRect(2, 8, lightBarWidth, 6, WHITE); // Progress bar
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.print("Light: ");
  display.print(lightLevel);

  // Draw a progress bar to visually represent the distance
  int distanceBarWidth = map(distanceCm, 0, 200, 0, SCREEN_WIDTH - 4);
  display.drawRect(2, SCREEN_HEIGHT / 2 - 3, SCREEN_WIDTH - 4, 6, WHITE); // Outline of progress bar
  display.fillRect(2, SCREEN_HEIGHT / 2 - 3, distanceBarWidth, 6, WHITE); // Progress bar

  // Display distance value
  display.setCursor(0, SCREEN_HEIGHT / 2 + 8);
  display.print("Distance: ");
  display.print(distanceCm);
  display.println(" cm");

  // Display the content on the OLED screen
  display.display();

  delay(500);
}