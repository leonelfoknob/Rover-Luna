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
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int data[4];

int joy1_x;
int joy1_y;
int joy2_x;
int pot_val;



void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  //Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    radio.read(data, sizeof(data));

   joy1_x = data[0];
   joy1_y = data[1];
   joy2_x = data[2];
   pot_val = data[3];

   lcd.setCursor(0, 0);
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
   lcd.print("  ");

  }
    else{
    lcd.setCursor(1, 0);
    lcd.print("   veri yok");
    lcd.setCursor(1, 1);
    lcd.print("ver kontrol edin");
    delay(100);
    lcd.clear();
    delay(100);
    }
}
