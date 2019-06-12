// BME280 Temperature, Humidity, and Pressure sensor
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME280_ADDR 0x76

Adafruit_BME280 bme;

// LCD
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// MHZ19B CO2 sensor
#include <MHZ19_uart.h>

// Serial pins where the sensor is connected to
#define MHZ_RX 2
#define MHZ_TX 3

MHZ19_uart mhz19;

// How often should we update readings, ms
#define REFRESH_INTERVAL 10000

// Here we read the data and print it to LCD
void refreshSensorReadings() {
  Serial.println(F("Refreshing readings..."));

  lcd.setCursor(0, 0);
  lcd.print("Temp:     ");
  lcd.print(bme.readTemperature());
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Pressure: ");
  lcd.print(bme.readPressure() / 100.0F);
  lcd.print("hPa");

  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.print(bme.readHumidity());
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("CO2:      ");
  lcd.print(mhz19.getPPM());
  lcd.print("PPM");
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("Starting..."));

  // Init BME280
  Serial.println(F("BME280..."));

  if (!bme.begin(BME280_ADDR)) {
    Serial.println("Failed to connect to BME280 sensor");
    while (1);
  }

  // Init MHZ-19B
  Serial.println(F("MHZ-19B..."));

  mhz19.begin(MHZ_TX, MHZ_RX);
  mhz19.setAutoCalibration(false);
  mhz19.getStatus();

  delay(500);

  if (mhz19.getStatus() != 0) {
    Serial.println(F("Failed to connect to MHZ-19B sensor"));
    while (1);
  }

  // LCD
  Serial.println("Init LCD...");

  lcd.init();
  lcd.backlight();
}

void loop() {
  refreshSensorReadings();
  delay(REFRESH_INTERVAL);
}
