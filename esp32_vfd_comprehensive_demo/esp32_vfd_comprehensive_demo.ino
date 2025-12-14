#include <Arduino.h>
#include <U8g2lib.h>

/*
==============================================================
 GP1287 / 256x50 VFD — ESP32 COMPREHENSIVE DEMO
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
 - FILAMENT_EN is NOT GPIO - connect directly to power

 DEMO MODES:
 This demo cycles through various display tests to showcase
 the VFD's capabilities and test brightness/contrast:

 1. Text Display Demo - Various fonts and text positioning
 2. Graphics Demo - Lines, boxes, circles, and shapes
 3. Brightness Pattern Test - Different patterns for contrast
 4. Animation Demo - Moving elements and scrolling
 5. Pixel Pattern Test - Checkerboard and gradient patterns
 6. Counter Demo - Simple incrementing counter
 7. Full Screen Tests - All on/all off brightness test

 Each mode runs for a set duration, then automatically advances.
 Serial console provides detailed feedback for each mode.
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

// Demo configuration
const int MODE_DURATION = 8000;  // Time per demo mode in milliseconds
const int ANIMATION_SPEED = 50;  // Animation frame delay in ms

// Demo state variables
int currentMode = 0;
const int NUM_MODES = 7;
unsigned long modeStartTime = 0;
int frameCounter = 0;
int globalCounter = 0;

// Mode names for serial output
const char* modeNames[] = {
  "TEXT DISPLAY",
  "GRAPHICS DEMO",
  "BRIGHTNESS PATTERNS",
  "ANIMATION DEMO",
  "PIXEL PATTERNS",
  "COUNTER DEMO",
  "FULL SCREEN TEST"
};

/*
==============================================================
 SETUP - Initialize display and serial communication
==============================================================
*/
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n==================================================");
  Serial.println("  GP1287 VFD COMPREHENSIVE DEMO");
  Serial.println("  256x50 Graphic VFD Display Test");
  Serial.println("==================================================\n");

  Serial.println("Initializing display...");
  u8g2.begin();

  // Start with maximum contrast for best visibility
  u8g2.setContrast(255);
  Serial.println("Display contrast set to: 255 (maximum)");

  Serial.println("Display initialized successfully!");
  Serial.println("\nDemo will cycle through 7 different modes");
  Serial.println("Each mode runs for 8 seconds");
  Serial.println("--------------------------------------------------\n");

  modeStartTime = millis();
  printModeHeader(0);
}

/*
==============================================================
 MAIN LOOP - Cycle through demo modes
==============================================================
*/
void loop() {
  // Check if it's time to switch modes
  if (millis() - modeStartTime >= MODE_DURATION) {
    currentMode = (currentMode + 1) % NUM_MODES;
    modeStartTime = millis();
    frameCounter = 0;
    Serial.println("\n--------------------------------------------------");
    printModeHeader(currentMode);
  }

  // Execute current demo mode
  switch(currentMode) {
    case 0:
      demoTextDisplay();
      break;
    case 1:
      demoGraphics();
      break;
    case 2:
      demoBrightnessPatterns();
      break;
    case 3:
      demoAnimation();
      break;
    case 4:
      demoPixelPatterns();
      break;
    case 5:
      demoCounter();
      break;
    case 6:
      demoFullScreen();
      break;
  }

  frameCounter++;
  globalCounter++;
  delay(ANIMATION_SPEED);
}

/*
==============================================================
 UTILITY FUNCTIONS
==============================================================
*/

// Print mode header to serial console
void printModeHeader(int mode) {
  Serial.print("MODE ");
  Serial.print(mode + 1);
  Serial.print("/");
  Serial.print(NUM_MODES);
  Serial.print(": ");
  Serial.println(modeNames[mode]);
  Serial.print("Description: ");

  switch(mode) {
    case 0:
      Serial.println("Testing various fonts and text positioning");
      break;
    case 1:
      Serial.println("Drawing lines, boxes, circles, and shapes");
      break;
    case 2:
      Serial.println("Testing display brightness with different patterns");
      break;
    case 3:
      Serial.println("Animated elements and scrolling text");
      break;
    case 4:
      Serial.println("Checkerboard and gradient patterns for contrast");
      break;
    case 5:
      Serial.println("Simple incrementing counter display");
      break;
    case 6:
      Serial.println("All pixels on/off for maximum brightness test");
      break;
  }
  Serial.println();
}

