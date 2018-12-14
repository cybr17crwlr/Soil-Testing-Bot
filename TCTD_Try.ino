int intr = 13;
int inp = 12;
int npk[3] = {50,200,3000};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(intr, OUTPUT);
  pinMode(inp, INPUT);
  digitalWrite(intr, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(inp))
  {
    for (int i=0; i<10; i++)
    {
      npk[0] += 12;
      npk[1] += 25;
      npk[2] += 3;
      digitalWrite(intr, HIGH);
      Serial.print(String(npk[0]) + "," + String(npk[1]) + "," + String(npk[2]) + "|");
      
      digitalWrite(intr, LOW);
      delay(500);
    }
    npk[0] = 50;
    npk[1] = 200;
    npk[2] = 3000;
  }
}
