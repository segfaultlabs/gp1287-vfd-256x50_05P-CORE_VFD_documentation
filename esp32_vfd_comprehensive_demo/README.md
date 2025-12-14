# GP1287 VFD Comprehensive Demo

This is an extensive demonstration program for the GP1287 / 256x50 VFD display with ESP32. It showcases all major display capabilities and provides detailed serial console feedback.

## Features

This demo automatically cycles through **7 different test modes**, each running for 8 seconds:

### 1. Text Display Demo
- Tests various U8g2 fonts (5x7, 6x10, 7x13)
- Shows text positioning and rendering capabilities
- Demonstrates different font sizes and styles

### 2. Graphics Demo
- Draws geometric shapes: rectangles, circles, lines
- Shows both filled and hollow shapes
- Demonstrates the full graphics drawing API
- Includes display border to show full active area

### 3. Brightness Pattern Test
- **Four different pixel density patterns:**
  - Horizontal stripes (50% pixel density)
  - Vertical stripes (50% pixel density)
  - Diagonal lines (25% pixel density)
  - Sparse dots (10% pixel density)
- Helps understand VFD brightness characteristics
- Useful for evaluating phosphor uniformity and contrast

### 4. Animation Demo
- Scrolling text across the display
- Bouncing ball with sine wave motion
- Moving rectangle animation
- Demonstrates smooth frame updates

### 5. Pixel Patterns
- Checkerboard pattern for contrast testing
- Fine grid pattern for alignment testing
- Tests display uniformity and pixel response

### 6. Counter Demo
- Simple incrementing counter display
- Classic demo functionality
- Shows numeric text rendering

### 7. Full Screen Test
- Alternates between all pixels ON and all pixels OFF
- Tests maximum and minimum brightness levels
- **Dynamically adjusts contrast levels** (128-255)
- Serial output reports current contrast setting
- Useful for power consumption and brightness analysis

## Serial Console Output

The demo provides **detailed real-time feedback** via serial console (115200 baud):

### Startup Information
```
==================================================
  GP1287 VFD COMPREHENSIVE DEMO
  256x50 Graphic VFD Display Test
==================================================

Initializing display...
Display contrast set to: 255 (maximum)
Display initialized successfully!

Demo will cycle through 7 different modes
Each mode runs for 8 seconds
--------------------------------------------------
```

### Mode Information
For each mode, the console displays:
- Mode number and name
- Detailed description of what's being tested
- Frame-by-frame updates
- Pattern changes and variations
- Contrast level adjustments

Example output:
```
MODE 3/7: BRIGHTNESS PATTERNS
Description: Testing display brightness with different patterns

Brightness Test - Pattern: 1/4 - Horizontal stripes (50% density)
Brightness Test - Pattern: 2/4 - Vertical stripes (50% density)
Brightness Test - Pattern: 3/4 - Diagonal lines (25% density)
Brightness Test - Pattern: 4/4 - Sparse dots (10% density)
```

## Hardware Setup

### Wiring (VFD → ESP32)
```
VFD PIN 6  (GND)         → ESP32 GND
VFD PIN 5  (RESET)       → ESP32 GPIO16
VFD PIN 4  (SDA DATA)    → ESP32 GPIO23 (MOSI)
VFD PIN 3  (ChipSelect)  → ESP32 GPIO5
VFD PIN 2  (SCK CLOCK)   → ESP32 GPIO18 (SCK)
VFD PIN 1  (FILAMENT_EN) → 3.3V or 5V (ALWAYS HIGH)
```

### Important Notes
- External 5-12V power supply required for VFD operation
- Common ground between ESP32 and VFD is **REQUIRED**
- FILAMENT_EN should be connected directly to power (not a GPIO pin)
- Uses ESP32 hardware SPI for fast updates

## Software Requirements

### Arduino Libraries
- **U8g2** library (install via Arduino Library Manager)
- Standard Arduino ESP32 board support

### Installation Steps
1. Install Arduino IDE
2. Add ESP32 board support: `https://dl.espressif.com/dl/package_esp32_index.json`
3. Install U8g2 library: Sketch → Include Library → Manage Libraries → Search "U8g2"
4. Open `esp32_vfd_comprehensive_demo.ino`
5. Select your ESP32 board
6. Upload the sketch

## Usage

1. **Upload the sketch** to your ESP32
2. **Open Serial Monitor** at 115200 baud
3. **Watch the demo** cycle through all modes automatically
4. **Observe the serial console** for detailed information about each test

The demo runs continuously, cycling through all 7 modes in sequence. Each mode lasts 8 seconds before automatically advancing to the next.

## Understanding the Tests

### Brightness and Contrast Testing

The demo includes several tests specifically designed to understand VFD brightness:

- **Pattern density tests** show how different pixel densities affect perceived brightness
- **Full screen test** shows maximum power draw and brightness
- **Contrast variation** (mode 7) tests the display at different contrast settings
- Serial output provides exact contrast values being tested

VFD displays have unique characteristics compared to LCD/OLED:
- Brightness is proportional to pixel density
- More lit pixels = higher power consumption
- Contrast settings affect drive voltage
- Phosphor glow may vary across the display

### Practical Applications

Use this demo to:
- Verify your VFD is working correctly
- Test all display features before building your own project
- Learn the U8g2 API for VFD graphics programming
- Understand brightness and power characteristics
- Share a working example with others
- Debug wiring or connection issues

## Customization

The demo is designed to be easy to modify:

- **Change timing**: Adjust `MODE_DURATION` (default: 8000ms)
- **Adjust animation speed**: Modify `ANIMATION_SPEED` (default: 50ms)
- **Add new modes**: Create new demo functions and add to the switch statement
- **Modify patterns**: Edit pattern drawing code in each demo function
- **Change contrast range**: Adjust values in `demoFullScreen()`

## Serial Console Example

Complete startup and operation:
```
==================================================
  GP1287 VFD COMPREHENSIVE DEMO
  256x50 Graphic VFD Display Test
==================================================

Initializing display...
Display contrast set to: 255 (maximum)
Display initialized successfully!

Demo will cycle through 7 different modes
Each mode runs for 8 seconds
--------------------------------------------------

MODE 1/7: TEXT DISPLAY
Description: Testing various fonts and text positioning

Text Demo - Frame: 0 - Displaying multiple fonts and text sizes
Text Demo - Frame: 20 - Displaying multiple fonts and text sizes
...

--------------------------------------------------
MODE 2/7: GRAPHICS DEMO
Description: Drawing lines, boxes, circles, and shapes

Graphics Demo - Frame: 0 - Drawing shapes and patterns
...
```

## Code Structure

The code is organized into clear sections:

1. **Configuration** - Pin definitions and timing constants
2. **Setup()** - Display initialization and serial output
3. **Loop()** - Mode switching and execution
4. **Utility Functions** - Serial console formatting
5. **Demo Functions** - One function per demo mode
6. **Extensive Comments** - Every function is documented

All code is **heavily commented** to make it easy to understand and modify.

## Troubleshooting

### Display not working?
- Check all wiring connections
- Verify external power supply is connected
- Ensure FILAMENT_EN is connected to power
- Check serial console for initialization messages

### Partial display or artifacts?
- Try reducing SPI speed
- Check for loose connections
- Verify power supply has adequate current
- Check contrast settings

### No serial output?
- Verify baud rate is set to 115200
- Check USB cable connection
- Ensure correct COM port is selected

## Contributing

This demo is designed to be a reference for the community. Suggestions for improvements or additional test modes are welcome!

## License

Open source - use freely for educational and project purposes.
