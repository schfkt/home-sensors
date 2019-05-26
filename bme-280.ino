#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <LiquidCrystal_I2C.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

#define DME280_ADDRESS 0x76

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

LiquidCrystal_I2C lcd(0x27,20,4);

unsigned long delayTime;

void printValues() {
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");
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
}

void setup() {
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin(DME280_ADDRESS);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 5000;

    Serial.println();

    lcd.init();
    lcd.backlight();
}

void loop() { 
    printValues();
    delay(delayTime);
}
