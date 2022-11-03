// whell and servo motor 
#include<Servo.h>

Servo servo_direction;
int servo_init_val = 81;

int ena = 5;
int in1 = 2;
int in2 = 4;

int enb = 10;
int in3 = 6;
int in4 = 9;

void setup() {

  servo_direction.attach(3);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  servo_direction.write(servo_init_val);

}

void loop() {
  
  forward();
  servo_direction.write(90);
  delay(1000);
  
  back();
  servo_direction.write(servo_init_val);
  delay(1000);
  
}

void back(){
  analogWrite(ena,100);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
}

void forward(){
  analogWrite(ena,100);
  digitalWrite(in1,0);
  digitalWrite(in2,1);
}
