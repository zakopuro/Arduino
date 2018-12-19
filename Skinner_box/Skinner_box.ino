#include <Servo.h>
#include <MsTimer2.h>

Servo servo;
// その他
#define EVENT_OFF   (0)
#define EVENT_ON    (1)
#define EVENT_NONE  (2)

// PIN番号の定義
#define HUMAN_SENSOR_PIN  (2)
#define SERVO_MOTOR_PIN   (8)
#define LED_PIN           (13)
#define LIGHT_SENSOR_PIN  (7)
#define BUZZER            (5)
#define SOUND_SENSOR_PIN  (4)
static boolean  lc_motorstate;
static boolean  lc_buzzerstate;
static boolean  lc_ledstate;

static uint8_t lc_buzzer_input_event;

static uint16_t cnt_buzzer;

void buzzer(){
  cnt_buzzer++;
  if(cnt_buzzer == 100){
    // digitalWrite(BUZZER,LOW);
    delay(1);
    cnt_buzzer = 0;
  } else{
    digitalWrite(BUZZER,HIGH);
  }
}

void pinsetup(){
  servo.attach(SERVO_MOTOR_PIN);
  pinMode(LED_PIN,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  digitalWrite(BUZZER,HIGH);          // buzzerはLOW activeなのでHIGHにしておく
  pinMode(HUMAN_SENSOR_PIN,INPUT);
  pinMode(LIGHT_SENSOR_PIN,INPUT);
}

void setup(){
  lc_motorstate  = false;
  lc_buzzerstate = false;
  lc_ledstate    = false;
  pinsetup();
  MsTimer2::set(10, buzzer);
  MsTimer2::start();
}

void loop(){

  if (digitalRead(SOUND_SENSOR_PIN) == HIGH){
    // lc_ledstate = !lc_ledstate;
    digitalWrite(LED_PIN,HIGH);
  } else{
    digitalWrite(LED_PIN,LOW);
  }
}