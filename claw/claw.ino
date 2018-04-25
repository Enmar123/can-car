#define IN12 12
#define IN13 13


// Function Setup -----------------------------------------
void close() {
  digitalWrite(IN12, HIGH);
  digitalWrite(IN13, LOW);
  Serial.println("Open sesame!");
} 
void open() {
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, HIGH);
  Serial.println("Chomp!");
} 

// Main Control Loop ------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IN12, OUTPUT);
  pinMode(IN13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  open();
  delay(2000);
  close();
  delay(1500); 
}
