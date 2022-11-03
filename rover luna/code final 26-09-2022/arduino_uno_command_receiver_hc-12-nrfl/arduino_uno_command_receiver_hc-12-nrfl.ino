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
//---------------------> Rover verici hc-12 with nrfl24 arduino uno 26/09/2022 <-------------------------
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial HC12(5, 6);//tx,rx
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

//data will be receive
int receive_Speed;
float receive_Latitude;
float receive_Longitude;
int receive_Pressure;
int receive_Altitude;
float receive_Temperature;

String Receive_Data;
char Serparator = ',';


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  Serial.begin(9600);
  HC12.begin(9600);

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

  /*lcd.setCursor(0, 0);
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
  lcd.print("  ");*/

    //----------->Received

  if(HC12.available()){
  Receive_Data = HC12.readStringUntil('\n');
  if (Receive_Data.length() > 0){
        receive_Speed  = (getValue(Receive_Data,Serparator, 0)).toInt();
        receive_Latitude = (getValue(Receive_Data,Serparator, 1)).toFloat();
        receive_Longitude = (getValue(Receive_Data,Serparator, 2)).toFloat();
        receive_Pressure = (getValue(Receive_Data,Serparator, 3)).toInt();
        receive_Altitude = (getValue(Receive_Data,Serparator, 4)).toInt();
        receive_Temperature = (getValue(Receive_Data,Serparator, 5)).toFloat();

        //print to lcd Received value
       lcd.setCursor(0, 0);
       lcd.print("T:");
       lcd.setCursor(2, 0);
       lcd.print(receive_Temperature);
       lcd.print("C");
       lcd.print(" ");
       
       lcd.setCursor(9, 0);
       lcd.print("A:");
       lcd.setCursor(11, 0);
       lcd.print(receive_Altitude);
       lcd.print("m");
       lcd.print(" ");
    
       lcd.setCursor(0, 1);
       lcd.print("P:");
       lcd.setCursor(2, 1);
       lcd.print(receive_Pressure);
       lcd.print("P");
       lcd.print(" ");
    
       lcd.setCursor(9, 1);
       lcd.print("S:");
       lcd.setCursor(11, 1);
       lcd.print(receive_Speed);
       lcd.print("m/s");
       lcd.print(" ");
        
        Serial.println("Received...");
        Serial.print("Receive : ");Serial.println(Receive_Data);
        Serial.println(" ");
  //delay(1);
      }
  }
  
}

//function to separate string separate by one charatere for each position's data
String getValue(String data, char separator, int index){
int found = 0;
int strIndex[] = {0, -1};
int maxIndex = data.length()-1;
for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
    found++;
    strIndex[0] = strIndex[1]+1;
    strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
}
return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
