/********************************************************************
 GP1287 / GP1294 / 05P-CORE VFD — ESP32 **IS IT ALIVE** TEST
 PURPOSE:
 - Light the display and draw ONE solid vertical bar, 
 - However this does not work, it just displays static accross the entire screen!!! 
 - Confirms power, filament, HV, SPI wiring, SPI mode, and init.
 - This is the MINIMUM known-good bring-up.

 POWER:
 - Display powered from external **12V** (per datasheet / your setup)
 - ESP32 powered separately (USB)
 - **COMMON GROUND REQUIRED**

 ==============================================================
 DISPLAY BOARD PIN FUNCTIONS  (FROM DATASHEET)
 --------------------------------------------------------------
 PIN 1  - FILAMENT_EN (INPUT)        -> enable heater/HV
 PIN 2  - CLOCK (SPI SCK)
 PIN 3  - CHIP SELECT (ACTIVE LOW)
 PIN 4  - DATA (SPI MOSI, LSB FIRST)
 PIN 5  - RESET (ACTIVE LOW)
 PIN 6  - GND
 PIN 7  - GND
 PIN 8  - +5V OUT (FROM DISPLAY)
 PIN 12 - GND

 ==============================================================
 ESP32 WIRING — **USE THIS EXACTLY**
 --------------------------------------------------------------
 ESP32 GPIO17 -> DISPLAY PIN 1  (FILAMENT_EN)
 ESP32 GPIO14 -> DISPLAY PIN 2  (CLOCK / SCK)
 ESP32 GPIO5  -> DISPLAY PIN 3  (CS, active LOW)
 ESP32 GPIO13 -> DISPLAY PIN 4  (DATA / MOSI)
 ESP32 GPIO16 -> DISPLAY PIN 5  (RESET, active LOW)
 ESP32 GND    -> DISPLAY PIN 6 / 7 / 12 (GND)

 NOTE:
 - SPI MUST BE: MODE0 + LSBFIRST
 - SOFTWARE RESET (0xAA) IS MANDATORY
 ============================================================== */

#include <SPI.h>

/* ===== ESP32 PIN DEFINITIONS (CANONICAL) ===== */
#define VFD_CS    5
#define VFD_RESET 16
#define VFD_EN    17
#define VFD_CLK   14
#define VFD_DATA  13

SPIClass *vspi;

/* ===== LOW-LEVEL HELPERS ===== */
inline void csLow()  { digitalWrite(VFD_CS, LOW); }
inline void csHigh() { digitalWrite(VFD_CS, HIGH); }
inline void tx(uint8_t b){ vspi->transfer(b); }

void sendCmd(uint8_t c){
  csLow(); tx(c); csHigh();
}

void sendCmd2(uint8_t c, uint8_t a){
  csLow(); tx(c); tx(a); csHigh();
}

void hwReset(){
  digitalWrite(VFD_RESET, LOW);
  delay(20);
  digitalWrite(VFD_RESET, HIGH);
  delay(20);
}

void setup(){
  Serial.begin(115200);
  delay(300);

  /* GPIO setup */
  pinMode(VFD_CS, OUTPUT);
  pinMode(VFD_RESET, OUTPUT);
  pinMode(VFD_EN, OUTPUT);

  digitalWrite(VFD_CS, HIGH);
  digitalWrite(VFD_EN, HIGH);     // ENABLE FILAMENT / HV

  /* SPI setup — MUST MATCH */
  vspi = new SPIClass(VSPI);
  vspi->begin(VFD_CLK, -1, VFD_DATA, VFD_CS);
  vspi->beginTransaction(SPISettings(2000000, LSBFIRST, SPI_MODE0));

  /* REQUIRED INIT SEQUENCE */
  hwReset();
  sendCmd(0xAA);                  // SOFTWARE RESET (REQUIRED)
  delay(10);
  sendCmd2(0x80, 0x00);            // NORMAL MODE

  /* BRIGHTNESS (SAFE MID) */
  csLow();
  tx(0xA0);                        // DIMMCTR
  tx(120);                         // low byte
  tx(0x00);                        // high bits
  csHigh();

  sendCmd(0x6D);                   // DISPLAY ON

  /* WRITE ONE SOLID COLUMN (X=0) */
  csLow();
  tx(0xF0);                        // RAM WRITE (COLUMN MODE)
  tx(0x00);                        // X start
  tx(0x00);                        // Y start
  tx(47);                          // HEIGHT-1 (48px)
  for (int i = 0; i < 6; i++) tx(0xFF); // FULL COLUMN ON
  csHigh();

  Serial.println("TEST DONE: You should see a bright vertical bar on the LEFT.");
}

void loop(){
  // nothing — static test
}
