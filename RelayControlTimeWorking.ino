#include <RTClib.h>

RTC_DS3231 rtc;

const int RELAY_1 = 41;
const int RELAY_2 = 39;
const unsigned long RELAY_1_TIME_1 = 60; //  1 minutes in seconds
const unsigned long RELAY_1_TIME_2 = 120; // 2 minutes in seconds
const unsigned long RELAY_1_TIME_3 = 180; // 3 minutes in seconds

int State_1 = 0;
int State_2 = 0;

const unsigned long RELAY_2_TIME_1 = 60; //  1 minutes in seconds
const unsigned long RELAY_2_TIME_2 = 120; // 2 minutes in seconds
const unsigned long RELAY_2_TIME_3 = 180; // 3 minutes in seconds

unsigned long lastRelay1OnTime = 0;
unsigned long lastRelay2OnTime = 0;
bool relay1CountdownInProgress = false;
bool relay2CountdownInProgress = false;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_1, OUTPUT);
  digitalWrite(RELAY_1, LOW); // turn off relay 1

  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_2, LOW); // turn off relay 2

  rtc.begin();
}

void loop() {
   if (Serial.available()) {
    // Read the incoming data from the Bluetooth module
    char incomingData = Serial.read();
    
    // If the incoming data is '1', turn on relay 1
    if (incomingData == '1' && !relay1CountdownInProgress && State_1 == 0) {
      digitalWrite(RELAY_1, HIGH);
      lastRelay1OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 1 turned on");
      State_1 = 1;
    }
    // If the incoming data is '2', turn on relay 1
    else if (incomingData == '2' && !relay1CountdownInProgress && State_1 == 0) {
      digitalWrite(RELAY_1, HIGH);
      lastRelay1OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 1 turned on");
      State_1 = 2;
    }
    // If the incoming data is '3', turn on relay 1
    else if (incomingData == '3' && !relay1CountdownInProgress && State_1 == 0) {
      digitalWrite(RELAY_1, HIGH);
      lastRelay1OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 2 turned on");
      State_1 = 3;
    }
    // If the incoming data is '4', turn on relay 2
    else if (incomingData == '4' && !relay2CountdownInProgress && State_2 == 0) {
      digitalWrite(RELAY_2, HIGH);
      lastRelay2OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 2 turned on");
      State_2 = 1;
    }
    // If the incoming data is '5', turn on relay 2
    else if (incomingData == '5' && !relay2CountdownInProgress && State_2 == 0) {
      digitalWrite(RELAY_2, HIGH);
      lastRelay2OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 2 turned on");
      State_2 = 2;
    }
    // If the incoming data is '6', turn on relay 2
    else if (incomingData == '6' && !relay2CountdownInProgress && State_2 == 0) {
      digitalWrite(RELAY_2, HIGH);
      lastRelay2OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 2 turned on");
      State_2 = 3;
    }
  }
  DateTime now = rtc.now();
  if(digitalRead(RELAY_1) == HIGH){
    unsigned long elapsedSeconds = now.unixtime() - lastRelay1OnTime; // calculate the elapsed time since the relay was turned on
    if (elapsedSeconds >= RELAY_1_TIME_1 && State_1 == 1) {
      digitalWrite(RELAY_1, LOW); // turn off relay 1
      Serial.println("Relay 1 turned OFF");
      State_1 = 0;
    }
    else if(elapsedSeconds >= RELAY_1_TIME_2 && State_1 == 2) {
      digitalWrite(RELAY_1, LOW); // turn off relay 1
      Serial.println("Relay 1 turned OFF");
      State_1 = 0;
    }
    else if(elapsedSeconds >= RELAY_1_TIME_3 && State_1 == 3) {
      digitalWrite(RELAY_1, LOW); // turn off relay 1
      Serial.println("Relay 1 turned OFF");
      State_1 = 0;
    }
    else {
      if(State_1 == 1 ){
        unsigned long remainingSeconds_1 = RELAY_1_TIME_1- elapsedSeconds; // calculate the remaining time
        Serial.print("Time remaining for Relay 1: ");
        Serial.print(remainingSeconds_1);
        Serial.println(" seconds");
      }else if(State_1 == 2 ){
        unsigned long remainingSeconds_1 = RELAY_1_TIME_2- elapsedSeconds; // calculate the remaining time
        Serial.print("Time remaining for Relay 1: ");
        Serial.print(remainingSeconds_1);
        Serial.println(" seconds");
      }else if(State_1 == 3 ){
        unsigned long remainingSeconds_1 = RELAY_1_TIME_3- elapsedSeconds; // calculate the remaining time
        Serial.print("Time remaining for Relay 1: ");
        Serial.print(remainingSeconds_1);
        Serial.println(" seconds");
      }
      
    }
  }
  if(digitalRead(RELAY_2) == HIGH){
    unsigned long elapsedSeconds = now.unixtime() - lastRelay2OnTime; // calculate the elapsed time since the relay was turned on
    if (elapsedSeconds >= RELAY_2_TIME_1 && State_2 == 1) {
      digitalWrite(RELAY_2, LOW); // turn off relay 2
      Serial.println("Relay 2 turned OFF");
      State_2 = 0;
    }
    else if(elapsedSeconds >= RELAY_2_TIME_2 && State_2 == 2) {
      digitalWrite(RELAY_2, LOW); // turn off relay 2
      Serial.println("Relay 2 turned OFF");
      State_2 = 0;
    }
    else if(elapsedSeconds >= RELAY_2_TIME_3 && State_2 == 3) {
      digitalWrite(RELAY_2, LOW); // turn off relay 2
      Serial.println("Relay 2 turned OFF");
      State_2 = 0;
    }
    else {
      if(State_2 == 1){
        unsigned long remainingSeconds = RELAY_2_TIME_1 - elapsedSeconds; // calculate the remaining time
        Serial.print("Time remaining for Relay 2: ");
        Serial.print(remainingSeconds);
        Serial.println(" seconds");
      }else if(State_2 == 2){
        unsigned long remainingSeconds = RELAY_2_TIME_2 - elapsedSeconds; // calculate the remaining time
        Serial.print("Time remaining for Relay 2: ");
        Serial.print(remainingSeconds);
        Serial.println(" seconds");
      }else if(State_2 == 3){
        unsigned long remainingSeconds = RELAY_2_TIME_3 - elapsedSeconds; // calculate the remaining time
        Serial.print("Time remaining for Relay 2: ");
        Serial.print(remainingSeconds);
        Serial.println(" seconds");
      }
      
    }
  }
  delay(1000);
}
