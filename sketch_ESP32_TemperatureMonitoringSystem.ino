#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

#define LED_PIN 2
#define BUZZER_PIN 15

#define TEMP_THRESHOLD 35

DHT dht(DHTPIN, DHTTYPE);

// LCD Address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Temperature");
  lcd.setCursor(0,1);
  lcd.print("Monitoring");

  delay(2000);
  lcd.clear();
}

void loop()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("DHT11 Error!");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor Error");

    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C  ");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(10,0);
  lcd.print("H:");
  lcd.print((int)humidity);

  lcd.setCursor(0,1);
  lcd.print("TH:");
  lcd.print(TEMP_THRESHOLD);
  lcd.print((char)223);
  lcd.print("C");

  if (temperature >= TEMP_THRESHOLD)
  {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    lcd.setCursor(10,1);
    lcd.print("ALERT!");
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    lcd.setCursor(10,1);
    lcd.print("SAFE ");
  }

  delay(2000);
}