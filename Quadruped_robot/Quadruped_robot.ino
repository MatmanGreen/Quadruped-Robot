#include <Servo.h>

int servo_pins[] = {5, 6, 7, 8, 9, 10, 11, 12}; 
int reverse[] = {0, 0, 0, 0, 0, 0, 0, 0}; //1 reverse 0 normal

enum servos 
{
  RB_F = 0, // Right Back Foot
  RB_S,     // Right Back Shoulder
  LB_F,     // Left Back Foot
  LB_S,     // Left Back Shoulder
  RF_F,     // Right Front Foot
  RF_S,     // Right Front Shoulder
  LF_F,     // Left Front Foot
  LF_S      // Left Front Shoulder
};

int for_i = sizeof(servo_pins) / sizeof(servo_pins[0]);

Servo servos[sizeof(servo_pins) / sizeof(servo_pins[0])]; 

void move_servo(int servo_index, 
                int position, 
                int delay_time, 
                int after_delay) 
{
  servos[servo_index].attach(servo_pins[servo_index]); 
  if (reverse[servo_index] == 1) 
  {
    position -= 180; 
  }
  servos[servo_index].write(position);  
  delay(delay_time);                    
  servos[servo_index].detach();
  delay(after_delay);  
}     
  
void wave()
{
  Serial.println("waving hallo to the World");
  move_servo(RF_F, 90, 500, 100);
  move_servo(RF_S, 135, 500, 100);
  for (int i = 0; i < 3; i++)
  {
    move_servo(RF_F, 180, 500, 100);
    move_servo(RF_F, 135, 500, 500);
  }
  move_servo(RF_F, 90, 500, 100);
  move_servo(RF_S, 90, 500, 100);
  move_servo(RF_F, 0, 500, 100);
}

void stand_up()
{
  move_servo(RF_F, 0, 500, 100);
  move_servo(LB_F, 0, 500, 100);
  move_servo(RB_F, 180, 500, 100);
}

void all_90()
{
  for (int i = 0; i < for_i; i++)
  {
    move_servo(i, 90, 500, 100);
  }
}

void stop_all() 
{
  for (int i = 0; i < for_i; i++) 
  {
    servos[i].detach();
  }
  Serial.println("All servos detached");
}

void reset(bool feedback)
{
  for (int i = 0; i < for_i; i++) 
  {
    if (i == RB_F || i == LB_F || i == RF_F || i == LF_F) 
    {
      move_servo(i, 90, 500, 100);
      if(feedback) 
      {
        Serial.print("moved Servo_");
        Serial.println(i);
      }
    }
    else if (i == RB_S || i == LB_S || i == RF_S || i == LF_S) 
    {
      move_servo(i, 0, 500, 100);
      if(feedback) 
      {
        Serial.print("moved Servo_");
        Serial.println(i);
      }
    }
  }
}



void setup() 
{
  Serial.begin(9600);
  Serial.println("");
  Serial.println("enter START to go through the setup");
  
  while (true)
  {
    if (Serial.available() > 0) 
    {
      String input = Serial.readStringUntil('\n');
      input.trim();
      if (input.equalsIgnoreCase("START")) 
      {
        break;
      }
      else 
      {
        Serial.println("invaild input");
      }
    }
  }

  stand_up();
  delay(250);
  Serial.println("setup completed");
}

void loop() 
{
  Serial.println("enter START to activate the loop or STOP to suspend the programm");
  Serial.println("or choose an action:");
  Serial.println("wave");

  while (true)
  {
    if (Serial.available() > 0) 
    {
      String input = Serial.readStringUntil('\n');
      input.trim();
      if (input.equalsIgnoreCase("START")) 
      {
        break;
      }
      else if(input.equalsIgnoreCase("STOP"))
      {
        Serial.println("Programm will be suspended");
        stop_all();
        while(true){};
      }
      else if(input.equalsIgnoreCase("WAVE"))
      {
        wave();
        delay(500);
      }
      else 
      {
        Serial.println("invaild input");
      }
    }
  }
  Serial.println("resetting the servos to 90");
  stand_up();
}

