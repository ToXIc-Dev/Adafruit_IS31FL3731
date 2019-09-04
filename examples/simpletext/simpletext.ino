#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
//Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();
// If you're using the Scroll pHAT HD
Adafruit_IS31FL3731_ScrPhHD matrix = Adafruit_IS31FL3731_ScrPhHD();

// Type a message in the serial monitor to update the display
// Type br + a number between 0-255 to update the brightness

int Brightness = 1;
String message = "BOB";
String message2;
String a;

void setup() {
  Serial.begin(115200);
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
}

void loop() {

while(Serial.available()) {
a = Serial.readString();// read the incoming data as string
if (a.indexOf("br") >=0 ) {
 a.remove(0,2);
 String b = a;
 Brightness = b.toInt();
 message2 = "";
 Serial.println("Brightness set to: " + b);
} else {
message = a;
Serial.println("Message set to: " + message);
}
}

  if (message2 == message) {
    
  } else {
  message2 = message;
  matrix.setRotation(0);
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(Brightness);
  matrix.clear();
  matrix.setCursor(0,0);
  matrix.print(message2);
  }
}