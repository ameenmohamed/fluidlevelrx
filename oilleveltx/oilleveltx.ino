//imports for transmitter 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// defines pins numbers
const int trigPin = 3;
const int echoPin = 2;
RF24 radio(7, 8); // CE, CSN

// defines variables
long duration;
int distanceCm, distanceInch;
const byte address[6] = "00001";
char text[32];

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);       // Starts the serial communication
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
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
  
 //const char text[] = "Hello World";  
  //String distStr = String(distanceCm);
  itoa(distanceCm, text, 10);
  Serial.println(distanceCm);
 //radio.write(&text, sizeof(text));
 radio.write(&text, sizeof(text));
//  // Prints the distance on the Serial Monitor
//  Serial.print("DistanceCM: ");
//  Serial.println(distanceCm);

  //transmission finished

  delay(1000);
//  LowPower.deepSleep(1000);
}
