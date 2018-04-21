
int a = 0;
int bump = 0;
//char data[1];

const byte MAXIMUM_INPUT_LENGTH = 10;
char input[MAXIMUM_INPUT_LENGTH+1] = {'\0'};
byte currentIndex = 0;

//char datain[1];

void setup() {
Serial.begin(9600);              //Starting serial communication
}
  
void loop() {

if(Serial.available()){
  
   if (Serial.available()){
   if (currentIndex>=MAXIMUM_INPUT_LENGTH){
     for (byte i=0; i<=MAXIMUM_INPUT_LENGTH; i++){
       input = '\0'; //clear input
     }
     currentIndex = 0; //start over
   }
   input[currentIndex++] = Serial.read(); //append to input
   
   Serial.print("input is: ");
   Serial.println(input);
   }
}
}
  
  
  
  
//  String datain = String(Serial.read());
//  int number = datain.toInt();
//  //int number = datain.remove(1,2)
//  //String number = datain.remove(0, 1);
//  //int num = number.toInt();
//  int number1 = number - 48;
//  //a = a + number;
//  //Serial.println(Serial.read());
//  //delay(250);
//  //Serial.println(datain);
//  //delay(250);
//  Serial.println(number1); 
//  delay(250);
//}

//a = a + 1;                    // max count is up to +- 32767
//String data = String(a);
//Serial.println(data);
//delay(1000);                 // "Spent" terminal windows cause slowdowns

//}
