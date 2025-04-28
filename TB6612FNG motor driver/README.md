# Motor Driver and TB6612FNG Module Guide

## 1. Understanding Motor Pins

Each motor has 6 wires:

- **M1**: Motor coil terminal 1 (for driving motor)
- **M2**: Motor coil terminal 2 (for driving motor)
- **GND**: Ground (for encoder electronics)
- **VCC**: Power supply for encoder logic (usually 3.3V or 5V depending on encoder)
- **C1**: Encoder output channel A (for speed/direction)
- **C2**: Encoder output channel B (for quadrature)

### 🔵 Summary:

- **M1/M2** ➔ Connected to motor driver output.
- **C1/C2** ➔ Connected to ESP32 GPIO inputs (with interrupt support).
- **VCC/GND** ➔ Connected to ESP32 3.3V (or 5V if available) and GND.

---

## 2. TB6612FNG Basic Pins

The TB6612FNG module has two channels (A and B) for two motors.

### Important Pins:

- **AIN1, AIN2** → Control direction (Motor A)
- **BIN1, BIN2** → Control direction (Motor B)
- **PWMA, PWMB** → PWM speed control for A and B
- **AO1, AO2** → Motor A outputs
- **BO1, BO2** → Motor B outputs
- **STBY** → Standby (should be pulled HIGH to operate)
- **VCC** → Logic voltage (3.3V)
- **VM** → Motor voltage (connect to your motor supply, e.g., 6V)
- **GND** → Ground

---

## 3. Wiring Diagram

### Step-by-Step Wiring Guide:

| **ESP32 Pin** | **TB6612FNG Pin** | **Motor**   | **Description**               |
|---------------|-------------------|-------------|-------------------------------|
| 3.3V          | VCC               |             | Logic voltage                 |
| GND           | GND               |             | Common ground                 |
| GPIOx         | AIN1              | Motor 1     | Direction control             |
| GPIOy         | AIN2              | Motor 1     | Direction control             |
| GPIOz         | PWMA              | Motor 1     | PWM speed control             |
| GPIOa         | BIN1              | Motor 2     | Direction control             |
| GPIOb         | BIN2              | Motor 2     | Direction control             |
| GPIOc         | PWMB              | Motor 2     | PWM speed control             |
| 3.3V          | STBY              |             | Pull HIGH to enable driver    |
| 6V Motor Battery + | VM           |             | Motor voltage                 |
| Battery GND   | GND               |             | Motor ground                  |

### Motor Connections:

- **Motor 1 M1** ➔ AO1  
- **Motor 1 M2** ➔ AO2  
- **Motor 2 M1** ➔ BO1  
- **Motor 2 M2** ➔ BO2  

### Encoder Connections:

- **Motor 1 C1** ➔ GPIOd (ESP32 input with interrupt)  
- **Motor 1 C2** ➔ GPIOe (ESP32 input with interrupt)  
- **Motor 2 C1** ➔ GPIOf (ESP32 input with interrupt)  
- **Motor 2 C2** ➔ GPIOg (ESP32 input with interrupt)  

### Power Connections:

- **Motor 1 + 2 VCC** ➔ 3.3V (or 5V if required)  
- **Motor 1 + 2 GND** ➔ GND  
