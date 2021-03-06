// Load libraries
#include "BluetoothSerial.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// This is probably not done the best way it can but im not great at this, it does work though

// Type txt + message in a bluetooth serial monitor app to update the display
// Type br + a number between 0-255 to update the brightness

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Adafruit_IS31FL3731_ScrPhHD matrix = Adafruit_IS31FL3731_ScrPhHD();

// Bluetooth Serial object
BluetoothSerial SerialBT;

// Handle received and sent messages
int Brightness = 1;
String txt = "BOB";
String message = "";
String message2;
String message3;
String message4;
String SerialD;
bool Swirl = false;
bool loopt = false;
// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};

void setup() {
  Serial.begin(115200);
    if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  // Bluetooth device name
  SerialBT.begin("ESP32 - Badge");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // Read received messages
  unsigned long currentMillis = millis();
  if (SerialBT.available()){
    SerialD = SerialBT.readString();
    Serial.println(SerialD);
      message = SerialD;
      message3 = SerialD;
  }

    if(Swirl) {
    for (uint8_t incr = 0; incr < 24; incr++)
      for (uint8_t x = 0; x < 17; x++)
        for (uint8_t y = 0; y < 9; y++)
          matrix.drawPixel(x, y, sweep[(x+y+incr)%20]);
    //delay(20);
    }

  // Check received message and control output accordingly
if (message3.length() > 1){
message3.remove(0,4);
  
if (message.indexOf("br") >=0 ) {
 message4 = message;
 message4.remove(0,2);
 String b = message4;
 Brightness = b.toInt();
 message2 = "";
 Serial.println("Brightness set to: " + b);
 SerialBT.println("Brightness set to: " + b);
 
  }  else if (message.indexOf("txt") >=0 ){
    Swirl = false;
    message4 = message;
    message4.remove(0,4);
    message4.trim();
    txt = message4;
    Serial.println("Display message set to: " + txt);
    SerialBT.println("Display message set to: " + txt);
  }

    else if (message.indexOf("swirl") >=0 ){
    loopt = false;
    Swirl = true;
    Serial.println("Display message set to Swirl");
    SerialBT.println("Display message set to Swirl");
  }

}

  if (message2 == txt) {
    
  } else {
  message2 = txt;
  matrix.setRotation(0);
  matrix.setTextSize(0);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(Brightness);
  matrix.clear();
  matrix.setCursor(0,0);
  if (message2.length() >= 4) {
    loopt = true;
  } else {
     loopt = false;
     matrix.print(message2);
  }
  }

if (loopt == true) {
      int leng = message2.length() * 7;
      for (int8_t x=18; x>=-leng; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print(message2);
      delay(150);
  }
}

}
