#include <SoftwareSerial.h>
#include <Servo.h>

#define servoMot 6
#define servoHai 7
#define servoBa 8
#define servoBon 9

SoftwareSerial mybluetooth(2, 3);

Servo sv1;
Servo sv2;
Servo sv3;
Servo sv4;

int gocSv1 = 110;
int gocSv2 = 0;
int gocSv3 = 180;
int gocSv4 = 75;
// int angleFirst = 180;
// int angle = 0; // Góc ban đầu
char value;

const int lazer = 10;

void setup() {
  Serial.begin(9600);
  mybluetooth.begin(9600);
  sv1.attach(servoMot);
  sv2.attach(servoHai);
  sv3.attach(servoBa);
  sv4.attach(servoBon);

  sv1.write(gocSv1);
  sv2.write(gocSv2);
  sv3.write(gocSv3);
  sv4.write(gocSv4);
  Serial.println("Da san sang");

  // sv1.detach();
  // sv2.detach();
  // sv3.detach();
  sv4.detach();

  pinMode(lazer, OUTPUT);
}

void loop() {
  if(mybluetooth.available()>0) {
      value = mybluetooth.read();

      if(value == 'F') {
        if(gocSv2 < 180) { 
          // sv2.attach(servoHai);
          gocSv2 += 2; 
          sv2.write(gocSv2);
          // sv2.detach();
        }
      }

      if(value == 'B') {
        if(gocSv2 > 0) { 
          // sv2.attach(servoHai);
          gocSv2 -= 2; 
          sv2.write(gocSv2); 
          // sv2.detach();
        }
      }

      if (value == 'G')
      {
        if (gocSv3 < 180)
          {
            // sv3.attach(servoBa);
            gocSv3 += 2; 
            sv3.write(gocSv3); 
            // sv3.detach();
          }
      }

      if (value == 'I')
      {
        if (gocSv3 > 0)
        {
            // sv3.attach(servoBa);
            gocSv3 -= 2; 
            sv3.write(gocSv3); 
            // sv3.detach();
        }
      }


      // if(value == 'F') {

      // }

      // if(value == 'B') {
      //   if(gocSv3 > 0) { 

      //   }
      // }

      if(value == 'L') {
        Serial.println("Gia tri tra ve la L");
        if(gocSv1 < 180 && gocSv1 >= 90) {
          // sv1.attach(servoMot);
          gocSv1+=2;
          sv1.write(gocSv1);
          // sv1.detach();
        }
      }
      if(value == 'R') {
        Serial.println("Gia tri tra ve la R");
        if(gocSv1 <= 180 && gocSv1 > 90) {
          // sv1.attach(servoMot);
          gocSv1-=2;
          sv1.write(gocSv1);
          // sv1.detach();
        }
      }
      
        if(value == 'H') {
        Serial.println("Gia tri tra ve la G");

          if(gocSv4 < 180) { 
            sv4.attach(servoBon);
            gocSv4 += 1;
            sv4.write(gocSv4);
            sv4.detach();
          }
        }

        if(value == 'J') {
        Serial.println("Gia tri tra ve la I");

          if(gocSv4 > 0) { 
            sv4.attach(servoBon);
            gocSv4 -= 1;
            sv4.write(gocSv4);
            sv4.detach();
          }
        }

    else {
      Serial.println("Chua ket noi duoc");
    }
  }

  if (value == 'V')
  {
      digitalWrite(lazer, HIGH);
  }  
  if (value == 'v')
  {
      digitalWrite(lazer, LOW);
  }
}




