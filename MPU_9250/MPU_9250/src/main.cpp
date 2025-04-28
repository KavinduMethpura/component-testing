//code from https://github.com/hideakitai/MPU9250

// #include "MPU9250.h"
// #include <Arduino.h>
// MPU9250 mpu; // You can also use MPU9255 as is

// void setup() {
//     Serial.begin(115200);
//     Wire.begin();
//     delay(2000);

//     mpu.setup(0x68);  // change to your own address
// }

// void loop() {
//     if (mpu.update()) {
//         Serial.print(mpu.getYaw()); Serial.print(", ");
//         Serial.print(mpu.getPitch()); Serial.print(", ");
//         Serial.println(mpu.getRoll());
//     }
// }

//second example

// #include <Wire.h>
// #include <MPU9250.h> // have to use 
// #include <Arduino.h>

// MPU9250 mpu;

// void setup() {
//     Serial.begin(115200);
//     Wire.begin(); // SDA = 21, SCL = 22 (default for ESP32)
//     delay(2000);  // Give sensor some time to start up

//     if (!mpu.setup(0x68)) {  // 0x68 is the default address
//         Serial.println("MPU9250 connection failed. Please check your wiring or I2C address!");
//         while (1); // Stop if not found
//     }

//     Serial.println("MPU9250 is ready!");
// }

// void loop() {
//     if (mpu.update()) {
//         // Accelerometer values (g)
//         Serial.print("Accel (g): ");
//         Serial.print(mpu.getAccX(), 3); Serial.print(", ");
//         Serial.print(mpu.getAccY(), 3); Serial.print(", ");
//         Serial.print(mpu.getAccZ(), 3);
//         Serial.print(" | ");

//         // Gyroscope values (deg/sec)
//         Serial.print("Gyro (deg/s): ");
//         Serial.print(mpu.getGyroX(), 3); Serial.print(", ");
//         Serial.print(mpu.getGyroY(), 3); Serial.print(", ");
//         Serial.print(mpu.getGyroZ(), 3);
//         Serial.print(" | ");

//         // Magnetometer values (uT)
//         Serial.print("Mag (uT): ");
//         Serial.print(mpu.getMagX(), 3); Serial.print(", ");
//         Serial.print(mpu.getMagY(), 3); Serial.print(", ");
//         Serial.print(mpu.getMagZ(), 3);
//         Serial.print(" | ");

//         // Orientation (Yaw, Pitch, Roll)
//         Serial.print("YPR (deg): ");
//         Serial.print(mpu.getYaw(), 2); Serial.print(", ");
//         Serial.print(mpu.getPitch(), 2); Serial.print(", ");
//         Serial.println(mpu.getRoll(), 2);
//     }
// }

//i tried to connect Adafruit MPU9250 library + Adafruit Sensor Fusion library but its not working.

//third one
#include <Wire.h>
#include <Adafruit_MPU9250.h>

Adafruit_MPU9250 mpu;  // Create sensor object

void setup() {
    Serial.begin(115200);
    Wire.begin(); // SDA = 21, SCL = 22 for ESP32
    delay(2000);  // Let MPU9250 power up

    if (!mpu.begin()) {
        Serial.println("MPU9250 connection failed. Check wiring or address!");
        while (1); // Stop here if sensor not found
    }

    Serial.println("MPU9250 is ready!");
}

void loop() {
    sensors_event_t accel_event, gyro_event, mag_event, temp_event;

    // Get fresh sensor events
    mpu.getEvent(&accel_event, &gyro_event, &mag_event, &temp_event);

    // Accelerometer (m/s^2)
    Serial.print("Accel (m/s^2): ");
    Serial.print(accel_event.acceleration.x, 3); Serial.print(", ");
    Serial.print(accel_event.acceleration.y, 3); Serial.print(", ");
    Serial.print(accel_event.acceleration.z, 3);
    Serial.print(" | ");

    // Gyroscope (rad/s)
    Serial.print("Gyro (rad/s): ");
    Serial.print(gyro_event.gyro.x, 3); Serial.print(", ");
    Serial.print(gyro_event.gyro.y, 3); Serial.print(", ");
    Serial.print(gyro_event.gyro.z, 3);
    Serial.print(" | ");

    // Magnetometer (uT)
    Serial.print("Mag (uT): ");
    Serial.print(mag_event.magnetic.x, 3); Serial.print(", ");
    Serial.print(mag_event.magnetic.y, 3); Serial.print(", ");
    Serial.print(mag_event.magnetic.z, 3);
    Serial.print(" | ");

    // Orientation placeholder (simple, based on accelerometer)
    // More accurate Yaw/Pitch/Roll would need sensor fusion
    float pitch = atan2(accel_event.acceleration.y, accel_event.acceleration.z) * 180.0 / PI;
    float roll  = atan2(-accel_event.acceleration.x, sqrt(accel_event.acceleration.y * accel_event.acceleration.y + accel_event.acceleration.z * accel_event.acceleration.z)) * 180.0 / PI;
    
    Serial.print("YPR (deg): ");
    Serial.print(0.0); Serial.print(", "); // Yaw requires magnetometer+fusion (not calculated here)
    Serial.print(pitch, 2); Serial.print(", ");
    Serial.println(roll, 2);

    delay(100);
}
