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
#define IN12 12
#define IN13 13

char datain = 'O';
int a = 0;
int mod_delay;
int turnSpeed = 200;

// USER INPUTS --------------------------------------------

#define carSpeed 150
#define carspeed2 100
#define turnSpeed1 200
#define turnSpeed2 250
#define delay1 100
#define turntime 720        
#define forwardtime 2150

int rightDistance = 0, leftDistance = 0, middleDistance = 0;



// Function Setup -----------------------------------------

void avoidR(){ 
  turnSpeed = turnSpeed2;
  
  right();
  delay(turntime);
  forward();              //go forward
  delay(forwardtime);          //delay 1000 ms
  left();                 //turning left
  delay(turntime);
  forward();              //go forward
  delay(forwardtime);          //delay 1000 ms
  left();                 //turning left
  delay(turntime/2);
  //forward();              //go forward
  //delay(forwardtime-750);      //delay 1000 ms
  
  turnSpeed = turnSpeed1;
  
  //right();                //turning left
  //delay(turntime);
  //forward();              //go forward
  //delay(forwardtime-750);      //delay 1000 ms
}

void avoidL(){
  turnSpeed = turnSpeed2;
  
  left();
  delay(turntime);
  forward();              //go forward
  delay(forwardtime);          //delay 1000 ms
  right();                //turning left
  delay(turntime);
  forward();              //go forward
  delay(forwardtime);          //delay 1000 ms
  right();                //turning left
  delay(turntime/2);
  //forward();              //go forward
  //delay(forwardtime-750);      //delay 1000 ms
  
  turnSpeed = turnSpeed1;
  
  //left();                 //turning left
  //delay(turntime);
  //forward();              //go forward
  //delay(forwardtime-750);      //delay 1000 ms
}

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

void merge() {
  int test = 0;
  while(test == 0){
    Serial.println("Merging!");
    forward();
    if(LT_M==1){
      test = 1;
    }
  }
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

//Claw functions
void close() {
  digitalWrite(IN12, HIGH);
  digitalWrite(IN13, LOW);
  Serial.println("Chomp!");
  delay(1500);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
}

void open() {
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, HIGH);
  Serial.println("Open sesame!");
  delay(2200);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
} 

//----------------------------------------------------------------

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
  pinMode(IN12, OUTPUT);
  pinMode(IN13, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
  
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
} 

// Main Control Loop ------------------------------------------------

// Note: Black line = 1 or high
void loop() { 
  unsigned long loopstart = millis();
  
  // PI->INO Serial in 
  while(Serial.available()){
  datain = char(Serial.read());
  }
  
  // VISION BEHAVIOR -----------------------
  
  if(datain != 'O'){
    Serial.println("-----VISION BEHAVIOR-----");
  /*  
    middleDistance = Distance_test();
    
    if(middleDistance <= 27){
      stop();
      
      if (datain == 'M'){
        open();
        delay(500);
        forward();
        delay(500);
        close();       
      }
    }
  */
    if(datain == 'M'){
      
      middleDistance = Distance_test();
      
      if(middleDistance <= 27){
        stop();
        open();
        delay(500);
        forward();
        delay(500);
        close();
      }
      else{
        forward();
        Serial.println("Following forward!");
      }
    }
    else if(datain == 'R'){
      right();
      Serial.println("Following Right!");
    }
    else if(datain == 'L'){
      left();
      Serial.println("Following left!");
    }
  }
  else if(datain == 'O'){
  // OBSTACLE AVOIDANCE---------------------
  
  //myservo.write(90);  //(initial 90/modified to 125)setservo position according to scaled value
  //delay(500); 
  middleDistance = Distance_test();

  if(middleDistance <= 27) {
  Serial.println("-----AVOID BEHAVIOR-----");
  
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
      
      //Double checking incase object moved away
      middleDistance = Distance_test(); 
      
      if(middleDistance <= 27){
        if(rightDistance > leftDistance) {
          avoidR();
          merge();
        }
        else if(rightDistance < leftDistance) {
          avoidL();
          merge();
        }
        else if((rightDistance <= 20) || (leftDistance <= 20)) {
          back();
          delay(180);
        }
      }
  }

// LINE TRACKING ----------------------

  Serial.println("-----LINE BEHAVIOR-----");
  
  unsigned long StartTime = millis();
  
  if((LT_R==0 && LT_M==0 && LT_L==0) || (LT_R==1 && LT_M==1 && LT_L==1)){
    forward();
  }
  else if(LT_R==0 && LT_M==1 && LT_L==0){
    forward();
    a=a-1;
  }
  else if((LT_R==1 && LT_M==0 && LT_L==0) || (LT_R==1 && LT_M==1 && LT_L==0)) { 
    right();
    a=a+1;
    delay(mod_delay);                             
  }   
  else if((LT_R==0 && LT_M==0 && LT_L==1) || (LT_R==0 && LT_M==1 && LT_L==1)) {
    left();
    a=a+1;
    delay(mod_delay);  
  }
  else if(LT_R==1 && LT_M==0 && LT_L==1) {  
    right();
    delay(delay1);
  }
  
  forward();
  delay(25);
  }

// Post Loop Calculations -------------
  
  if(a > 6){
    a = 6;
  }
  else if(a < 0){
    a = 0;
  }
  
  mod_delay = delay1 + a*25;
  
  //unsigned long CurrentTime = millis();
  //unsigned long ElapsedTime = CurrentTime - StartTime;
  
  unsigned long loopend = millis();
  unsigned long looptime = loopend - loopstart;
  
  // Serial Feedback -------------------------
  
  Serial.println("");
  Serial.print("looptime = ");
  Serial.println(looptime);
  //Serial.println(ElapsedTime);
  //Serial.println(CurrentTime);
  Serial.print("data in = ");
  Serial.println(datain);
  Serial.print("mod_delay = ");
  Serial.println(mod_delay);
  Serial.print("middleDistance = ");
  Serial.println(middleDistance);  
}  
