# GP1287 / GP1294 / 05P-CORE  
## 256×50 Graphic VFD Documentation and ESP32 Examples

![256x50 Graphic VFD Module](vfd.jpeg)

![Interface / Pinout Diagram](pinout.jpeg)

This repository provides consolidated technical documentation for a 256×50 graphic vacuum fluorescent display (VFD) module commonly sold under multiple part numbers and labels, including **GP1287** and **05P-CORE**.

The purpose of this repository is to collect, preserve, and clarify information required to electrically interface and control this display, based on available datasheets and verified behavior.

---

## Scope and motivation

These displays are widely available through surplus channels and online marketplaces, but are typically distributed without pinout documentation or controller references. Existing public projects demonstrate that the display is usable, but often omit low-level electrical details required for independent implementation.

An example of such a project is:

- **Simple ESP8266 NTP Clock on VFD256x50 GP1287**  

  https://www.hackster.io/mircemk/simple-esp8266-ntp-clock-on-vfd-display-vfd256x50-gp1287-e0187a

- **Car gauges with Arduino UNO and VFD Display**

  https://github.com/upiir/arduino_car_vfd_gauges/tree/main  

That project confirms functional operation but does not publish a pinout or archive the associated datasheet. This repository focuses specifically on documenting those missing elements.

---

## Repository objectives

- Document the **pin functions and electrical interface**
- Archive the most complete publicly available **datasheet**
- Provide **working ESP32 Arduino reference code**
- Record known **part numbers and aliases** for identification

---

## Display overview

- Display type: Graphic vacuum fluorescent display (VFD)
- Resolution: 256 × 50 pixels
- Interface: SPI (serial)
- Controller family: GP12xx
- Supply voltage: 5 V nominal
- Logic levels: 3.3 V compatible

---

## Known names and identifiers

This display or close variants have been observed under the following identifiers:

- VFD256x50 GP1287
- GP1287 Graphic VFD
- 05P-CORE
- GP1294AI-based VFD
- INBN0BV1294UD
- EPC-INBN0BV1294UD
- 256×50 Graphic VFD Module
- 256×50 SPI VFD Display

Modules sold under these names share a common SPI interface and command structure, with differences primarily in PCB layout and labeling.

---

## Datasheet archive

The repository includes the following archived datasheet:

```

EPC-INBN0BV1294UD_SPEC.pdf

```

This document provides:

- Pin function definitions
- Electrical characteristics
- SPI timing specifications
- Reset and filament control behavior
- Core command set used by GP12xx controllers

Although some modules are labeled **GP1287** or **05P-CORE**, this datasheet accurately describes the observed behavior of the hardware.

---

## Pin functions (from datasheet)

| Pin | Name        | I/O    | Description                                   |
|-----|-------------|--------|-----------------------------------------------|
| 1   | FILAMENT_EN | INPUT  | VFD filament enable, high active              |
| 2   | CLOCK       | INPUT  | SPI clock input                               |
| 3   | CHIPSELECT  | INPUT  | SPI chip select, low active                   |
| 4   | DATA        | INPUT  | SPI data input, LSB first                     |
| 5   | RESET       | INPUT  | VFD reset, low active                         |
| 6   | GND         | —      | Ground                                        |
| 7   | GND         | —      | Ground                                        |
| 8   | +5V OUT     | OUTPUT | +5 V power supply output                     |
| 9   | AINL        | OUTPUT | Audio left channel signal                    |
| 10  | AINR        | OUTPUT | Audio right channel signal                   |
| 11  | LII_SW      | OUTPUT | Light sensor pin, GL5506 pull-down            |
| 12  | GND         | —      | Ground                                        |

---

## ESP32 reference implementations

This repository includes verified ESP32 Arduino examples with the following characteristics:

- Uses the U8g2 library
- Hardware SPI for fast performance
- Explicit handling of filament enable and reset signals
- Operates within the electrical and timing limits specified in the datasheet

### Available Demo Programs

#### 1. Simple Counter Demo (`esp32_vfd_simple_counter/`)
Basic "Hello World" example with incrementing counter - perfect for testing your wiring and getting started.

#### 2. Comprehensive Demo (`esp32_vfd_comprehensive_demo/`)
**Full-featured demonstration** showcasing all display capabilities:
- 7 different test modes (text, graphics, animations, patterns)
- Brightness and contrast testing with various pixel density patterns
- Detailed serial console output for debugging and monitoring
- Automatic mode cycling every 8 seconds
- Extensively documented and easy to understand

**Recommended for:**
- Learning VFD programming
- Testing display capabilities
- Understanding brightness characteristics
- Use as reference code for your own projects

---

## Repository structure

```
.
├── README.md
├── vfd.jpeg
├── pinout.jpeg
├── EPC-INBN0BV1294UD_SPEC.pdf
├── esp32_vfd_simple_counter/
│   └── esp32_vfd_simple_counter.ino
└── esp32_vfd_comprehensive_demo/
    ├── esp32_vfd_comprehensive_demo.ino
    └── README.md
```

---

## Contributions

Contributions are welcome, including:

- Additional datasheets or service documentation
- Confirmed pinout variations
- Code for other microcontrollers
- Measured timing or electrical data

---

## License

Documentation and example code are provided for educational and archival purposes.  
Use at your own risk.
