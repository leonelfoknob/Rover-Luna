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
*/
//---------------------> Rover verici <-------------------------
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int pot = A2 ;
int j1x = A1 ;
int j1y = A0 ;
int j2x = A3 ;


int joy1_x;
int joy1_y;
int joy2_x;
int pot_val;

int data[4];


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

void loop() {
  joy1_x = analogRead(j1x);
  joy1_y = analogRead(j1y);
  joy2_x = analogRead(j2x);

  pot_val = analogRead(pot);
  pot_val = map(pot_val,0,1023,60,255); //map 60-255 car la voiture commence a rouler a 70
  
  data[0] = joy1_x; //orta deger = 515
  data[1] = joy1_y; //orta deger = 513
  data[2] = joy2_x; //orta deger = 572
  data[3] = pot_val;
  
  Serial.print(data[0]);
  Serial.print(" | ");
  Serial.print(data[1]);
  Serial.print(" | ");
  Serial.print(data[2]);
  Serial.print(" | ");
  Serial.println(data[3]);
  
  radio.write(&data, sizeof(data));
  delay(1);

  lcd.setCursor(0, 0);
  lcd.print(joy1_x);
  lcd.print("    ");
  lcd.setCursor(5, 0);
  lcd.print(joy1_y);
  lcd.print("    ");
  lcd.setCursor(10, 0);
  lcd.print(joy2_x);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print(pot_val);
  lcd.print("  ");
  
}
