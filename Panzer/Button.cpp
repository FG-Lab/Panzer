// A simple class for simulating digital button behavior with electrical buttons

#include <Arduino.h>

namespace Panzer
{
class Button
{
public:
    Button(short pin_a) : pin(pin_a){};

    void begin()
    {
        pinMode(pin, INPUT);
    }

    // Public in case force-updating is necessary
    void update_state()
    {
        switch(digitalRead(pin))
        {
            case HIGH:
                last_state = HIGH;
                break;
            case LOW:
                last_state = LOW;
                break;
        }
    }

    // Returns if the button was pressed this loop. FOR SIMPLICITY DOES NOT WORK WHEN CALLED MULTIPLE TIMES IN A ROW! Save value of first call if needed!
    bool is_pressed()
    {
        if(digitalRead(pin) and !last_state)
        {
            update_state();
            return true;
        }
        update_state();
        return false;
    }


    // Returns if the button was freed this loop. FOR SIMPLICITY DOES NOT WORK WHEN CALLED MULTIPLE TIMES IN A ROW! Save value of first call if needed!
    bool is_freed()
    {
        if(!digitalRead(pin) and last_state)
        {
            update_state();
            return true;
        }
        update_state();
        return false;
    }

    bool is_held()
    {
        update_state();
        return digitalRead(pin);
    }

private:
    short pin;
    bool last_state = LOW;
    bool pressed = false;
    bool freed = false;
};
}
