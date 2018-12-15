//TCTD-IIT GUWAHATI
//This module needs to be added as a function to the control module
//After determining npk values, intr pin to be set to high for data transfer

//Set pins
int intr = 13;

//NPK values, currently set at random
//Determined values to be stored here
int npk[3] = {50,200,3000};

void setup() {
  //Start Serial
  Serial.begin(115200);
  //Set PinModes
  pinMode(intr, OUTPUT);
  digitalWrite(intr, LOW);
}

void loop() {
  //Start transmission
  digitalWrite(intr, HIGH);
  //Send serial data
  Serial.print(String(npk[0]) + "," + String(npk[1]) + "," + String(npk[2]) + "|");
  //End transmission to prevent data mismatch
  digitalWrite(intr, LOW);
  delay(500);
}
