#include <Servo.h>
#include <AFMotor.h>


const int TRIGGER_PIN = A4;
const int ECHO_PIN = A5;
float duration;
float distance;

const int SUPERSPEED = 150;
const int TURN_DELAY = 210;
float left_distance = 0;
float right_distance = 0;
int i = 0;

//instansiate
Servo head;
AF_DCMotor motor_left(4,MOTOR34_1KHZ);
AF_DCMotor motor_right(1,MOTOR12_1KHZ);


void setup() {
  // put your setup code here, to run once:
  // sonar sesor butt
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);

  //servo setup
  head.attach(10);
  look_forward();
  delay(1000);
  check_distance();
  delay(1000);
}

void loop() {

  //check distance
  distance = check_distance();
  delay(50);
  
  if (distance < 50)
  {
    robot_stop();
    look_left();
    delay(1000);
    left_distance = check_distance();
    delay(100);
    
    look_right();
    delay(1500);
    right_distance = check_distance();
    delay(100);
    
    if ( (left_distance > 50) || (right_distance > 50))
    {
      if (left_distance > right_distance)
      {
        robot_turn_left();
      }
      else if (right_distance > left_distance)
      {
        robot_turn_right();
      }
    }
    else
    {
      robot_turn_180();
    }

    look_forward();
    delay(1000);
  }
  else
  {
    robot_forward();
  }

}
//======================================================================
float check_distance()
{ 
  float sonar_distance;
  
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  sonar_distance = (duration*.0343)/2;
  //Serial.print("Distance: ");
  //Serial.println(sonar_distance);
  //delay(10);
  return sonar_distance;
}
//======================================================================
void look_forward()
{
  head.write(90);
}

//======================================================================
void look_left()
{
  head.write(180);
}
//======================================================================
void look_right()
{ 
  head.write(0);
}
//======================================================================
void robot_stop()
{
  for (i = SUPERSPEED; i > 0 ; i -=1)
  {
    motor_left.setSpeed(i);
    motor_right.setSpeed(i);
  }
  motor_left.run(RELEASE);  
  motor_right.run(RELEASE);
}
//======================================================================
void robot_forward()
{
  motor_left.run(FORWARD);
  motor_right.run(FORWARD);
  for (i = 0; i < SUPERSPEED; i +=1)
  {
    motor_left.setSpeed(i);
    motor_right.setSpeed(i);
  }
}
//======================================================================
void robot_backward()
{
  motor_left.run(BACKWARD);
  motor_right.run(BACKWARD);
  for (i = 0; i < SUPERSPEED; i +=1)
  {
    motor_left.setSpeed(i);
    motor_right.setSpeed(i);
  }
}
//======================================================================
void robot_turn_left()
{
  motor_left.run(BACKWARD);
  motor_right.run(FORWARD);
  for (i = 0; i < SUPERSPEED; i +=1)
  {
    motor_left.setSpeed(i);
    motor_right.setSpeed(i);
  }
  delay(TURN_DELAY);
  robot_stop();
}
//======================================================================
void robot_turn_right()
{
  motor_left.run(FORWARD);
  motor_right.run(BACKWARD);
  for (i = 0; i < SUPERSPEED; i +=1)
  {
    motor_left.setSpeed(i);
    motor_right.setSpeed(i);
  }
  delay(TURN_DELAY);
  robot_stop();
}
//======================================================================
void robot_turn_180()
{
  motor_left.run(FORWARD);
  motor_right.run(BACKWARD);
  for (i = 0; i < SUPERSPEED; i +=1)
  {
    motor_left.setSpeed(i);
    motor_right.setSpeed(i);
  }
  delay(TURN_DELAY * 1.6);
  robot_stop();
}
