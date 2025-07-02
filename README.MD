# PS/2 Keyboard Initialization Sketch

This Arduino sketch initializes and communicates with a PS/2 keyboard using direct pin manipulation. It's designed for low-level integration with breadboard computers (such as Ben Eater's 6502 project) where raw scan codes from a keyboard are needed without a USB interface.

## 🧠 Purpose

Modern microcontrollers rarely have built-in PS/2 support, yet PS/2 keyboards are perfect for low-resource systems — they operate with simple clocked serial data and provide direct key state feedback. This sketch:

- Initializes a PS/2 keyboard
- Reads raw scan codes directly from the keyboard's clock/data lines
- Sends them to the microcontroller for decoding or display
- Can be integrated into a 6502-based computer or used standalone to verify keyboard functionality

## ⚙️ Features

- Bit-level control of PS/2 communication
- Interrupt-driven or polling options possible
- Written for clarity and adaptability in hobby retrocomputing environments
- Intended for breadboard integration — **not** HID/USB translation

## 🪛 Wiring

The PS/2 keyboard has 4 pins (5V, GND, CLK, DATA). You’ll need a PS/2 breakout cable or cut end of a PS/2 cable and wire accordingly:

| PS/2 Pin | Color (typical) | Function  | Connect to Arduino        |
|----------|------------------|-----------|----------------------------|
| 1        | (varies)         | Data      | `PIN_DATA` (e.g. pin 2)    |
| 3        | (varies)         | GND       | GND                        |
| 4        | (varies)         | VCC       | 5V                         |
| 5        | (varies)         | Clock     | `PIN_CLOCK` (e.g. pin 3)   |

> **Note**: Some keyboards require pull-up resistors (e.g. 1k–10k on data and clock lines).

### 🧾 Example Arduino R4 Wiring (Tested Configuration)

```
Clock → D3  
Data  → D2  
GND   → GND  
VCC   → 5V
```

> Be sure your Arduino board supports 5V logic. The PS/2 keyboard is not 3.3V tolerant.

## 💻 Usage

1. Open the sketch in the Arduino IDE.
2. Connect your PS/2 keyboard to the board using the wiring table above.
3. Upload the sketch to your board.
4. Open the Serial Monitor at 9600 baud (or whatever speed is set).
5. Press keys and observe raw scan codes printed to the monitor.

## ✅ Compatibility

This sketch was developed and tested on the **Arduino UNO R4 WiFi**, but it may work with other 5V-compatible boards:

| Board              | Status     | Notes                                    |
|-------------------|------------|------------------------------------------|
| Arduino UNO R4 WiFi | ✅ Tested   | Works with direct port writes             |
| Arduino UNO R3     | ⚠️ Untested | Should work (5V logic) but unverified     |
| Arduino Mega 2560  | ⚠️ Untested | Likely compatible with port adjustments  |
| Arduino Nano       | ⚠️ Untested | 5V logic but pin assignments may differ  |
| ESP32 / RPi Pico   | ❌ Incompatible | Not 5V-tolerant; uses different I/O model |

> Compatibility with 3.3V boards like ESP32 or Pico requires logic level shifting and possibly timing changes — not recommended unless you know what you're doing.

## 🛠️ Customization

- **Pin configuration**: Change `PIN_CLOCK` and `PIN_DATA` to your desired digital pins.
- **Timing adjustments**: Some keyboards are sensitive to initialization timing — you may need to tweak delays.
- **Scan code decoding**: This sketch leaves decoding up to your application (e.g. to handle SHIFT, EXTENDED codes, etc.)

## 📸 Example Output

```
Key A pressed:   0x1C  
Key A released:  0xF0 0x1C

Key B pressed:   0x32  
Key B released:  0xF0 0x32

Key C pressed:   0x21  
Key C released:  0xF0 0x21
```

> PS/2 keyboards send a unique **make code** when a key is pressed, and a **break code** (usually `0xF0` followed by the make code) when it’s released.

## 🔒 License

MIT License — free to use, modify, and distribute. Attribution appreciated.

## 📎 Resources

- [Ben Eater:](https://eater.net/)
- [PS/2 Keyboard Protocol](https://en.wikipedia.org/wiki/PS/2_port)
- [Scan Code Tables](https://wiki.osdev.org/PS/2_Keyboard)
