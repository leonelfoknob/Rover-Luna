//---------------------> Rover verici hc-12 arduino uno <-------------------------
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
SoftwareSerial HC12(5, 6);//tx,rx

int pot = A2 ;
int j1x = A1 ;
int j1y = A0 ;
int j2x = A3 ;

//data will be send
int send_joy1_x;
int send_joy1_y;
int send_joy2_x;
int send_pot_val;

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
}

void loop() {
  send_joy1_x = analogRead(j1x);
  send_joy1_y = analogRead(j1y);
  send_joy2_x = analogRead(j2x);
  send_pot_val = analogRead(pot);
  send_pot_val = map(send_pot_val,0,1023,60,255); //map 60-255 car la voiture commence a rouler a 70
  Serial.print("sended data : ");Serial.print(send_joy1_x);Serial.print(",");Serial.print(send_joy1_y);Serial.print(",");Serial.print(send_joy2_x);Serial.print(",");Serial.print(send_pot_val);Serial.println("");
  
  //----------->sended
  
  HC12.print(send_joy1_x);//sends the variables
  HC12.print(",");
  HC12.print(send_joy1_y);
  HC12.print(",");
  HC12.print(send_joy2_x);
  HC12.print(",");
  HC12.print(send_pot_val);
  HC12.println("");
  
  //----------->Received

  if(HC12.available()){
  Receive_Data = HC12.readStringUntil('\n');
  if (Receive_Data.length() > 0){
        receive_Latitude = (getValue(Receive_Data,Serparator, 0)).toFloat();
        receive_Longitude = (getValue(Receive_Data,Serparator, 1)).toFloat();
        receive_Speed = (getValue(Receive_Data,Serparator, 2)).toInt();
        receive_Temperature = (getValue(Receive_Data,Serparator, 3)).toFloat();
        receive_Pressure = (getValue(Receive_Data,Serparator, 4)).toInt();
        receive_Altitude = (getValue(Receive_Data,Serparator, 5)).toInt();

        //print to lcd Received value
       /*lcd.setCursor(0, 0);
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
       lcd.print(" ");*/
        
        Serial.println("Received...");
        Serial.print("Receive : ");Serial.println(Receive_Data);
        Serial.println(" ");
  //delay(1);
      }
  }
  
  //print to lcd sended value
  lcd.setCursor(0, 0);
  lcd.print(send_joy1_x);
  lcd.print("    ");
  lcd.setCursor(5, 0);
  lcd.print(send_joy1_y);
  lcd.print("    ");
  lcd.setCursor(10, 0);
  lcd.print(send_joy2_x);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print(send_pot_val);
  lcd.print("  ");
  
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
