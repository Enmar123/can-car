// Variable definitions for the codes below (space separated)

char datain = ' ';

char datastring[50] = {0};
char dataout;

int a = 0;
char data[1];

//-----------------------------------------------------------------

void setup() {
Serial.begin(9600);              //Starting serial communication
}

//------------------------------------------------------------------  

void loop() {

//// PI->INO chars (works) -----------------------------------------

if(Serial.available()){
  datain = char(Serial.read());
  Serial.println();
  Serial.println(datain);
  delay(250);
}
  
//// INO -> PI char (works) ------------------------------------------
//
//char datastring[50] = {0};
//char dataout;
//
//dataout = 'A';
//sprintf(datastring,"%02X",dataout);
//Serial.println(datastring);
//delay(1000);             // "Spent" terminal windows cause slowdowns
//
//dataout = 'B';
//sprintf(datastring,"%02X",dataout);
//Serial.println(datastring);
//delay(1000);

// INO -> PI nums (works) --------------------------------------

//a = a + 1;                    // max count is up to +- 32767
//String data = String(a);
//Serial.println(data);
//delay(100);             // "Spent" terminal windows -> slowdowns

}
