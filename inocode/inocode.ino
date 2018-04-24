//Line Tracking IO define ---------------------------------
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo  

int Echo = A4;  
int Trig = A5; 

#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

// USER INPUTS --------------------------------------------

#define carSpeed 150
#define delay1 100
#define turnSpeed 250
#define turntime 360
#define forwardtime 2150
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

// Function Setup -----------------------------------------
void forward(){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  analogWrite(IN1, 240);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 255);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 0);
  analogWrite(IN4, 255); 
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  analogWrite(IN1, 255);
  analogWrite(IN2, 0);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} 

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  

void setup(){
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
} 

// Main Control Loop ------------------------------------------------

// Note: Black line = 1 or high
void loop() { 
   //myservo.write(90);  //(initial 90/modified to 125)setservo position according to scaled value
    //delay(500); 
    middleDistance = Distance_test();

if(middleDistance <= 27) {     
      stop();
      delay(500);                         
      myservo.write(10);          
      delay(1000);      
      rightDistance = Distance_test();
      
      delay(500);
      myservo.write(90);     //initial 90/modified to 125         
      delay(1000);                                                  
      myservo.write(180);              
      delay(1000); 
      leftDistance = Distance_test();
      
      delay(500);
      myservo.write(90);     //initial 90/modified to 125         
      delay(1000);
      if(rightDistance > leftDistance) {
        right();
        delay(turntime+40);
          forward();  //go forward
          delay(forwardtime);//delay 1000 ms
            left();     //turning left
            delay(turntime);
              forward();  //go forward
              delay(forwardtime);//delay 1000 ms
                left();     //turning left
                delay(turntime);
                  forward();  //go forward
                  delay(forwardtime-750);//delay 1000 ms
                    right();     //turning left
                    delay(turntime);
                      forward();  //go forward
                      delay(forwardtime-750);//delay 1000 ms
      }
      else if(rightDistance < leftDistance) {
        left();
        delay(turntime+40);
          forward();  //go forward
          delay(forwardtime);//delay 1000 ms
            right();     //turning left
            delay(turntime);
              forward();  //go forward
              delay(forwardtime);//delay 1000 ms
                right();     //turning left
                delay(turntime);
                  forward();  //go forward
                  delay(forwardtime-750);//delay 1000 ms
                    left();     //turning left
                    delay(turntime);
                      forward();  //go forward
                      delay(forwardtime-750);//delay 1000 ms
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        back();
        delay(180);
      }
  }
      
  else if(LT_M ){
    forward();
  }
  else if(LT_R || (LT_R && LT_M)) { 
    right();
    while(LT_R);                             
  }   
  else if(LT_L || (LT_L && LT_M)) {
    left();
    while(LT_L);  
  }

}  
