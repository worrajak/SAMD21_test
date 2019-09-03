#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <ArduinoLowPower.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C #define BME280_ADDRESS                (0x76)

#define I2C_ADDRESS 0x3C
#define RST_PIN -1
SSD1306AsciiWire oled;

float temperature = 0;
float humidity = 0;

void setup() {

  Serial.begin(9600);

  bool status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
 
  #if RST_PIN >= 0
    oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
  #else // RST_PIN >= 0
    oled.begin(&Adafruit128x64, I2C_ADDRESS);
  #endif // RST_PIN >= 0

  oled.setFont(Adafruit5x7);
}

void loop() {
    temperature = bme.readTemperature();
    humidity = bme.readHumidity();

    oled.clear();
    oled.println("SAMD21 Zero");
    oled.setCursor(0,2);
    oled.print(temperature,1);oled.print("C ");oled.print(humidity,1);oled.print("%");
    oled.setCursor(0,4);
    oled.print(bme.readPressure() / 100.0F,1);oled.print("hPa. ");oled.print(bme.readAltitude(SEALEVELPRESSURE_HPA),1);oled.print("m."); 
    Serial.println("Sleep.....");
    delay(10000);
    LowPower.deepSleep(20000);
}



