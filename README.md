# STM32F401 7-Segment Display Project

This project implements a **bare-metal 7-segment display driver** for the STM32F401 microcontroller. It includes functionality to:

- Initialize GPIO pins for 7-segment segments and digit control
- Display numbers from 0 to 99
- Highlight prime numbers using the display

---

## **Files**

- `STM32F401_7SEG.c` - Main source file with 7-segment driver and prime number display
- `STM32F401_7SEG.h` - Header file for the driver APIs
- `STM32F401_GPIO.h` / `.c` - GPIO driver for STM32F401

---

## **Hardware Connections**

- **Segments (A-G, DP)** → `GPIOB pins 0-7`
- **Digit Select Pins** → `GPIOA pins 0 (Tens), 1 (Units)`

> This project uses multiplexing to display two digits.

---

## **How to Build and Flash**

1. Use **STM32CubeIDE** or **Keil uVision**.
2. Add all `.c` and `.h` files to your project.
3. Build and flash to the STM32F401 board.
4. The board will display prime numbers from 0–99 on the 7-segment display.

---

## **License**

MIT License
