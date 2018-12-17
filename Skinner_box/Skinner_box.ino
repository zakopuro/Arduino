#include <Servo.h> 

Servo servo;
#define HUMAN_SENSOR_PIN  (2)
#define SERVO_MOTOR_PIN   (8)
#define LED_PIN           (13)
// static int  motorstate = 0;

void setup(){
  servo.attach(SERVO_MOTOR_PIN);
  servo.write(0);
  pinMode(LED_PIN,OUTPUT);
  pinMode(HUMAN_SENSOR_PIN,INPUT);
  delay(2000);
}

void loop(){
  static int a;

  if (digitalRead(HUMAN_SENSOR_PIN) == LOW){
    // Do Nothing
  } else{
    if ( a == 0){
      servo.write(90);
      a = 1;
      digitalWrite(LED_PIN,HIGH);
    } else{
      servo.write(0);
      a = 0;
      digitalWrite(LED_PIN,LOW);
    }
    delay(3000);
  }
}