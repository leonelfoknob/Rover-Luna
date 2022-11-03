/****************************** Read pressure sensor and print value to serial monitor and lcd screen *******************/
/*
 * vcc->5v
 * gnd->GND
 * SCL->SCL OR A5
 * SDA->SDA OR A4
 */
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define seaLevelPressure_hPa 1013.25

   float Temperature;
   int Pressure;
   int Altitude;
   float ReadSealevelPressure;
   float Real_altitude;
   int Speed;

Adafruit_BMP085 bmp;
  
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  
  Serial.begin(9600);
  
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  
}
  
void loop() {

   //check sensor value
   Temperature =bmp.readTemperature();
   Pressure =bmp.readPressure();
   Altitude=bmp.readAltitude();
   ReadSealevelPressure =bmp.readSealevelPressure();
   Real_altitude =bmp.readAltitude(seaLevelPressure_hPa * 100);
   
   //lcd print
   lcd.setCursor(0, 0);
   lcd.print("T:");
   lcd.setCursor(2, 0);
   lcd.print(Temperature);
   lcd.print("C");
   lcd.print(" ");
   
   lcd.setCursor(9, 0);
   lcd.print("A:");
   lcd.setCursor(11, 0);
   lcd.print(Altitude);
   lcd.print("m");
   lcd.print(" ");

   lcd.setCursor(0, 1);
   lcd.print("P:");
   lcd.setCursor(2, 1);
   lcd.print(Pressure);
   lcd.print("P");
   lcd.print(" ");

   lcd.setCursor(9, 1);
   lcd.print("S:");
   lcd.setCursor(11, 1);
   lcd.print(Speed);
   lcd.print("m/s");
   lcd.print(" ");
   
   //serial print
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
    Serial.println(" meters");

    Serial.print("Speed = ");
    Serial.print(Speed);
    Serial.println("km/h");
    
    Serial.println();
    
}
