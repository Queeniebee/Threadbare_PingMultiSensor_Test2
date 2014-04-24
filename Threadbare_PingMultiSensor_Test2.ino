#include <NewPing.h>

// For HC-SR04
#define TRIGGER_PIN  12 
#define ECHO_PIN     11

// For Parallax Ping))
#define SIG_PIN      13

// For Both
#define MAX_DISTANCE 500 //in cm
#define PING_INTERVAL 5  //not sure if it should be in micro or milliseconds, this is millis
#define NUM_SENSORS  2

unsigned long pingTimes[NUM_SENSORS];         // Holds the times when the next ping should happen for each sensor.
unsigned int distanceStore[NUM_SENSORS];      // Where the ping distances are stored.
int currentSensor = 0;                        // Keeps track of which sensor is active.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//Need to figure how to interface with the NewPing library and the Parallax sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  delay(29);     // Wait 29ms between pings. 29ms should be the shortest delay between pings.
//  delayMicroseconds(29);     // have this line as an experiment 
  unsigned int uS1 = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("HC1: ");
  Serial.print(uS1 / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
  // for Parallax Ping)))
  long duration, cm;

  pinMode(SIG_PIN, OUTPUT);
  digitalWrite(SIG_PIN, LOW);
  
  // Version One has this line in 2microseconds: delayMicroseconds(2);
  delay(29);
  digitalWrite(SIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(SIG_PIN, LOW);
  pinMode(SIG_PIN, INPUT);
  
  duration = pulseIn(SIG_PIN, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.print("Parallax: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
 
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

