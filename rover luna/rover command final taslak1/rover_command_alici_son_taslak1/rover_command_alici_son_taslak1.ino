/*
 * 3.3v and gnd use 10 nanofarad condansator and if you want change ce and cns pin
 * NRF24L01  PNA/LNA Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---------   
13  |SCK         MOSI| 11      ANTEN  |
12  |MISO        IRQ |      ---------
     ----------------

* NRF24L01 Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---  
13  |SCK         MOSI| 11     | ANTEN
12  |MISO        IRQ |      ---
     ----------------

* NRF24L01 Arduino Mega connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---  
52  |SCK         MOSI| 51     | ANTEN
50  |MISO        IRQ |      ---
     ----------------
     
*/

//-----------------------------> Rover alıcı <---------------------------------------
#include <SPI.h> 
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include<Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

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

Servo servo_direction;
int servo_init_val = 81;

int ena = 5;
int in1 = 2;
int in2 = 4;

int enb = 10;
int in3 = 6;
int in4 = 9;



void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  //Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  servo_direction.attach(3);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  servo_direction.write(servo_init_val);
}
void loop() {
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
    servo_direction.write(90);
    lcd.setCursor(10, 0);
    lcd.print("right");
  }
  else if(com_l_r > 600){ // left sola
    servo_direction.write(70);
    lcd.setCursor(10, 0);
    lcd.print("left");
  }
  else{
    servo_direction.write(servo_init_val);
    lcd.setCursor(10, 0);
    lcd.print("      ");
  }
   /*lcd.setCursor(0, 0);
   lcd.print("jx1:");
   lcd.setCursor(4, 0);
   lcd.print(joy1_x);
   lcd.print("  ");

   lcd.setCursor(9, 0);
   lcd.print("jy1:");
   lcd.setCursor(13, 0);
   lcd.print(joy1_y);
   lcd.print("  ");

   lcd.setCursor(0, 1);
   lcd.print("jx2:");
   lcd.setCursor(4, 1);
   lcd.print(joy2_x);
   lcd.print("  ");

   lcd.setCursor(9, 1);
   lcd.print("pot:");
   lcd.setCursor(13, 1);
   lcd.print(pot_val);
   lcd.print("  ");*/

  }
   /* else{
    lcd.setCursor(1, 0);
    lcd.print("   veri yok");
    lcd.setCursor(1, 1);
    lcd.print("ver kontrol edin");
    delay(100);
    lcd.clear();
    delay(100);
    }*/
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
