//imports for transmitter 
#include <RH_ASK.h>
#include <SPI.h> 

// defines pins numbers
const int trigPin = 10;
const int echoPin = 11;
int ledPin = 13;
RH_ASK driver(2000, 2, 4, 5); // speed, receivePin, transmitPin, push-to-talk

// defines variables
long duration;
int distanceCm, distanceInch;
void setup()
{
  pinMode(ledPin, OUTPUT); // ard led 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);       // Starts the serial communication
  if (!driver.init())
         Serial.println("init failed");
}
void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distanceCm= duration*0.034/2;
  distanceInch = duration*0.0133/2;


  // will run until tranmission finishes sending
  digitalWrite(ledPin, HIGH);

  const char * msg = distanceCm;
  
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  
//  // Prints the distance on the Serial Monitor
//  Serial.print("DistanceCM: ");
//  Serial.println(distanceCm);

  //transmission finished
  digitalWrite(ledPin, LOW);

  delay(1000);
//  LowPower.deepSleep(1000);
}
