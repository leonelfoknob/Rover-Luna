 /*   
modified on Sep 27, 2020
Modified by MohammedDamirchi from https://github.com/mikalhart/TinyGPSPlus
Home 
*/ 
//gps arduino mega rover luna**********/
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

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 13, TXPin = 12; //i change it myself and it is work
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

float Latitude;
float Longitude;
int Speed;
int hours;
int minutes;
int seconde;
int days;
int months;
int years;


void setup()
{
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
  //Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Latitude = gps.location.lat();
    Longitude = gps.location.lng();
    
    /*Serial.print(Latitude,6);
    Serial.print(F(","));
    Serial.print(Longitude,6);*/
  }
  /*else
  {
    Serial.print(F("INVALID"));
  }*/

  //Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    days = gps.date.day();
    months = gps.date.month() ;
    years = gps.date.year() ;
    
   /* Serial.print(days);
    Serial.print(F("/"));
    Serial.print(months);
    Serial.print(F("/"));
    Serial.print(years);*/
  }
  /*else
  {
    Serial.print(F("INVALID"));
  }*/

  //Serial.print(F(" "));
  if (gps.time.isValid())
  {
    hours = gps.time.hour()+3;
    minutes = gps.time.minute();
    seconde = gps.time.second();
    
    /*if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(hours);
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(minutes);
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(seconde);*/
  }
  /*else
  {
    Serial.print(F("INVALID"));
  }*/
  if (gps.speed.isValid())
  {
    Speed = gps.speed.kmph();
    //Serial.print("  speed :");Serial.println(Speed);
  }
  /*else{
    Serial.println(" invalid speed");
  }*/
    Serial.println(); 
    
    Serial.print("Date : ");Serial.print(days);Serial.print("/");Serial.print(months);Serial.print("/");Serial.println(years);
    Serial.print("HOUR : ");Serial.print(hours);Serial.print(":");Serial.print(minutes);Serial.print(":");Serial.println(seconde);
    Serial.print("Latitude : ");Serial.print(Latitude,6);Serial.print("  ");Serial.print("longitude : ");Serial.println(Longitude,6);
    Serial.print("Speed : ");Serial.println(Speed);

    Serial.println();
}
