#include <HCSR04.h>
#include <ArduinoLowPower.h>
#include <SigFox.h>

#include "conversions.h"

// Set oneshot to false to trigger continuous mode when you finish setting up the whole flow
int oneshot = true;

const int trigPin = 7;
const int echoPin = 8;

long duration;
int distance;


typedef struct __attribute__ ((packed)) sigfox_message {
  uint8_t status;
  int16_t data1;
  uint8_t lastMessageStatus;
} SigfoxMessage;

// stub for message which will be sent
SigfoxMessage msg;

void setup() {

  if (oneshot == true) {
    // Wait for the serial
    Serial.begin(115200);
    while (!Serial) {}
  }

  if (!SigFox.begin()) {
    // Something is really wrong, try rebooting
    // Reboot is useful if we are powering the board using an unreliable power source
    // (eg. solar panels or other energy harvesting methods)
    reboot();
  }

  //Send module to standby until we need to send a message
  SigFox.end();

  if (oneshot == true) {
    // Enable debug prints and LED indication if we are testing
    SigFox.debug();
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
 
}

void loop() {
  // Every 15 minutes, read all the sensors and send them
  // Let's try to optimize the data format
  // Only use floats as intermediate representaion, don't send them directly
  
  //Water level measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  if(duration == 0){
        Serial.println("Warning : No pulse from the sensor");
        return;
    }
    
  distance = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  // set value
  if(distance < 10000)
  {
    msg.data1 = convertoFloatToUInt16(distance, 2000);
    Serial.println(distance);
  }

  
  // Start the module
  SigFox.begin();
  // Wait at least 30ms after first configuration (100ms before)
  delay(100);

  // Clears all pending interrupts
  SigFox.status();
  delay(1);

  SigFox.beginPacket();
  SigFox.write((uint8_t*)&msg, 12);

  msg.lastMessageStatus = SigFox.endPacket();

  if (oneshot == true) {
    Serial.println("Status: " + String(msg.lastMessageStatus));
  }

  SigFox.end();

  if (oneshot == true) {
    // spin forever, so we can test that the backend is behaving correctly
    while (1) {}
  }

  //Sleep for 15 minutes
  LowPower.sleep(15 * 60 * 1000);
}

void reboot() {
  NVIC_SystemReset();
  while (1);
}
