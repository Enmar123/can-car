
int a =0;
char data[1];

void setup() {
Serial.begin(9600);              //Starting serial communication
}
  
void loop() {
//  a++;                          // a value increase every loop
//  sprintf(dataString,"%02X",a); // convert a value to hexa 
//  Serial.println(dataString);   // send the data
//  delay(1000);                  // give the loop some break

a = a + 1;                    // max count is up to +- 32767
String data = String(a);
Serial.println(data);
delay(50);                 // "Spent" terminal windows cause slowdowns

//char data = 'a';
//sprintf(dataString,"%02X",data);
//Serial.println(data);
//delay(2000);

//data[1] = x;                          // a value increase every loop
//sprintf(dataString,"%02X",a); // convert a value to hexa 
//Serial.println(dataString);   // send the data
//Serial.print(data[1]);
//Serial.print(dataString);
//delay(1000);                  // 
}
