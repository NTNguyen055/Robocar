#include <Servo.h>
#include <SoftwareSerial.h>
#include <L298N.h>
SoftwareSerial mybluetooth(2,3);

#define ENA	5
#define IN1	6
#define IN2	7
#define IN3	8
#define IN4	9
#define ENB	10

L298N motor1(ENA, IN1, IN2); //TRAI
L298N motor2(ENB, IN3, IN4); // PHAIR

#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

void setup() {

    Serial.begin(9600);
    mybluetooth.begin(9600);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    Serial.println("Da san sang");

    pinMode(PIN_LED, OUTPUT);
}

void loop() {

    char codeReceived;

    if(mybluetooth.available()>0) 
    {
      codeReceived = mybluetooth.read();
    }

    switch (codeReceived) {
        case 'F': {
            motor_1_Tien(MAX_SPEED);
            motor_2_Tien(MAX_SPEED);
          } 
          break;
        case 'L': {
            motor_2_Tien(MAX_SPEED);
          } 
          break;
        case 'B': {
            motor_1_Lui(MAX_SPEED);
            motor_2_Lui(MAX_SPEED);
          } 
          break;
        case 'R': {
            motor_1_Tien(MAX_SPEED);
          } 
          break;
        case 'S': stop(); break;
        case 'M': turnOnLed(); break;
        case 'm': turnOffLed(); break;
    }
}

void turnOnLed() {
    digitalWrite(PIN_LED, HIGH);
}

void turnOffLed() {
    digitalWrite(PIN_LED, LOW);
}

void motor_1_Dung() {
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
}
 
void motor_2_Dung() {
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
}
 
void motor_1_Tien(int speed) {
  motor1.setSpeed(speed);
  motor1.backward();
}
 
void motor_1_Lui(int speed) {
  motor1.setSpeed(speed);
  motor1.forward();
}
 
void motor_2_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  motor2.setSpeed(speed);
  motor2.forward();
}
 
void motor_2_Lui(int speed) {
  motor2.setSpeed(speed);
  motor2.backward();
}

