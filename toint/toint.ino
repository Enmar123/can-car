
int a = 0;
int bump = 1;
int input =666;

void setup() {
Serial.begin(9600);              //Starting serial communication
}
  
void loop() {
  String datain = String(input);              //Serial.read();
  int number = datain.toInt();
  //int bump = int(toInt(datain));
  //Serial.print(datain);
  //Serial.println(100);
  
  //Serial.println(bump);
  
  Serial.println(number);
  //Serial.println(input);
  
//  Serial.println(datain);

  if(number == 666)
  {
    Serial.println("SATAN! ABSFDJV$*QR(%UW%W*$%W($%WIBTO");
  }
// 
  
  delay(1000);

}
