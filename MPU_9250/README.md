# MPU9250 and MPU6500 Overview

The MPU9250 and MPU6500 are advanced 9-axis motion tracking sensors, combining a 3-axis accelerometer, a 3-axis gyroscope, and (in the case of the MPU9250) a 3-axis magnetometer for enhanced motion tracking.

## Pinout Description

| Pin Name | Purpose                                                                 | Typical Connection                                                                 |
|----------|-------------------------------------------------------------------------|-----------------------------------------------------------------------------------|
| **VCC**  | Power Supply (Voltage input to the sensor)                              | Connect to 3.3V or 5V                                                             |
| **GND**  | Ground                                                                  | Connect to Ground                                                                 |
| **SCL**  | I2C Clock (controls timing of data transfer)                            | Connect to SCL pin of microcontroller (e.g., GPIO 22 for ESP32)                   |
| **SDA**  | I2C Data (carries the actual data)                                      | Connect to SDA pin of microcontroller (e.g., GPIO 21 for ESP32)                   |
| **XDA**  | Auxiliary Data (used in the auxiliary I2C bus for external devices)     | Not commonly used in basic setups                                                |
| **XCL**  | Auxiliary Clock (used in the auxiliary I2C bus for external devices)    | Not commonly used in basic setups                                                |
| **AD0**  | I2C Address Selection (sets the I2C address of the sensor)              | Pull Low (0x68) or High (0x69) to select I2C address                              |
| **INT**  | Interrupt (signals events like data ready or motion detected)           | Connect to an interrupt-capable GPIO pin on the microcontroller (e.g., GPIO 13)   |
| **NCS**  | Chip Select (used for SPI communication)                                | Not used for I2C, only for SPI communication                                      |
| **FSYNC**| Frame Synchronization (synchronizes external sensors or devices)        | Generally unused in simple setups                                                |

## Detailed Explanation of Each Pin

### VCC (Pin 1)
- **Purpose**: Provides power to the sensor.
- **Typical Voltage**: 3.3V or 5V depending on the sensor and microcontroller. Typically, 3.3V is preferred for ESP32.

### GND (Pin 2)
- **Purpose**: Ground pin for the sensor.
- **Connection**: Connect to the GND of your circuit.

### SCL (Pin 3)
- **Purpose**: Serial Clock Line for I2C communication.
- **Connection**: Connect to the SCL pin of your microcontroller (e.g., GPIO 22 on ESP32).

### SDA (Pin 4)
- **Purpose**: Serial Data Line for I2C communication.
- **Connection**: Connect to the SDA pin of your microcontroller (e.g., GPIO 21 on ESP32).

### XDA (Pin 5)
- **Purpose**: Auxiliary Data Line for the auxiliary I2C bus.
- **Connection**: Typically unused in basic setups.

### XCL (Pin 6)
- **Purpose**: Auxiliary Clock Line for the auxiliary I2C bus.
- **Connection**: Typically unused in basic setups.

### AD0 (Pin 7)
- **Purpose**: Selects the I2C address of the sensor.
    - Low (0V): I2C address is 0x68.
    - High (3.3V): I2C address is 0x69.
- **Connection**: Connect to ground (low) for default I2C address (0x68).

### INT (Pin 8)
- **Purpose**: Interrupt output pin for signaling events like:
    - Data ready to be read.
    - Motion detected.
- **Connection**: Connect to an interrupt-capable GPIO pin (e.g., GPIO 13 on ESP32).

### NCS (Pin 9)
- **Purpose**: Chip Select pin for SPI communication.
- **Connection**: Not used in I2C mode.

### FSYNC (Pin 10)
- **Purpose**: Synchronizes external devices or sensors.
- **Connection**: Typically unused in basic setups.

## Basic Pin Connections for I2C

| MPU9250/6500 Pin | ESP32 Pin         |
|-------------------|-------------------|
| **VCC**          | 3.3V             |
| **GND**          | GND              |
| **SCL**          | GPIO 22          |
| **SDA**          | GPIO 21          |
| **AD0**          | GND (I2C address 0x68) |
| **INT**          | GPIO 13          |
| **NCS**          | Not used (I2C mode) |
| **FSYNC**        | Not used         |

## Key Considerations
- **Magnetometer Access**: The MPU9250 includes a magnetometer, requiring both I2C buses for access. The accelerometer and gyroscope share the same I2C interface as the MPU6050.
- **AD0 Pin**: Use the AD0 pin to change the I2C address (0x68 or 0x69) for multiple sensors on the same bus.
- **Interrupts**: The INT pin enables event-driven communication, useful for efficient data handling.

## Summary
The MPU9250 and MPU6500 offer flexible communication options (I2C and SPI) and advanced features for motion tracking. With proper pin connections and configurations, they can be used in both basic and complex setups.

# How to Connect the MPU9250 to ESP32

To connect your MPU9250 sensor to the ESP32 and read sensor data (accelerometer, gyroscope, and magnetometer), you'll use I2C communication. Follow these steps for wiring and coding to display sensor readings on the serial monitor.

## Step 1: Wiring the MPU9250 to ESP32

Connect the MPU9250 to the ESP32 using the I2C protocol as shown below:

| **MPU9250 Pin** | **ESP32 Pin** | **Description**                                   |
|------------------|---------------|---------------------------------------------------|
| **VCC**          | 3.3V          | Power supply for the sensor.                     |
| **GND**          | GND           | Ground for the sensor.                           |
| **SCL**          | GPIO 22       | I2C Clock (SCL). Connect to ESP32's GPIO 22.     |
| **SDA**          | GPIO 21       | I2C Data (SDA). Connect to ESP32's GPIO 21.      |
| **AD0**          | GND (Optional)| I2C Address Selection Pin (0x68 if grounded, 0x69 if high). |
| **INT**          | GPIO 13 (Optional) | Interrupt pin for event-driven actions (optional). |

> **Note**: Ensure the VCC pin is connected to 3.3V on the ESP32, as the sensor operates at 3.3V logic.

## Step 2: Install the MPU9250 Library

### Steps to Add a Library Manually

1. **Find and Download the Library**  
    - Visit the library's GitHub page (e.g., [hideakitai/MPU9250](https://github.com/hideakitai/MPU9250)).
    - Click the green **Code** button.
    - Select **Download ZIP**.

2. **Extract the ZIP File**  
    - Unzip the downloaded file.
    - You should see a folder containing `.h`, `.cpp`, and other source files.

3. **Move the Library into the Project**  
    - Open your PlatformIO project folder.
    - Locate the `lib/` directory.
    - Move the extracted folder into the `lib/` directory.

> **Note**: Ensure the library folder name matches the library's main header file for proper inclusion in your project.


