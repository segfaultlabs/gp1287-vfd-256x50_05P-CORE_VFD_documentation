#include <Arduino.h>
#include <U8g2lib.h>

/*
==============================================================
 GP1287 / 256x50 VFD — ESP32 HARDWARE SPI TEST
==============================================================

 WIRING (VFD → ESP32):
 PIN 6  GND         → GND
 PIN 5  RESET       → GPIO16
 PIN 4  SDA DATA    → GPIO23
 PIN 3  ChipSelect  → GPIO5
 PIN 2  SCK CLOCK   → GPIO18
 PIN 1  FILAMENT_EN → 3.3V or 5V (ALWAYS HIGH)

 NOTES:
 - External USB-C or 5-12V required for VFD
 - Common ground REQUIRED
 - FILAMENT_EN is NOT GPIO
==============================================================
*/

// HW SPI pins are fixed on ESP32:
// MOSI = GPIO23
// SCK  = GPIO18

U8G2_GP1287AI_256X50_2_4W_HW_SPI u8g2(
  U8G2_R0,
  /* cs    = */ 5,
  /* dc    = */ U8X8_PIN_NONE,
  /* reset = */ 16
);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("GP1287 ESP32 TEST START");

  u8g2.begin();
  u8g2.setContrast(255);

  Serial.println("Display init done");

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(10, 20, "ESP32 + GP1287");
    u8g2.drawStr(10, 40, "HELLO WORLD");
  } while (u8g2.nextPage());

  Serial.println("Frame sent");
}

void loop() {
  static int counter = 0;
  counter++;

  Serial.print("Loop tick: ");
  Serial.println(counter);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.setCursor(10, 25);
    u8g2.print("COUNT: ");
    u8g2.print(counter);
  } while (u8g2.nextPage());

  delay(1000);
}
