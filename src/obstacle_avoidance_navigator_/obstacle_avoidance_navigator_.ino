#include <Servo.h>

//Defined servo objects 
Servo rservo;
Servo lservo;

//setting pins 
int pingPin = 7;
int IRSensorRight = 3; 
int IRSensorLeft = 4;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  //attaching servos to pin 9 and 11
  rservo.attach(9);
  lservo.attach(11);
  pinMode(IRSensorRight, INPUT); 
  pinMode(IRSensorLeft, INPUT);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;
  float i =0;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = centi(duration);

  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  int Rstatus = digitalRead(IRSensorRight); 
  int Lstatus = digitalRead(IRSensorLeft);

  // If distance of the object/obstacle is more than 16 cm, then the bot will move ahead
  if (cm>=16)
  {
  moveForward(); 
  }
  // If the distance of the object/obstacle is less than 10 cm, the bot will stop and detach the servos
  else if (cm<10)
  {
  stop();
  }
  // If the distance of the obstacle/object is less than 15 cm, then the bot will adjust its path by going to the right first (arbitrary choice)
  else if (cm<=15)
  {
  moveRight();
  moveaBIT();
  moveLeft();
  }

  // If the right IR sensor detects white lane, the robot will go backwards 
  if (Rstatus==LOW)
  {
   stop();
   moveBackwardRight();
  }
 //If the left IR sensor detects white line, the robot will go backward and left 
  if (Lstatus==LOW){
    stop();
    moveBackwardLeft();
  }


// Func definitions from here 

long centi(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

// Employed to make the bot move forward endlessly
void moveForward(){
  rservo.attach(9);
  lservo.attach(11);
  float i=0;
  for (i=0;i<=3;i++)
  {rservo.write(0);
  lservo.write(180-i);}
}

//Employed to move teh bot to the right 
void moveRight(){
  rservo.detach();
  lservo.attach(11);
  float i=0;
  for (i=0;i<=1;i++)
  {
  lservo.write(180);
  Serial.println(i);
  delay(500);
  // When i=1, the function stops executing
  if (i==1){
  lservo.detach();
  }
  }
}

//Employed to move the boebot to the left 
void moveLeft(){
  lservo.detach();
  rservo.attach(9);
  float i=0;
  for (i=0;i<=2;i++)
  {
  rservo.write(0);
  //Serial.println(i);
  delay(500);
  //Function stops after i=2
  if (i==2){
  rservo.detach();}
  }
}

//Disconnects the servos
void stop(){
  rservo.detach();
  lservo.detach();  
}

//Moves the bot until i=4 unlike moveForward function that is endless 
void moveaBIT(){
  rservo.attach(9);
  lservo.attach(11);

  float i=0;
  for (i=0;i<=4;i++)
  {rservo.write(i);
  lservo.write(180-i);}
  Serial.println(i);
  delay(500);
  if (i==4)
  {
  rservo.detach();
  lservo.detach();
  }
}

// This makes the bot move backwards and right, employed when a (right)lane is encounted by the IR sensor(right)
void moveBackwardRight(){
  rservo.detach();
  lservo.attach(11);
  float i=0;
  for (i=0;i<=2;i++){
  lservo.write(0);
  Serial.println(i);
  delay(500);
  if (i==2)
  {
  lservo.detach();
  }
}
}

//This function makes the bot move backwards and to the left, employed when a (left)lane is encountered by the IR sensor(left)
void moveBackwardLeft(){
  lservo.detach();
  rservo.attach(9);
  float i=0;
  for (i=0;i<=2;i++)
  {
  rservo.write(180);
  //Serial.println(i);
  delay(500);
  if (i==2){
  rservo.detach();}
  }
}


  




