#include <MeMCore.h>
MeUltrasonicSensor ultraSensor(PORT_4);
MeLineFollower lineFinder(PORT_2);
MeDCMotor leftMotor(M1);
MeDCMotor rightMotor(M2);
MeBuzzer buzzer;
const int sensorPin = A3;
const int IRPin = A2;
#define SAFE_DISTANCE 10
#define IR_DETECT_THRESHOLD 170
unsigned long lastTurnTime = 0;
unsigned long turnInterval = 0;

void setup() {
    Serial.begin(115200);
    randomSeed(analogRead(0));
    lastTurnTime = millis();
    turnInterval = random(3000, 5000);
}

void loop() {
    int sensorState = lineFinder.readSensors();
    int distance = ultraSensor.distanceCm();
    int sensorValue = analogRead(sensorPin);

    killBot();

    if(sensorValue > 20) {
        buzzer.tone(1000, 100);
    } else {
        buzzer.noTone();
    }
    if (distance > 0 && distance < SAFE_DISTANCE) {
        avoidObstacle();
        lastTurnTime = millis();
        turnInterval = random(3000, 5000);
        return;
    }
    switch (sensorState) {
        case S1_IN_S2_OUT: 
            moveBack();      
            turnRight();
            break;
        case S1_OUT_S2_IN: 
            moveBack();
            turnLeft();
            break;
        case S1_OUT_S2_OUT:
            moveForward();
            break;
        case S1_IN_S2_IN:
            avoidLine();
            break;
    }
}

void moveForward() {
    leftMotor.run(-100);
    rightMotor.run(100);
}

void stop() {
    leftMotor.run(0);
    rightMotor.run(0);
}

void turnLeft() {
    int turnAngle = random(90, 180);
    leftMotor.run(100);
    rightMotor.run(100);

    unsigned long turnStartTime = millis();
    unsigned long turnTime = map(turnAngle, 0, 180, 500, 1500);

    while (millis() - turnStartTime < turnTime) {
        killBot();}
}

void turnRight() {
    int turnAngle = random(90, 180);
    leftMotor.run(-100);
    rightMotor.run(-100);
    unsigned long turnStartTime = millis();
    unsigned long turnTime = map(turnAngle, 0, 180, 500, 1500);

    while (millis() - turnStartTime < turnTime) {
        killBot();
    }
}

void avoidLine() {
    int turnDirection = random(0, 2);

    if (turnDirection == 0) {
        turnLeft();
    } else {
        turnRight();
    }
}

void avoidObstacle() {
    stop();
    leftMotor.run(100);
    rightMotor.run(-100);
    unsigned long turnStartTime = millis();
    while (millis() - turnStartTime < 400) {
        killBot();
    }
    if (random(0, 2) == 0) {
        turnLeft();
    } else {
        turnRight();
    }
    moveForward();
}

void killBot() {
    if (analogRead(IRPin) < IR_DETECT_THRESHOLD) {
      while(true){
        stop();}
    }
}

void moveBack() {
    leftMotor.run(100);
    rightMotor.run(-100); 
    unsigned long moveStartTime = millis();
    while (millis() - moveStartTime < 500) {
        killBot();
    }
}
