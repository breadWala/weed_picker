#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>


#include <ESP32Servo.h>
const char* ssid="koootida";
const char* password="12345678";
//hole side motors
int in1=23;
int in2=22;
int in4=19;
int in3=18;
int en1=21;
int en2=5;



Servo myServo;
Servo myServo2;
const int OPEN_ANGLE = 25;
const int CLOSE_ANGLE = 115;

bool servo_open=false;
bool forward_yes=false;
 WebServer server(80);

//control functions
void forward()
{
   //move forward 
   //holeside
   digitalWrite(in1,LOW);
   digitalWrite(in2,HIGH);

   //wholeside
   digitalWrite(in3,HIGH);
   digitalWrite(in4,LOW);


}
void backward()
{

   
   //holeside
   digitalWrite(in1,HIGH);
   digitalWrite(in2,LOW);

   //wholeside
   digitalWrite(in3,LOW);
   digitalWrite(in4,HIGH);


}
void right()
{
   
   //holeside
   digitalWrite(in1,HIGH);
   digitalWrite(in2,LOW);

   //wholeside
   digitalWrite(in3,LOW);
   digitalWrite(in4,LOW);

}
void left()
{
   
   //holeside
   digitalWrite(in1,LOW);
   digitalWrite(in2,LOW);

   //wholeside
   digitalWrite(in3,LOW);
   digitalWrite(in4,HIGH);
}
void stop()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  

  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}



















void toggleServos()
{
  servo_open=!servo_open;
  if (servo_open)
  {
  myServo2.write(50);
  delay(2000);

  myServo.write(40);
  delay(3000);
  
  myServo.write(90);
  delay(2000);

  for(int angle=50;angle<=300;angle++)
      {
        myServo2.write(angle);
        delay(10);
      }
   
   delay(200);

  myServo.write(40);
  delay(2000);

  for(int angle=270;angle>=50;angle--)
      {
        myServo2.write(angle);
        delay(10);
      }
   
   delay(2000);
  }
  else 
  {
    myServo2.write(80);
  }
}
void handleRoot()
{
  
  server.send(200,"text/html",
  R"rawliteral(
    <!DOCTYPE html>
    <html>
    <body>
    <h1>gripper Control</h1>
    <input 
    type="range"
    min="40"
    max="120"
    value="40"
    oninput="moveServo1(this.value)">


    <h2> vertical axis controller </h2>
    <input 
    type="range"
    min="50"
    max="200"
    value="70"
    oninput="moveServo2(this.value)">
    <h3>forward</h3>
    <button onclick="fetch('/forward')">Forward</button>
    <button onclick="fetch('/stop')">STOP</button>
     <button onclick="fetch('/back')">reverse</button>
      <button onclick="fetch('/left')">left</button>
       <button onclick="fetch('/right')">right</button>
    <script>
    function moveServo1(angle)
    {
      fetch("/servo?angle=" + angle);
    }
    function moveServo2(angle)
    {
      fetch("/servo2?angle2=" +angle);
    }
    </script>
    </body>
    </html>
      )rawliteral");
}
//pivot servo
void handleServo()
{ 
  if(!server.hasArg("angle"))
  {
    server.send(400,"/text/plain","Missing angle");
    return;
  }
  
    int angle=server.arg("angle").toInt();
    
    
    myServo.write(angle);
  
    server.send(200,"text/plain","ok");
  }
  void handleServo2()
  {
    if (!server.hasArg("angle2"))
    {
      server.send(400,"/text/plain","missing angle");
      return;
    }
    int angle=server.arg("angle2").toInt();
    myServo2.write(angle);
    server.send(200,"text/plain","ok");
  }


  void handletoggle()
  {
    toggleServos();
    server.send(200,"text/plain","done");
  }
void setup() {
  Serial.begin(115200);
 
  server.on("/",handleRoot);
  server.on("/toggle",handletoggle);
  server.on("/servo",handleServo);
  server.on("/servo2",handleServo2);
  server.on("/forward",forward);
  server.on("/back",backward);
  server.on("/right",right);
  server.on("/left",left);

  server.on("/stop",stop);
   if(WiFi.softAP(ssid,password))
   {
    Serial.println("wifi started ");
   }
   else 
   {
    Serial.println("nope not online ");
   }
  server.begin();
  WiFi.softAP(ssid,password);
  myServo.setPeriodHertz(50);   // Standard servo frequency
  myServo.attach(14, 500  ,2500 );
  myServo2.attach(12,500,2600);
  myServo2.write(90);
  myServo.write(90);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);

  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  
  


  
  


  Serial.println("Servo Test");
}

//pivot servo
void loop() {
  

server.handleClient();

  






}