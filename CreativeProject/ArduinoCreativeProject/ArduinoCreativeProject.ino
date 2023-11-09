#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#define PIN 25
#define NUMPIXELS 16
#define BAUD_RATE 230400
#define ringshow_noglitch() {delay(1);ring.show();delay(1);ring.show();}
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(32);
  ring.clear(); // clear all pixels
  ring.setPixelColor(0,0);
  ringshow_noglitch(); 
  Serial.begin(BAUD_RATE);
}

byte frame_header[4];
byte value;
void loop() {
  if(Serial.available()) {
    Serial.readBytes(frame_header, 4);
    byte i;
    for(i=0;i<4;i++) {
      if(frame_header[i]!=i+61) break;  // verify frame header, should be 61,62,63,64
    }
    if(i==4) {  // valid frame header received
//      Serial.readBytes(value, 1);
      value = Serial.read();
      ring.clear();
      for (int i = 0; i < (int)value; i++) {
        ring.setPixelColor(i, ring.Color(255, 0, 0)); // Set the pixel color to red
      }
      ringshow_noglitch(); 
    }
  }
}
