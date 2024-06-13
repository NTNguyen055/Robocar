#include <L298N.h>

#define enA 9   //Enable1 L298 Pin enA 
#define in1 8   //Motor1 L298 Left Pin in1 
#define in2 10   //Motor1 L298 Left Pin in2 
#define in3 13   //Motor2 L298 Right Pin in3
#define in4 12  //Motor2 L298 Right Pin in4 
#define enB 11  //Enable2 L298 Pin enB  

L298N motor1(enA, in1, in2); //TRAI
L298N motor2(enB, in3, in4); // PHAI

#define ir1 2
#define ir2 3
#define ir3 4
#define ir4 5
#define ir5 6

int sensor[5] = { 0, 0, 0, 0, 0 };
#define MOTOR_SPEED 85

int error = 0;

void setup() {

  // Ket noi dau vao cho L298N va ra cho motor
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  Serial.begin(9600);
  delay(2000);
}

void loop() {

  // Doc cac gia tri tin hieu tu cam bien hong ngoai
  sensor[0] = digitalRead(ir1);
  sensor[1] = digitalRead(ir2);
  sensor[2] = digitalRead(ir3);
  sensor[3] = digitalRead(ir4);
  sensor[4] = digitalRead(ir5);

  handle();
}

void handle() {

  //Xet tat ca cac truong hop nhan va khong nhan tin hieu cua cam bien
  if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0)) // phải nhiều
  {
    motor_drive(-MOTOR_SPEED, MOTOR_SPEED);
  }  
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0)) // phải trung
  {
    motor_drive(0, MOTOR_SPEED);
  } 
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))  // phải
  {
    motor_drive(MOTOR_SPEED * 0.4, MOTOR_SPEED);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 1))  // phải ít
  {
    motor_drive(MOTOR_SPEED * 0.7, MOTOR_SPEED);
  }  
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1)) // giữa
  {
    motor_drive(MOTOR_SPEED, MOTOR_SPEED);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))  // trái ít
  {
    motor_drive(MOTOR_SPEED, MOTOR_SPEED * 0.7);
  }
  else if ((sensor[0] ==1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))  // trái
  {
    motor_drive(MOTOR_SPEED, MOTOR_SPEED * 0.4);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))  // trái trung
  {
    motor_drive(MOTOR_SPEED, 0);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))  // trái nhiều
  {
    motor_drive(MOTOR_SPEED, -MOTOR_SPEED);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))  // trái 90
  {
    motor_drive(MOTOR_SPEED, -MOTOR_SPEED);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))  // phải 90
  {
    motor_drive(-MOTOR_SPEED, MOTOR_SPEED);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))  // quay
  // motor_drive(0, 0);
  {
    stop();
  }
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))  // dừng
  {
    stop();
  }
}

void stop() {
  motor1.stop();
  motor2.stop();
};

void motor_drive(int right, int left) {

  // Banh phai
  if(right > 0) 
  {
    motor2.setSpeed(right);
    motor2.forward();
  }
  else {
    right = -right;
    motor2.setSpeed(right);
    motor2.backward();
  }
  
  //Banh trai
  if(left > 0) 
  {
    motor1.setSpeed(left);
    motor1.forward();
  } 
  else {
    left = -left;
    motor1.setSpeed(left);
    motor1.backward();
  }
}
