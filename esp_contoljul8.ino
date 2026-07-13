#include <ESP32Servo.h>


HardwareSerial MoveSerial(2);
//hole side motors
int in1=23;
int in2=22;
int in4=19;
int in3=18;
int en1=21;
int en2=5;
unsigned long lastCommandTime=0;



Servo myServo;
Servo myServo2;
const int OPEN_ANGLE = 25;
const int CLOSE_ANGLE = 115;

bool servo_open=false;
bool forward_yes=false;

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













void setup() {
  // put your setup code here, to run once:
   MoveSerial.begin(115200,SERIAL_8N1,16,17);
   Serial.begin(115200);
   pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);

pinMode(en1,OUTPUT);
pinMode(en2,OUTPUT);

digitalWrite(en1,HIGH);
digitalWrite(en2,HIGH);

myServo.attach(14,500,2500);
myServo2.attach(12,500,2600);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (MoveSerial.available())
   {
    String msg=MoveSerial.readStringUntil('\n');
    Serial.println(msg);
    lastCommandTime=millis();
    if(msg.length() == 0)
    return;
    switch(msg[0])
    {
      case 'F':
        forward();
        break;

    case 'S':
        stop();
        break;

    case 'L':
        left();
        break;

    case 'R':
        right();
        break;

    case 'Z':
        backward();
        break;

    case 'G':
    {
        int angle = msg.substring(2).toInt();
        myServo.write(angle);
        break;
    }

    case 'V':
    {
        int angle = msg.substring(2).toInt();
        myServo2.write(angle);
        break;

    }
    
    

   }
    

   }
   
}
