//HC12 send string data
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial HC12(10,11);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

#define seaLevelPressure_hPa 1013.25
Adafruit_BMP085 bmp;

float Temperature;
int Pressure;
int Altitude;
int Speed;

char separator =',';
String send_string_data;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);

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
   
  send_string_data = String(Temperature)+String(separator)+String(Pressure)+String(separator)+String(Altitude)+String(separator)+String(Speed);
  /*Serial.print("send_string_data :");
  Serial.println(send_string_data);*/
  //Serial.println(send_string_data);
  HC12.print(send_string_data);

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
delay(1000);
}
