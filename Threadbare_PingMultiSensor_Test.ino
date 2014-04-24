#include <NewPing.h>

// For HC-SR04
#define TRIGGER_PIN  12 
#define ECHO_PIN     11

// For Parallax Ping))
#define SIG_PIN      13
// For Both
#define MAX_DISTANCE 500 //in cm
#define PING_INTERVAL 5//not sure if it should be in micro or milliseconds, this is millis
#define NUM_SENSORS  2

unsigned long pingTimes[NUM_SENSORS];           // Holds the times when the next ping should happen for each sensor.
unsigned int distanceStore[NUM_SENSORS];        // Where the ping distances are stored.
int currentSensor = 0;                          // Keeps track of which sensor is active.

//NewPing sonar[NUM_SENSORS] = {     // Sensor object array.
//  NewPing(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
//  NewPing(SIG_PIN, MAX_DISTANCE)
//  };

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//NewPing sonar2(SIG_PIN, MAX_DISTANCE);


void setup() {
  Serial.begin(9600);

//  pingTimes[0] = millis() + 10;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
//
//  pingTimes[0] = pingTimes[0] + PING_INTERVAL; // Set the starting time for each sensor.
//  pingTimes[1] = pingTimes[1] + PING_INTERVAL;

  //    for (int i = 1; i < NUM_SENSORS; i++){   
  //      pingTimes[i] = pingTimes[i - 1] + PING_INTERVAL;
  //    }
}

void loop() {
  
  delay(29);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS1 = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("HC1: ");
  Serial.print(uS1 / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
  // for Parallax Ping)))
  long duration, cm;

  pinMode(SIG_PIN, OUTPUT);
  digitalWrite(SIG_PIN, LOW);
  delayMicroseconds(2);
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
  
 /* unsigned int uS2 = sonar2.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping2: ");
  Serial.print(uS2 / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");*/
  
  /*
  for (int i = 0; i < NUM_SENSORS; i++) { // Loop through all the sensors.
    if (millis() >= pingTimes[i]) {         // Is it this sensor's time to ping?
      pingTimes[i] += PING_INTERVAL * NUM_SENSORS;  // Set next time this sensor will be pinged.
      // original code has (NUM_SENSORS - 1) but since this is only two sensors I am just doing 1
      if ((i == 0) && (currentSensor == 1)) { 
        // Sensor ping cycle complete, so printing the results.
        oneSensorCycle();
        sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
        currentSensor = i;                          // Sensor being accessed.
        distanceStore[currentSensor] = 0;           // Make distance zero in case there's no ping echo for this sensor.
        sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
      }
    }
  } */
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
/*
// If ping received, set the sensor distance to array.
void echoCheck() { 
  if (sonar[currentSensor].check_timer())
    distanceStore[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

// Sensor ping cycle complete, so printing the results.
void oneSensorCycle() {    
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(distanceStore[i]);
    Serial.print("cm");
  }
  Serial.println();
}
*/






