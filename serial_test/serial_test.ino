
int a = 0;
int bump = 0;
char data[1];
char datain[1];

void setup() {
Serial.begin(9600);              //Starting serial communication
}
  
void loop() {
if(Serial.available()){
  datain = Serial.read();
  int bump = toInt(datain);
}

a = a + 1;                    // max count is up to +- 32767
String data = String(a);
Serial.println(data);
delay(1000);                 // "Spent" terminal windows cause slowdowns

}
