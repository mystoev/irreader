#include <IRremote.h>
#include "ssd1306.h"

IRrecv IR(8);

void textDemo(char message[])
{
    ssd1306_clearScreen();
    
    ssd1306_printFixed(0,  8, "SIGNAL DECODED", STYLE_NORMAL);
    ssd1306_printFixed(0,  24, message, STYLE_NORMAL);
}


void setup() {
  IR.enableIRIn();
  Serial.begin(9600);

  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  ssd1306_printFixed(0,  8, "Waiting for signal...", STYLE_NORMAL);
}

void loop() {
  if (IR.decode()) {
    Serial.println(IR.decodedIRData.decodedRawData, HEX);

    char message[16];
    sprintf(message, "%lX", (uint32_t) IR.decodedIRData.decodedRawData);
    textDemo(message);
    delay (200);
    IR.resume ();
  }
}