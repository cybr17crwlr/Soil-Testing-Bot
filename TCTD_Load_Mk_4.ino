//TCTD - Load - IIT Guwahati
//NPK Detection Module

//Include libraries
#include <ESP8266WiFi.h>

//Define GPIO pins
#define inPin     16//Input Interrupt Pin - D0

//Network credentials
const char* ssid     = "duncan";
const char* password = "11111111";

//Web server port number
WiFiServer server(80);

//Variable to store HTTP request
String header;

//Input values
bool inIntr = 0;
bool done = 0;
//Variables
String currState = "";
String N = "";
String P = "";
String K = "";

void setup()
{
  //Start serial
  Serial.begin(115200);
  //Connect to WiFi
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  //Print local IP for connection
  Serial.print("\n");
  Serial.println("WiFi connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
  //Check the Serial Monitor for IP
  //Start server
  server.begin();
  //Set interrupt(level triggered) pins
  pinMode(inPin, INPUT);
}

void loop()
{
  currState = "Waiting";
  //Client connection
  WiFiClient client = server.available(); //Listen for incoming clients
  inIntr = 0;
  done = 0;
  inIntr = digitalRead(inPin);
  if (inIntr && Serial.available())
  {
      done = 1;
      currState = "Analysing";
      N = Serial.readStringUntil(',');
      P = Serial.readStringUntil(',');
      K = Serial.readStringUntil('|');
      Serial.print(N);
      Serial.print("\t");
      Serial.println(P);
      Serial.print("\t");
      Serial.println(K);
      delay(1000);
  }
  Serial.println(currState);
  if (client)                             //Start if a new client connects
  {
    Serial.println("New Client");         //Client connected
    if(client.connected())                //Run only when client is connected
    {    
      //Display HTML
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println("Connection: close");
      client.println();
      //HTML WebPage
      client.println("<!DOCTYPE html><html>");
      client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
      client.println("<link rel=\"icon\" href=\"data:,\">");
      
      client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
      client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
      client.println("</style></head>");
      // Web Page Heading
      client.println("<body><h1>TCTD - IIT GUWAHATI</h1>");
    
      //Display Current State
      client.println("<p>Current State :  " + currState + "</p>");

      //Display values
      client.println("<p>N : " + N + "</p>");
      client.println("<p>P : " + P + "</p>");
      client.println("<p>K : " + K + "</p>");
      
      client.println("</body></html>");
      client.println();
      
    }
  }
  if (done == 1){ delay(5000);}
}