/*
==============================================================
 DEMO MODE 1: TEXT DISPLAY
 Shows different fonts and text positioning capabilities
==============================================================
*/
void demoTextDisplay() {
  if (frameCounter % 20 == 0) {
    Serial.print("Text Demo - Frame: ");
    Serial.print(frameCounter);
    Serial.println(" - Displaying multiple fonts and text sizes");
  }

  u8g2.firstPage();
  do {
    // Title with default font
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(2, 10, "GP1287 VFD - Text Demo");

    // Different font samples
    u8g2.setFont(u8g2_font_5x7_tf);
    u8g2.drawStr(2, 22, "5x7 Font: ABCDEFG 0123456789");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(2, 34, "6x10 Font: Test Pattern");

    u8g2.setFont(u8g2_font_7x13_tf);
    u8g2.drawStr(2, 48, "7x13 Font: Display Test");

  } while (u8g2.nextPage());
}

/*
==============================================================
 DEMO MODE 2: GRAPHICS DEMO
 Demonstrates drawing capabilities: lines, boxes, circles
==============================================================
*/
void demoGraphics() {
  if (frameCounter % 20 == 0) {
    Serial.print("Graphics Demo - Frame: ");
    Serial.print(frameCounter);
    Serial.println(" - Drawing shapes and patterns");
  }

  u8g2.firstPage();
  do {
    // Title
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(2, 10, "Graphics Test");

    // Draw various shapes
    // Rectangles
    u8g2.drawFrame(5, 15, 30, 20);      // Hollow rectangle
    u8g2.drawBox(40, 15, 30, 20);       // Filled rectangle

    // Circles
    u8g2.drawCircle(90, 25, 10);         // Hollow circle
    u8g2.drawDisc(120, 25, 10);          // Filled circle

    // Lines
    u8g2.drawLine(150, 15, 180, 35);     // Diagonal line
    u8g2.drawLine(150, 35, 180, 15);     // Cross

    // Pattern of horizontal lines
    for (int i = 0; i < 5; i++) {
      u8g2.drawLine(190, 15 + i*4, 250, 15 + i*4);
    }

    // Border around entire display
    u8g2.drawFrame(0, 0, 256, 50);

  } while (u8g2.nextPage());
}

/*
==============================================================
 DEMO MODE 3: BRIGHTNESS PATTERN TEST
 Tests different pixel patterns to observe brightness/contrast
 Useful for understanding VFD brightness characteristics
==============================================================
*/
void demoBrightnessPatterns() {
  static int patternIndex = 0;

  // Change pattern every 2 seconds
  if (frameCounter % 40 == 0) {
    patternIndex = (frameCounter / 40) % 4;
    Serial.print("Brightness Test - Pattern: ");
    Serial.print(patternIndex + 1);
    Serial.print("/4 - ");

    switch(patternIndex) {
      case 0:
        Serial.println("Horizontal stripes (50% density)");
        break;
      case 1:
        Serial.println("Vertical stripes (50% density)");
        break;
      case 2:
        Serial.println("Diagonal lines (25% density)");
        break;
      case 3:
        Serial.println("Sparse dots (10% density)");
        break;
    }
  }

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tf);

    switch(patternIndex) {
      case 0:
        // Horizontal stripes - every other line
        u8g2.drawStr(2, 8, "Horizontal Stripes");
        for (int y = 12; y < 50; y += 2) {
          u8g2.drawLine(0, y, 255, y);
        }
        break;

      case 1:
        // Vertical stripes - every other column
        u8g2.drawStr(2, 8, "Vertical Stripes");
        for (int x = 0; x < 256; x += 2) {
          u8g2.drawLine(x, 12, x, 49);
        }
        break;

      case 2:
        // Diagonal lines
        u8g2.drawStr(2, 8, "Diagonal Pattern");
        for (int i = 0; i < 300; i += 8) {
          u8g2.drawLine(i, 12, i - 50, 49);
        }
        break;

      case 3:
        // Sparse dot pattern
        u8g2.drawStr(2, 8, "Sparse Dots");
        for (int x = 0; x < 256; x += 8) {
          for (int y = 12; y < 50; y += 8) {
            u8g2.drawPixel(x, y);
          }
        }
        break;
    }

  } while (u8g2.nextPage());
}

