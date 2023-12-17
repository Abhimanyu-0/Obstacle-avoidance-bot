include <Servo.h>

//Defined servo objects 
Servo rservo;
Servo lservo;

//setting pins int RpingPin = 6;
const int RpingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int RechoPin = 7;

const int LpingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int LechoPin = 10; 


int IRSensorRight = 3; 
int IRSensorLeft = 5;

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
  long Rduration, Rinches, Rcm, Lcm, Lduration, Linches;
  float i =0;


   pinMode(RpingPin, OUTPUT);
   digitalWrite(RpingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(RpingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(RpingPin, LOW);
   pinMode(RechoPin, INPUT);
   Rduration = pulseIn(RechoPin, HIGH);
   //Rinches = microsecondsToInches(Rduration);
   Rcm = centi(Rduration);
   //Serial.print(Rinches);
   //Serial.print("in, ");
   //Serial.print(Rcm);
   //Serial.print("cm");
   //Serial.println();
   delay(100);

   pinMode(LpingPin, OUTPUT);
   digitalWrite(LpingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(LpingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(LpingPin, LOW);
   pinMode(LechoPin, INPUT);
   Lduration = pulseIn(LechoPin, HIGH);
   //Linches = microsecondsToInches(Lduration);
   Lcm = centi(Lduration);
   //Serial.print(Linches);
   //Serial.print("in, ");
   //Serial.print(Lcm);
   //Serial.print("cm");
   //Serial.println();
   delay(100);

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.

  // convert the time into a distance
 

  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print( Lcm);
  Serial.print("Lcm ");
  Serial.print(Rcm);
  Serial.print("Rcm");
  Serial.println();
  Serial.println();
  delay(500);

  int Rstatus = digitalRead(IRSensorRight); 
  int Lstatus = digitalRead(IRSensorLeft);


  

  if (Rcm>=16 && Lcm>=16)
  {
  moveForward(); 

  }
  else if (Lcm<12 && Lcm<12)
  {
  stop();
  }
  else if (Lcm<=15)
  {
  moveRight();
  moveaBIT();
  moveLeft();
  }
  else if (Rcm<=15)
  {
  moveLeft();
  moveaBIT();
  moveRight();
  }

  if (Rstatus==LOW)
  {
  stop();
  moveBackwardRight();
   
  }

  if (Lstatus==LOW){
  stop();
  moveBackwardLeft();
    
  }
  
 // else if (Serial.available()){
   // if (signal == 'S')
    
    //{for(i =0;i<10;i++){
     // rservo.detach();
      //lservo.detach();
      //Serial.println();
      //Serial.print(signal);
      
    //}}
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
  
  float i = 0;
  rservo.attach(9);
  lservo.attach(11);
  for(i=0;i<=3;i++){
  rservo.write(0);
  lservo.write(180-i);}
  }
 


//Employed to move teh bot to the right 
void moveRight(){
  rservo.attach(9);
  lservo.attach(11);
  float i=0;
  for (i=0;i<=1;i++)
  {
  lservo.write(180);
  rservo.write(85);
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
  for (i=0;i<=0.60;i=i+0.75)
  {
  rservo.write(0);
  //Serial.println(i);
  delay(500);
  //Function stops after i=2
  if (i==1){
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
  for (i=0;i<=7;i++)
  {rservo.write(i);
  lservo.write(180-i);}
  //Serial.println(i);
  delay(500);
  if (i==6)
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
  //Serial.println(i);
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


  





