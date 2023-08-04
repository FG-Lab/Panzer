// This is a class for controlling a DC Motor with an L239DNE
//
// The L239DNE is a Dual H-Bridge Motor Driver
// Per Motor and Side the L239DNE has 5 Pins: Enable, Input1, Output1, Input2 and Output2. It also has four ground pins,
// a logic-voltage-supply pin and a motor-voltage-supply pin, making it 16 in total.
// See https://wiki-content.arduino.cc/documents/datasheets/H-bridge_motor_driver.PDF for pin arrangement.
//
// To drive a motor with an L239DNE, follow the following steps:
// 1. Connect the logic-supply pin to 5V and all the ground-pins to ground.
// 2. Connect both ends of your motor with the Output pins.
// 3. Connect Input1 and Input2 with any digital pins and connect the enable pin with a digital pin capable of PWD. The Input pins will affect which direction the motor will take, while turning the enable pin on and off will affect speed.
// 4. Make an instance of the Motor class and setup your steering code with the provided API.
// 5. If you are sure that you wired everything the correct way and that the motor-power-supply is connected to common ground, connect the motor-power-supply with the motor-voltage-supply pin

#include <Arduino.h>


namespace Panzer
{
class Motor
{
public:
	Motor(short pin_1, short pin_2, short pin_3) : enable_pin(pin_1), input_pin_1(pin_2), input_pin_2(pin_3){};

	void begin()
	{
		pinMode(input_pin_1, OUTPUT);
		pinMode(input_pin_2, OUTPUT);
	}

	void start()
	{
		enabled = true;
		digitalWrite(enable_pin, 0);
		digitalWrite(input_pin_1, 0);
		digitalWrite(input_pin_2, 0);
	}

	void stop()
	{
		enabled = false;
		digitalWrite(enable_pin, 0);
		digitalWrite(input_pin_1, 0);
		digitalWrite(input_pin_2, 0);
	}

	void toggle()
	{
		enabled = !enabled;
		digitalWrite(enable_pin, 0);
		digitalWrite(input_pin_1, 0);
		digitalWrite(input_pin_2, 0);
	}

	// Will accelerate the vehicle forwards at given speed. Max is 255, minimum is -255
	void accelerate_forwards(short speed)
	{
		if(enabled == true)
		{
			if(speed < 0)
			{
				analogWrite(enable_pin, -1 * speed);
				digitalWrite(input_pin_1, 0);
				digitalWrite(input_pin_2, 1);
				return;
			}
			analogWrite(enable_pin, speed);
			digitalWrite(input_pin_1, 1);
			digitalWrite(input_pin_2, 0);
		}
	}

	// Will accelerate the vehicle backwards at given speed. Max is 255, minimum is -255
	void accelerate_backwards(short speed)
	{
		if(enabled == true)
		{
			if(speed < 0)
			{
				analogWrite(enable_pin, -1 * speed);
				digitalWrite(input_pin_1, 1);
				digitalWrite(input_pin_2, 0);
			}
			analogWrite(enable_pin, speed);
			digitalWrite(input_pin_1, 0);
			digitalWrite(input_pin_2, 1);
		}
	}

	bool is_enabled()
	{
		return enabled;
	}

private:
	bool enabled = false;
	short enable_pin;
	short input_pin_1;
	short input_pin_2;
};
}
