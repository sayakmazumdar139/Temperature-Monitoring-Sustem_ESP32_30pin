# Temperature-Monitoring-Sustem_ESP32_30pin
OBJECTIVE:
The objective of this project is to continuously monitor the ambient temperature and humidity using a DHT11 sensor and display the measured values on a 16×2 LCD display. When the temperature exceeds a predefined threshold value, an LED and buzzer are activated to provide a visual and audible warning. 

WORKING PRINCIPLE:
1. ESP32 DevKit V1 (Microcontroller Unit):

The ESP32 acts as the brain of the system.

Functions:

Reads temperature and humidity data from the DHT11 sensor.
Processes the received data.
Compares the measured temperature with the predefined threshold value.
Controls the LCD display, LED, and buzzer based on the sensor readings.

The ESP32 continuously executes the program stored in its flash memory and performs all decision-making operations.

2. DHT11 Temperature and Humidity Sensor:

The DHT11 is a digital sensor capable of measuring:

Temperature (0°C to 50°C)
Relative Humidity (20% to 90%)

Working:

Inside the DHT11, a thermistor measures temperature.
A humidity sensing element measures moisture content in the air.
The sensor converts these measurements into digital data.
The digital data is transmitted to the ESP32 through a single data pin (GPIO4).

Example:

Temperature = 28°C
Humidity = 65%

The ESP32 receives these values every few seconds.

3. 16×2 LCD Display (I2C):

The LCD is used to display:

Current Temperature
Current Humidity
Threshold Temperature
System Status (SAFE / ALERT)

Working:

The ESP32 sends data to the LCD through the I2C communication protocol.

Pins used:

SDA → GPIO21
SCL → GPIO22

Example LCD Output:

T:28°C H:65%
TH:35°C SAFE

4. LED Indicator:

The LED acts as a visual warning device.

Working:

When:
Temperature < Threshold

LED remains OFF.

When:
Temperature ≥ Threshold

ESP32 outputs HIGH logic to GPIO2.
The LED receives current and glows.

Example:

Threshold = 35°C
Measured = 37°C

LED = ON

5. 220Ω Current Limiting Resistor:

The resistor is connected in series with the LED.

Purpose:
The LED requires limited current for safe operation.

Using Ohm's Law:
I = V / R

Example:
V = 3.3V
R = 220Ω
I = 3.3 / 220
≈ 15mA

Without the resistor:

Excess current may flow.
LED may burn out.
ESP32 GPIO pin may be damaged.

Therefore, the resistor protects both the LED and ESP32.

6. Buzzer:
The buzzer provides an audible alarm.

Working:

When:
Temperature < Threshold

Buzzer remains OFF.

When:
Temperature ≥ Threshold

ESP32 sends HIGH signal to GPIO15.
The buzzer produces sound indicating an over-temperature condition.

Example:
Measured Temperature = 38°C

LED = ON
Buzzer = ON

CONCLUSION:
The Smart Temperature Monitoring System uses an ESP32 DevKit V1 microcontroller, DHT11 temperature and humidity sensor, 16×2 I2C LCD display, LED indicator, 220Ω current-limiting resistor, and buzzer to monitor environmental conditions in real time. The system provides both visual and audible alerts whenever the measured temperature exceeds the predefined threshold, making it suitable for basic industrial, laboratory, and home monitoring applications.
