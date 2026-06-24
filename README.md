# Temperature-Monitoring-Sustem_ESP32_30pin
🔰 OBJECTIVE:
The objective of this project is to continuously monitor the ambient temperature and humidity using a DHT11 sensor and display the measured values on a 16×2 LCD display. When the temperature exceeds a predefined threshold value, an LED and buzzer are activated to provide a visual and audible warning. 

🔰 WORKING PRINCIPLE:
1. ESP32 DevKit V1 (Microcontroller Unit):

The ESP32 acts as the brain of the system.

🔸Functions:

Reads temperature and humidity data from the DHT11 sensor.
Processes the received data.
Compares the measured temperature with the predefined threshold value.
Controls the LCD display, LED, and buzzer based on the sensor readings.

The ESP32 continuously executes the program stored in its flash memory and performs all decision-making operations.

2. DHT11 Temperature and Humidity Sensor:

The DHT11 is a digital sensor capable of measuring:

Temperature (0°C to 50°C)
Relative Humidity (20% to 90%)

🔸Working:

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

🔸Working:

The ESP32 sends data to the LCD through the I2C communication protocol.

Pins used:

SDA → GPIO21
SCL → GPIO22

Example LCD Output:

T:28°C H:65%
TH:35°C SAFE

4. LED Indicator:

The LED acts as a visual warning device.

🔸Working:

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

🔸Purpose:
The LED requires limited current for safe operation.

🔸Using Ohm's Law:
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

🔸Working:

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

🔰 CONCLUSION:
The Smart Temperature Monitoring System uses an ESP32 DevKit V1 microcontroller, DHT11 temperature and humidity sensor, 16×2 I2C LCD display, LED indicator, 220Ω current-limiting resistor, and buzzer to monitor environmental conditions in real time. The system provides both visual and audible alerts whenever the measured temperature exceeds the predefined threshold, making it suitable for basic industrial, laboratory, and home monitoring applications.

🟡 The embedded C code is in under the "sketch_ESP32_TemperatureMonitoringSystem" file. just click on it, and anyone can see this Code. Now the Explanation of this code is:

1. Header Files:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

🔸Purpose:
These libraries provide ready-made functions.

Wire.h:
Used for I2C communication between ESP32 and LCD.

ESP32 ↔ I2C Bus ↔ LCD

LiquidCrystal_I2C.h:
Used to control the 16×2 I2C LCD.

🔸Functions:
lcd.init()
lcd.print()
lcd.clear()

DHT.h:
Used to communicate with the DHT11 sensor.

🔸Functions:
readTemperature()
readHumidity()

2. Pin Definitions:
#define DHTPIN 4
#define DHTTYPE DHT11

#define LED_PIN 2
#define BUZZER_PIN 15

#define TEMP_THRESHOLD 35

🔸Purpose:
These are preprocessor macros.
The compiler replaces them before compilation.

🔸Meaning:
DHTPIN 4
DHT11 DATA pin connected to GPIO4.

LED_PIN 2
LED connected to GPIO2.

BUZZER_PIN 15
Buzzer connected to GPIO15.

TEMP_THRESHOLD 35
Threshold temperature is set to 35°C.

3. Creating Sensor Object:
DHT dht(DHTPIN, DHTTYPE);

🔸Purpose:
Creates a DHT11 object.

🔸Equivalent meaning:
DHT Sensor
Pin = GPIO4
Type = DHT11

This object is later used for:
dht.readTemperature()
dht.readHumidity()

4. Creating LCD Object:
LiquidCrystal_I2C lcd(0x27, 16, 2);

🔸Meaning:
I2C Address = 0x27
Columns = 16
Rows = 2

Most LCD I2C modules use:
0x27

5. Setup Function:
void setup()
Runs only once after ESP32 power-up or reset.

Serial Communication
Serial.begin(115200);
Starts Serial Monitor communication.

Baud Rate:
115200 bits/sec
Used for debugging.

GPIO Configuration:
pinMode(LED_PIN, OUTPUT);
pinMode(BUZZER_PIN, OUTPUT);

Configures:
GPIO2  → Output
GPIO15 → Output
Because LED and buzzer are output devices.

Initial State:
digitalWrite(LED_PIN, LOW);
digitalWrite(BUZZER_PIN, LOW);
Keeps both OFF at startup.

DHT11 Initialization:
dht.begin();
Starts communication with DHT11 sensor.

LCD Initialization:
lcd.init();
lcd.backlight();

lcd.init()
Initializes LCD.

lcd.backlight()
Turns ON LCD backlight.

Welcome Message:
lcd.setCursor(0,0);
lcd.print("Temperature");

lcd.setCursor(0,1);
lcd.print("Monitoring");

LCD displays:
Temperature
Monitoring

Delay
delay(2000);

Waits for:
2000 ms = 2 sec

Clear LCD:
lcd.clear();
Removes startup message.

6. Loop Function:
void loop()
Runs continuously forever.

Reading Sensor Data:
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();

🔸What Happens?

DHT11 sends:
Temperature & Humidity to ESP32.

Example:

Temperature = 30.2°C
Humidity = 65%

Stored in:
temperature
humidity

Sensor Error Check:
if (isnan(humidity) || isnan(temperature))

