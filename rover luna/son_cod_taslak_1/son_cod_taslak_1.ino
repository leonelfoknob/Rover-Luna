//HC12 send string data
#include <Wire.h>
#include <SPI.h> 
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>
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

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int data[4];

int joy1_x;
int joy1_y;
int joy2_x;
int pot_val;

int com_f_b;
int com_l_r;
int com_speed;

Servo servo_directionL;
Servo servo_directionR;

int servo_init_val = 81;

int ena = 2;
int in1 = 48;
int in2 = 49;

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

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  servo_directionL.attach(6);
  servo_directionR.attach(5);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  servo_directionL.write(servo_init_val);
  servo_directionR.write(servo_init_val);

}

void loop() {
   //check sensor value
   Temperature =bmp.readTemperature();
   Pressure =bmp.readPressure();
   Altitude=bmp.readAltitude();
   
  //send_string_data = String(Temperature)+String(separator)+String(Pressure)+String(separator)+String(Altitude)+String(separator)+String(Speed);
  /*Serial.print("send_string_data :");
  Serial.println(send_string_data);*/
  //Serial.println(send_string_data);
  //HC12.print(send_string_data);
  /*HC12.print(Temperature);
  HC12.print(",");
  HC12.print(Pressure);
  HC12.print(",");
  HC12.print(Altitude);
  HC12.print("");*/

//lcd print
   /*lcd.setCursor(0, 0);
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
   lcd.print(" ");*/
/*******************************************/
  if (radio.available()) {
    radio.read(data, sizeof(data));

   joy1_x = data[0];
   joy1_y = data[1];
   joy2_x = data[2];
   pot_val = data[3];

   com_f_b = joy1_y;
   com_l_r = joy2_x;
   com_speed = pot_val;
   //ilere geri
   if(com_f_b < 400){
    forward(com_speed);
    lcd.setCursor(2, 0);
    lcd.print("forward ");
   }
   else if(com_f_b >600){
    back(com_speed);
    lcd.setCursor(2, 0);
    lcd.print("back   ");
   }
   else{
    forward(0);
    lcd.setCursor(2, 0);
    lcd.print("Stop   ");
   }
  //sağ sol
  if(com_l_r < 400){ //right sağa
    servo_directionL.write(90);
    servo_directionR.write(90);
    lcd.setCursor(10, 0);
    lcd.print("right");
  }
  else if(com_l_r > 600){ // left sola
    servo_directionL.write(70);
    servo_directionR.write(70);
    lcd.setCursor(10, 0);
    lcd.print("left");
  }
  else{
    servo_directionL.write(servo_init_val);
    servo_directionR.write(servo_init_val);
    lcd.setCursor(10, 0);
    lcd.print("      ");
  }
  }
   /***************************************************/
delay(1);
}

void back(int hiz){
  analogWrite(ena,hiz);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
}

void forward(int hiz){
  analogWrite(ena,hiz);
  digitalWrite(in1,0);
  digitalWrite(in2,1);
}
