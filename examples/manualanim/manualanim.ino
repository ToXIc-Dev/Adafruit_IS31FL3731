#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
//Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();
// If you're using the Scroll pHAT HD
Adafruit_IS31FL3731_ScrPhHD matrix = Adafruit_IS31FL3731_ScrPhHD();

void setup() {

  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  
  matrix.setTextWrap(false);
  matrix.setTextColor(64); // quarter brightness
  matrix.setTextSize(1);

  // fill all 8 frames with some text
  for (uint8_t frame = 0; frame < 8; frame++) {
    matrix.clear();
    matrix.setFrame(frame);
    matrix.setCursor(0,0);
    matrix.write('a'+frame*3);
    matrix.write('b'+frame*3);
    matrix.write('c'+frame*3);
  }
}

int x = 0;

void loop() {
  // display each frame for 250 milliseconds
  for (uint8_t frame = 0; frame < 8; frame++) {
    matrix.displayFrame(frame);
    delay(250);
  }
}