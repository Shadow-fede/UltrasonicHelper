# UltrasonicHelper

A lightweight and optimized Arduino library for the HC-SR04 and HC-SR05 ultrasonic sensors.

This library provides an efficient way to measure distance using ultrasonic sensors by implementing a **statistical anti-flicker filter** to eliminate erroneous measurement spikes. It calculates the moving average of the samples while automatically discarding the maximum and minimum values detected in each reading cycle to ensure high precision and stability.

## Features

- **Anti-Flicker Filter:** Automatically removes extreme values (outliers) to ensure superior accuracy.
- **Configurable Moving Average:** Easily adjust the number of sample readings to balance responsiveness and stability.
- **Clean & Modular Code:** Full hardware abstraction layer implemented via an elegant C++ class.
- **High Reliability:** Optimized trigger timing management prevents blocking and ensures consistent sensor performance.

## Installation

1. Download this repository as a `.zip` file.
2. Open your Arduino IDE.
3. Navigate to **Sketch** -> **Include Library** -> **Add .ZIP Library...**.
4. Select the downloaded `.zip` file.
