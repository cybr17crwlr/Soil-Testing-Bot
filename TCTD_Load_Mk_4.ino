////TCTD - Load - IIT Guwahati
////NPK Detection Module
//
////Include libraries
#include <ESP8266WiFi.h>
//
////Define GPIO pins
//#define inPin     16//Input Interrupt Pin
//
////Network credentials
//const char* ssid     = "duncan";
//const char* password = "11111111";
//
////Web server port number
//WiFiServer server(80);
//
////Variable to store HTTP request
//String header;
//
////Input values
//bool inIntr = 0;
////float flowIn = 0;
//
////Servo object
//
////Variables
//String currState = "";
//int nutrient[3] = {0,0,0};
//String input = "";
//
////Functions
//void IntCallback();
//int process(int data, int color);
//
void setup() {}
void loop() {}
//{
//  //Start serial
//  Serial.begin(115200);
//  //Set servo pin
//  //Connect to WiFi
//  //Serial.print("Connecting to : ");
//  Serial.println(ssid);
//  WiFi.begin(ssid,password);
//  while(WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");
//  }
//  //Print local IP for connection
//  Serial.print("\n");
//  Serial.println("WiFi connected");
//  Serial.print("IP address : ");
//  Serial.println(WiFi.localIP());
//  //Start server
//  server.begin();
//  //Set control pins
//  pinMode(inPin, INPUT);
//  //Set Interrupt Pin
//  //attachInterrupt(digitalPinToInterrupt(flowPin), IntCallback, RISING);
//}
//String tr = "";
//String N = "";
//String P = "";
//String K = "";
//
//void loop()
//{
//  //Client connection
//  WiFiClient client = server.available(); //Listen for incoming clients
//  inIntr = digitalRead(inPin);
//  if (inIntr)
//  {
////    input = Serial.readStringUntil('|');
////    tr = input.substring(0,2);
////    nutrient[0] = input.substring(0,3);
////    nutrient[1] = input.substring(4,7);
////    nutrient[2] = input.substring(8,10);
//      N = Serial.readStringUntil(',');
//      P = Serial.readStringUntil(',');
//      K = Serial.readStringUntil('|');
//    //delay(500);
//  }
//  if (client)                             //Start if a new client connects
//  {
//    Serial.println("New Client");         //Client connected
//    if(client.connected())                //Run only when client is connected
//    {    
//      currState = "Input";
//      //Display HTML
//      client.println("HTTP/1.1 200 OK");
//      client.println("Content-type:text/html");
//      client.println("Connection: close");
//      client.println();
//      //HTML WebPage
//      client.println("<!DOCTYPE html><html>");
//      client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//      client.println("<link rel=\"icon\" href=\"data:,\">");
//      
//      client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//      client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//      client.println("</style></head>");
//      // Web Page Heading
//      client.println("<body><h1>TCTD - IIT GUWAHATI</h1>");
//    
//      //Display Current State
//      client.println("<p>Current State :  " + currState + "</p>");
//    
//      //Display values and recommendations
////      client.println("<p>N : " + String(nutrient[0]) + "</p>");
////      client.println("<p>P : " + String(nutrient[1]) + "</p>");
////      client.println("<p>K : " + String(nutrient[2]) + "</p>");
//      client.println("<p>N : " + N + "</p>");
//      client.println("<p>P : " + P + "</p>");
//      client.println("<p>K : " + K + "</p>");
////      client.println("<p>Input : " + input + "</p>");
////      client.println("<p>Try : " + tr + "</p>");
//      
//      client.println("</body></html>");
//      client.println();
//    }
//  }
//
//}
//
////Interrupt function
//void IntCallback(){
//  Serial.print("Stamp(ms): ");
//  Serial.println(millis());
//}
//
////Function to process given data
//int process(int data, int color)
//{
//  return 0;
//}
//
//
//