/*
==============================================================
 DEMO MODE 4: ANIMATION DEMO
 Shows animated elements: scrolling text and moving objects
==============================================================
*/
void demoAnimation() {
  if (frameCounter % 20 == 0) {
    Serial.print("Animation Demo - Frame: ");
    Serial.print(frameCounter);
    Serial.println(" - Scrolling text and moving elements");
  }

  // Scrolling position
  int scrollPos = (frameCounter * 2) % 280;

  // Bouncing ball position
  int ballY = 25 + sin(frameCounter * 0.1) * 15;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x10_tf);

    // Scrolling text
    u8g2.drawStr(256 - scrollPos, 10, "*** SCROLLING TEXT DEMO ***");

    // Moving ball
    u8g2.drawDisc(50, ballY, 5);

    // Moving rectangle
    int rectX = (frameCounter * 3) % 256;
    u8g2.drawFrame(rectX, 30, 20, 15);

    // Static info
    u8g2.setFont(u8g2_font_5x7_tf);
    u8g2.drawStr(2, 48, "Animation Test");

  } while (u8g2.nextPage());
}

/*
==============================================================
 DEMO MODE 5: PIXEL PATTERNS
 Checkerboard and other patterns for contrast testing
==============================================================
*/
void demoPixelPatterns() {
  static int patternType = 0;

  if (frameCounter % 40 == 0) {
    patternType = (frameCounter / 40) % 2;
    Serial.print("Pixel Pattern - Type: ");
    Serial.println(patternType == 0 ? "Checkerboard (50%)" : "Fine Grid (25%)");
  }

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tf);

    if (patternType == 0) {
      // Checkerboard pattern
      u8g2.drawStr(2, 8, "Checkerboard Pattern");
      for (int x = 0; x < 256; x += 4) {
        for (int y = 12; y < 50; y += 4) {
          if ((x/4 + y/4) % 2 == 0) {
            u8g2.drawBox(x, y, 4, 4);
          }
        }
      }
    } else {
      // Fine grid
      u8g2.drawStr(2, 8, "Fine Grid Pattern");
      for (int x = 0; x < 256; x += 4) {
        u8g2.drawLine(x, 12, x, 49);
      }
      for (int y = 12; y < 50; y += 4) {
        u8g2.drawLine(0, y, 255, y);
      }
    }

  } while (u8g2.nextPage());
}

/*
==============================================================
 DEMO MODE 6: COUNTER DEMO
 Simple incrementing counter (original demo functionality)
==============================================================
*/
void demoCounter() {
  if (frameCounter % 20 == 0) {
    Serial.print("Counter Demo - Value: ");
    Serial.print(globalCounter);
    Serial.println(" - Classic counting display");
  }

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(10, 15, "Simple Counter:");

    u8g2.setFont(u8g2_font_10x20_tf);
    u8g2.setCursor(10, 40);
    u8g2.print("COUNT: ");
    u8g2.print(globalCounter);

  } while (u8g2.nextPage());
}

/*
==============================================================
 DEMO MODE 7: FULL SCREEN TEST
 Alternates between all pixels on and all pixels off
 Tests maximum and minimum brightness
==============================================================
*/
void demoFullScreen() {
  static bool allOn = false;

  if (frameCounter % 40 == 0) {
    allOn = !allOn;
    Serial.print("Full Screen Test - ");
    Serial.println(allOn ? "ALL PIXELS ON (max brightness)" : "ALL PIXELS OFF (min brightness)");

    // Also test different contrast levels
    if (allOn) {
      int contrast = 128 + (frameCounter % 128);  // Vary between 128-255
      u8g2.setContrast(contrast);
      Serial.print("  Contrast level: ");
      Serial.println(contrast);
    } else {
      u8g2.setContrast(255);  // Reset to max
    }
  }

  u8g2.firstPage();
  do {
    if (allOn) {
      // Fill entire screen
      u8g2.drawBox(0, 0, 256, 50);
    } else {
      // Clear screen with just a small message
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.drawStr(2, 10, "Screen Off Test");
      u8g2.drawStr(2, 25, "Minimal pixels active");
    }

  } while (u8g2.nextPage());
}