isnan()
Means:
Is Not A Number
Checks if sensor returned invalid data.

If Error Occurs
Serial.println("DHT11 Error!");

Prints:
DHT11 Error!
lcd.clear();
lcd.print("Sensor Error");

LCD shows:
Sensor Error
return;
Stops current loop iteration.
Then tries again.

Printing Data on Serial Monitor:
Serial.print("Temp: ");
Serial.print(temperature);

Example:
Temp: 31.5 C

Serial.print("Humidity: ");
Serial.print(humidity);

Example:
Humidity: 65 %

Updating LCD:
lcd.clear();
Removes old data.

First Line
lcd.setCursor(0,0);
Moves cursor:
Row 0
Column 0

Print Temperature
lcd.print("T:");
lcd.print(temperature);

Example:
T:30.5

Degree Symbol:
lcd.print((char)223);

Displays:
°

🔸Complete Output:
T:30.5°C

Humidity Display:
lcd.setCursor(10,0);

Moves cursor to:
Column 10
Row 0

Displays:
H:65

Second Line:
lcd.setCursor(0,1);

Moves cursor to:
Column 0
Row 1

🔸Threshold Display:
lcd.print("TH:");
lcd.print(TEMP_THRESHOLD);

Shows:
TH:35°C

🔸Temperature Comparison:
This is the most important logic.

if (temperature >= TEMP_THRESHOLD)

Example:
Measured = 38°C
Threshold = 35°C
Condition becomes TRUE.

🔸Alert Mode:
digitalWrite(LED_PIN, HIGH);
LED ON.

digitalWrite(BUZZER_PIN, HIGH);
Buzzer ON.

lcd.print("ALERT!");

LCD shows:
ALERT!

Complete LCD:
T:38°C H:65
TH:35°C ALERT!

Safe Mode:
If:

Temperature < 35°C
Then:

digitalWrite(LED_PIN, LOW);
digitalWrite(BUZZER_PIN, LOW);

LED OFF.
Buzzer OFF.

LCD shows:
SAFE

Display:
T:29°C H:60
TH:35°C SAFE

Delay:
delay(2000);

ESP32 waits:
2 seconds before taking the next reading.
This prevents excessive LCD refresh and unnecessary sensor polling.


🔰 Real-World Applications of Smart Temperature Monitoring System:
The Smart Temperature Monitoring System can be used in various real-world applications where continuous temperature monitoring and alert generation are required.

✅ 1. Server Rooms and Data Centers:
Monitors the temperature of servers and networking equipment.
Prevents overheating that may damage electronic components.
Generates alerts when temperature exceeds safe limits.

✅ 2. Industrial Equipment Monitoring:
Used in factories to monitor motors, transformers, generators, and machinery.
Helps prevent equipment failure due to excessive heat.
Supports preventive maintenance.

✅ 3. Cold Storage and Refrigeration:
Monitors temperature inside cold storage units, refrigerators, and food warehouses.
Ensures proper storage conditions for food and perishable products.
Alerts operators if temperature rises above acceptable levels.

✅ 4. Greenhouse and Smart Agriculture:
Monitors environmental conditions for plant growth.
Helps farmers maintain optimum temperature inside greenhouses.
Can be integrated with automatic cooling or irrigation systems.

✅ 5. Home Automation Systems:
Used in smart homes for room temperature monitoring.
Can automatically control fans, air conditioners, or ventilation systems.
Improves energy efficiency and comfort.

✅ 6. Laboratories and Research Facilities:
Monitors temperature-sensitive experiments and equipment.
Protects samples, chemicals, and research instruments from overheating.
Provides continuous environmental monitoring.

✅ 7. Hospitals and Medical Storage:
Used to monitor temperature in medicine storage rooms and vaccine refrigerators.
Ensures compliance with healthcare temperature requirements.
Prevents spoilage of temperature-sensitive medical products.

✅ 8. Fire and Safety Warning Systems:
Detects abnormal temperature increases in electrical panels and enclosed spaces.
Provides early warning before overheating develops into a fire hazard.
Improves workplace safety.

✅ 9. IoT-Based Remote Monitoring Systems:
Since ESP32 includes Wi-Fi and Bluetooth, the project can be upgraded to send temperature data to:
Mobile applications
Cloud servers
IoT dashboards
Remote monitoring systems
Useful for Industry 4.0 and smart infrastructure applications.

✅ 10. Educational and Embedded Systems Training:
Used as a beginner-level embedded systems project.
Demonstrates sensor interfacing, LCD communication, GPIO control, and alarm systems.
Suitable for learning IoT and embedded firmware development.

🔰 Future Enhancements:
This project can be further enhanced by:

🔸Adding Wi-Fi-based monitoring using ESP32.
🔸Sending alerts to a smartphone.
🔸Storing temperature data on a cloud platform.
🔸Controlling cooling devices automatically using relays.
🔸Implementing data logging and graphical dashboards.
🔸Viva Answer (Short Form)

🟡 This Smart Temperature Monitoring System can be used in industries, server rooms, laboratories, cold storage facilities, hospitals, greenhouses, and smart homes for real-time temperature monitoring and over-temperature alert generation. Using ESP32, the system can also be upgraded into a complete IoT-based remote monitoring solution.
