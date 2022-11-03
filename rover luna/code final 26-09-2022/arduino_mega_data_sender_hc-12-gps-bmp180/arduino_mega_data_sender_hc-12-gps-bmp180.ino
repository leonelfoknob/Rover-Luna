 /*   
modified on Sep 27, 2020
Modified by MohammedDamirchi from https://github.com/mikalhart/TinyGPSPlus
Home 
*/ 
//gps pressure sensore hc-12 arduino mega rover luna send data**********/
/*
 * Siyah: GND
    Yeşil: TX
    Sarı: RX
    Kırmızı: + 5V
    Beyaz: SDA
    Turuncu: SCL
    Çap: 53mm
    Kablo Uzunluğu: ~15cm
    Ağırlık: 31gr.
 */

#include <Wire.h>
#include<Servo.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 13, TXPin = 12; //i change it myself and it is work
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
SoftwareSerial HC12(10, 11);//tx,rx
#define seaLevelPressure_hPa 1013.25
Adafruit_BMP085 bmp;

float Latitude;
float Longitude;
int Speed;
int hours;
int minutes;
int seconde;
int days;
int months;
int years;

//data will be send
int send_Speed;
float send_Latitude;
float send_Longitude;
int send_Pressure;
int send_Altitude;
float send_Temperature;


void setup()
{

  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  HC12.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
      
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Latitude = gps.location.lat();
    Longitude = gps.location.lng();
  }
  if (gps.date.isValid())
  {
    days = gps.date.day();
    months = gps.date.month() ;
    years = gps.date.year() ;
  }
  if (gps.time.isValid())
  {
    hours = gps.time.hour()+3;
    minutes = gps.time.minute();
    seconde = gps.time.second();
  }
  if (gps.speed.isValid())
  {
    Speed = gps.speed.kmph();
    //Serial.print("  speed :");Serial.println(Speed);
  }
    Serial.println(); 
    Serial.print("Date : ");Serial.print(days);Serial.print("/");Serial.print(months);Serial.print("/");Serial.println(years);
    Serial.print("HOUR : ");Serial.print(hours);Serial.print(":");Serial.print(minutes);Serial.print(":");Serial.println(seconde);
    Serial.print("Latitude : ");Serial.print(Latitude,6);Serial.print("  ");Serial.print("longitude : ");Serial.println(Longitude,6);
    Serial.print("Speed : ");Serial.println(Speed);
    Serial.println();

    //data will be receive
    send_Speed = Speed;
    send_Latitude = Latitude;
    send_Longitude = Longitude;
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
