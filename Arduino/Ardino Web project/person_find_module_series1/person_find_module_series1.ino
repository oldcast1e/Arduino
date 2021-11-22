// Includes the Servo library
#include <Servo.h>. 
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 2;
const int echoPin = 3;
// Variables for the duration and the distance
long duration;
int distance;

Servo myServo; // Creates a servo object for controlling the servo motor

void calculateDistance(){ 
  
   digitalWrite(trigPin,LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin,LOW);
   
   long D = pulseIn(echoPin,HIGH);
   
   long d = (D/2)/29.1;
  
   delay(10);
   Serial.print(d);
   Serial.println("cm");
}

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(7); // Defines on which pin is the servo motor attached

  myServo.write(0);
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
//  calculateDistance();
  
  for(int i=0;i<=179;i++){  
      myServo.write(i);
      delay(10);
      calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

  }
  // Repeats the previous lines from 165 to 15 degrees
  delay(10);
  
  for(int i=179;i>=0;i--){  
      myServo.write(i);
      delay(10);
      calculateDistance();
      
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
