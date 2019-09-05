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
char incomingChar;

void setup() {
  Serial.begin(115200);
    if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  // Bluetooth device name
  SerialBT.begin("ESP32");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // Read received messages (LED control command)
  unsigned long currentMillis = millis();
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
      message3 += String(incomingChar);
    }
    else{
      message = "";
    }
    //Serial.write(incomingChar);
   
  }

  // Check received message and control output accordingly
if (message3.length() > 1){
//Serial.println();
//Serial.println("Message 3: " + message3);
message3.remove(0,4);
//Serial.println("Message 3: " + message3);
  
if (message.indexOf("br") >=0 ) {
 message4 = message;
 message4.remove(0,2);
 String b = message4;
 Brightness = b.toInt();
 message2 = "";
 Serial.println("Brightness set to: " + b);
 SerialBT.println("Brightness set to: " + b);
 
  }  else if (message.indexOf("txt") >=0 ){
    message4 = message;
    message4.remove(0,4);
    message4.trim();
    txt = message4;
    Serial.println("Display message set to: " + txt);
    SerialBT.println("Display message set to: " + txt);
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
  matrix.print(message2);
  }
}
