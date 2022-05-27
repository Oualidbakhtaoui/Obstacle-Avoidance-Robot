#include<Servo.h>

#define LA 2   // LA in1 pin          //in1 and in2 signal goes to arduino
#define LB 3  // lb is in2 pin         //connect in1 of l298shield to ard1 in2 to ard3 in3(for 2nd motor) to ard pin 4 in4 to ard5 and enable ENA for for motor 1 to ard6 and enable ENB for motor 2 to ard7
#define RA 4
#define RB 5
#define ENA 6
#define ENB 7

#define TrigPin 13                      // connect pin 13 to trigger pin of ultrasonic sensor and pin12 to Echo pin of ultrasonic sensor
#define EchoPin 12
Servo SM;

void setup() {

// motor driver pinMode settings
pinMode(LA, OUTPUT);
pinMode(LB, OUTPUT); 
pinMode(RA, OUTPUT);
pinMode(RB, OUTPUT);
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);

analogWrite(ENA, 120);   // for controlling speed of motor1
analogWrite(ENB, 120);   // for controlling speed of motor 2

// ultra sonic pinmode settings
pinMode(TrigPin, OUTPUT);
pinMode(EchoPin, INPUT);

// initialize the serial port
Serial.begin(9600);
  SM.attach(9); // connect servo motor to pin9 of arduino
  SM.write(90); // 90 angle shift so that ultrasonic look straight
  delay(3000);
  
}
int distance; // global variable 
void loop() {
  FindDistance();
if (distance > 35){
  Forward();
  }
  else{
  delay(60);
  FindDistance();
  if(distance>35){
    Forward();
    }else{
      Stop();
      SM.write(40);
      delay(500);
      FindDistance();
      if(distance > 35){
      SM.write(90);
      delay(500);
        Right(); //  now the robot will look to right for an object
        delay(300);
        Stop();
        }else{
          SM.write(140);
          delay(1000);
          FindDistance();
          if(distance > 35){
            SM.write(90);
      delay(500);
            Left();
            delay(400);
            Stop();            
            }else{         // this line will rotate the robot in 180 degress if it is in corner or there is obstacle in all 3 directions
              SM.write(90);
              delay(500);
              Right();
              delay(800);
              Stop();
              }
          }
      }
    }
}
void Forward(){

digitalWrite(LA,HIGH);
digitalWrite(LB,LOW);
digitalWrite(RA,HIGH);
digitalWrite(RB,LOW);

}

void BackWard(){
digitalWrite(LA,LOW);
digitalWrite(LB,HIGH);
digitalWrite(RA,LOW);
digitalWrite(RB,HIGH);

}

void Right(){

digitalWrite(LA,HIGH);
digitalWrite(LB,LOW);
digitalWrite(RA,LOW);
digitalWrite(RB,HIGH);

}

void Left(){

digitalWrite(LA,LOW);
digitalWrite(LB,HIGH);
digitalWrite(RA,HIGH);
digitalWrite(RB,LOW);

}

void Stop(){
digitalWrite(LA,LOW);
digitalWrite(LB,LOW);
digitalWrite(RA,LOW);
digitalWrite(RB,LOW);

}
void FindDistance(){
int duration;
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin,LOW);
duration = pulseIn(EchoPin,HIGH);
distance = (duration/2)*(1/29.1);
Serial.println(distance);
delay(60);

}
