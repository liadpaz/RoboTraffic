#include "Robotraffic.h"

Robot Traffic;

///Enter sensors data in {(Pin), (Min), (Max)} format (from left (upmost) to right (downmost)).
int Sens[7][3] = {
    {1,1,1},
    {1,1,1},
    {1,1,1},
    {1,1,1},
    {1,1,1},
    {1,1,1},
    {1,1,1}
};
    
void setup()
{
    Traffic.SetSens(Sens);
    ///Enter inside the brackets the motor pin.
    Traffic.SetMotor(1);
    ///Enter servo data in {(Pin), (Value when leftmost), (Value when rightmost)} format.
    Traffic.SetupServo(1,1,1);
}
void loop()
{
    Traffic.Go();
}
