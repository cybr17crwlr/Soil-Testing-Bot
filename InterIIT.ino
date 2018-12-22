//TCTD - IIT GUWAHATI

//Import libraries
#include <Servo.h>
#include <math.h>

//Variables
Servo base_servo;
int pos = 60;
double npk[3];

//Pins
int intr            = 30; //NodeMCU Interrupt
int statusLed       = 13; //Show filling status
byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;  //Flow sensor pin
int fillPin         = 8;  //Activate filling pump-active low
int cleanPin        = 7;  //Activate cleaning pump-active low
int rPin            = 3;  //Red LED
int gPin            = 4;  //Green LED
int bPin            = 5;  //Blue LED
int servoPin        = 9;  //Servo Pin
int vibPin          = 12; //Vibrator Pin

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;

void setup() {
  
  Serial.begin(115200);
  Serial1.begin(115200);
  //Set Pins
  base_servo.attach(servoPin);         // Base Servo
  base_servo.write(pos);
  pinMode(rPin, OUTPUT);           // Red LED
  pinMode(gPin, OUTPUT);          // Green LED 
  pinMode(bPin, OUTPUT);          // Blue LED
  pinMode(vibPin, OUTPUT);          // Vibration crystal 
  pinMode(intr,OUTPUT);          //Interrupt to nodeMCU 
  pinMode(intr,LOW);  

  //Set up the status LED line as an output
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  
  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  //Set pump pins
  pinMode(fillPin, OUTPUT);
  pinMode(cleanPin, OUTPUT);
  //Turn off pumps
  digitalWrite(fillPin, HIGH);
  digitalWrite(cleanPin, HIGH);  
  digitalWrite(intr, LOW);
}


void loop() {
  base_servo.write(60);
  digitalWrite(fillPin, HIGH);
  digitalWrite(cleanPin, HIGH);
  digitalWrite(intr, LOW);
  //1. Insert Sample
  
  //2. Fill Water
  Serial.println("Filling Water");
  fillWater();
  
  //3. Mix
  Serial.println("Mixing");
  delay(3000);
  int shake_counter = 0; 
  digitalWrite(vibPin,HIGH);      //Turning vibrating crystal ON.
  for(shake_counter = 0; shake_counter<15; shake_counter += 1)    //Base Servo Shaker.
  {
  for ( ; pos <= 110; pos += 1) 
  { 
    base_servo.write(pos);              
    delay(2);                       
  }
  for (pos = 110; pos >= 60; pos -= 1) 
  { 
    base_servo.write(pos);              
    delay(2);                       
  }
  }
  digitalWrite(vibPin,LOW);                 //Turning vibrating crystal OFF.

  //4. Get values
  Serial.println("Getting Sensor data");
  delay(5000);  //Large delay
  int i = 0;
  int led_no[3] = {rPin, gPin, bPin};
  double metric;
  double V0 = 4.35;
  double Vi0[3] = {3.18,2.00,2.26};      // Experimental Observations
  double ab_coeff[3] = {1,1,1};
  double len = 0.01; //10mm
  double Abs;

  while(i<3)
  {
    int sensorValue;
    analogWrite(led_no[i],90);
    delay(1000);
    sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    
    delay(2000);
    double V_LDR = mapper(sensorValue, 0, 1023, 0, 5);
    Serial.println(V_LDR);
    Abs = -log10((V0-V_LDR)/(5-V_LDR)) - log10((5-Vi0[i])/(V0-Vi0[i]));
    Serial.println(Abs);
    //npk[i] = abs(Abs/(ab_coeff[i]*len));
    npk[i] = V_LDR; //To find thresholds
    analogWrite(led_no[i],0);
    i = i + 1;
    delay(2000);
  }
  //6. Transmit value
  //Data to be stored in npk[3] or change it as needed
  Serial.print(npk[0]);
  Serial.print("\t");
  Serial.print(npk[1]);
  Serial.print("\t");
  Serial.print(npk[2]);
  Serial.print("\n");
  Serial.println("Transmitting data");
  delay(500);
  digitalWrite(intr, HIGH);
  //Send serial data
  Serial1.print(String(npk[0]) + "," + String(npk[1]) + "," + String(npk[2]) + "|");
  delay(1000);
  //End transmission to prevent data mismatch
  digitalWrite(intr, LOW);

  //7. Clean
  Serial.println("Cleaning");
  delay(4000);
  for(int j = 60;j<=175;j+=1 )
  {base_servo.write(j);
  delay(10);}
  delay(5000);
  digitalWrite(vibPin, HIGH);
  digitalWrite(cleanPin, LOW);
  delay(4000);
  //Cleaning done
  digitalWrite(vibPin,LOW);
  digitalWrite(cleanPin, HIGH);
  delay(5000);
  for(int j =175;j>=60;j-=1)
  {base_servo.write(j);
  delay(10);}
  Serial.println("Getting ready for next sample");
  delay(6000); 
}

//Function to fill water-call only once
void fillWater()
{
   pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  
  while(totalMilliLitres<60){
    digitalWrite(fillPin,LOW);
   if((millis() - oldTime) > 30)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
        
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((30.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min");
    // Print the number of litres flowed in this second
    Serial.print("  Current Liquid Flowing: ");             // Output separator
    Serial.print(flowMilliLitres);
    Serial.print("mL/Sec");

    // Print the cumulative total of litres flowed since starting
    Serial.print("  Output Liquid Quantity: ");             // Output separator
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    
  }
}
digitalWrite(fillPin,HIGH);
}

/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}

double mapper(double val, double in_min, double in_max, double out_min, double out_max)
{
  return (val-in_min)*(out_max-out_min)/(in_max-in_min) + out_min;
}

