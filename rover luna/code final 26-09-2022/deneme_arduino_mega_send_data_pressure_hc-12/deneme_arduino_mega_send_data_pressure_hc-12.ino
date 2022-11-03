//-----------------------------> Rover verici arduino mega<---------------------------------------
#include <Wire.h>
#include<Servo.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
SoftwareSerial HC12(10, 11);//tx,rx
#define seaLevelPressure_hPa 1013.25
Adafruit_BMP085 bmp;

//data will be send
int send_Speed;
float send_Latitude;
float send_Longitude;
int send_Pressure;
int send_Altitude;
float send_Temperature;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  Serial.begin(9600);
  HC12.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}
void loop() {
    //data will be receive
    send_Speed = 0;
    send_Latitude = 0.5;
    send_Longitude = 0.6;
    send_Pressure = bmp.readPressure();
    send_Altitude = bmp.readAltitude();
    send_Temperature = bmp.readTemperature();;
 
  HC12.print(send_Speed);//sends the variables
  HC12.print(",");
  HC12.print(send_Latitude);
  HC12.print(",");
  HC12.print(send_Longitude);//if you just need to send 2 variables,simply change this value and the following to 0
  HC12.print(",");
  HC12.print(send_Pressure);//if you just need to send 3 variables,simply change this value and the next to 0
  HC12.print(",");
  HC12.print(send_Altitude);
  HC12.print(",");
  HC12.print(send_Temperature);//if you just need to send 4 variables,simply change this value to 0
  HC12.println("");
  delay(1);
//print sended data to lcd
       lcd.setCursor(0, 0);
       lcd.print("T:");
       lcd.setCursor(2, 0);
       lcd.print(send_Temperature);
       lcd.print("C");
       lcd.print(" ");
       
       lcd.setCursor(9, 0);
       lcd.print("A:");
       lcd.setCursor(11, 0);
       lcd.print(send_Altitude);
       lcd.print("m");
       lcd.print(" ");
    
       lcd.setCursor(0, 1);
       lcd.print("P:");
       lcd.setCursor(2, 1);
       lcd.print(send_Pressure);
       lcd.print("P");
       lcd.print(" ");
    
       lcd.setCursor(9, 1);
       lcd.print("S:");
       lcd.setCursor(11, 1);
       lcd.print(send_Speed);
       lcd.print("m/s");
       lcd.print(" ");
}
