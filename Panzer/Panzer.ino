#include "Motor.cpp"
#include "Button.cpp"

short speed = 0;
Panzer::Button button_toggle_status(5);
Panzer::Button button_speed_up(6);
Panzer::Button button_speed_down(7);

Panzer::Motor motor1(3, 2, 4);

void setup()
{
    //Serial.begin(9600);

    button_toggle_status.begin();
    button_speed_up.begin();
    button_speed_down.begin();

    motor1.begin();
    motor1.start();
}

void loop()
{
    if(button_speed_down.is_pressed() and speed >= -200)
    {
        speed -= 50;
    }

    if(button_speed_up.is_pressed() and speed <= 200)
    {
        speed += 50;
    }

    if(button_toggle_status.is_pressed())
    {
        motor1.toggle();
    }

    motor1.accelerate_forwards(speed);
}
