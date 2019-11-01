#include "Robotraffic.h"

void Robot::SetMotor(int Pin)
{
    this->Motor = Pin;
}

void Robot::SetupServo(int Pin, int Left, int Right)
{
    this->Servo[PIN] = Pin;
    this->Servo[LEFT] = Left;
    this->Servo[RIGHT] = Right;
}

void Robot::SetServo(int Val)
{
    analogWrite(this->Servo[PIN], map(Val, -MAX_FIX, MAX_FIX, this->Servo[LEFT], this->Servo[RIGHT]));
}

void Robot::SetSens(int Sensors[7][3])
{
    for (int i = 0; i < 7; i++)
    {
        this->Sens[i][PIN] = Sensors[i][PIN];
        this->Sens[i][MIN] = Sensors[i][MIN];
        this->Sens[i][MAX] = Sensors[i][MAX];
        pinMode(Sensors[i][PIN], INPUT);
    }
}

bool Robot::ReadFront()
{
    return (analogRead(9) > 400 || analogRead(10) > 400);
}

int Robot::ReadSen(int Num)
{
    return map(analogRead(this->Sens[Num][PIN]), this->Sens[Num][MIN], this->Sens[Num][MAX], 0, 100);
}

void Robot::AverageSen()
{
    for (int i = 0; i < 7; i++)
    {
        long int Sum = 0;
        for (int j = 0; j < 400; j++)
        {
            Sum += analogRead(this->Sens[i][PIN]);
        }
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.print(" 400 readings average: ");
        Serial.println(int(double(Sum)/400));
    }
}

int Robot::LeftSensVal()
{
    return ReadSen(0) + ReadSen(1) + ReadSen(2);
}

int Robot::RightSensVal()
{
    return ReadSen(3) + ReadSen(4) + ReadSen(5);
}

int Robot::GetError()
{
    return LeftSensVal() - RightSensVal();
}

int Robot::ReadLight()
{
	int IRnow = 11;
    while (Serial3.available())
        IRnow = Serial3.read();
	if (IRnow < 10)
	{
		Reading = IRnow;
		IRtime = millis();
	}
	if (millis() - IRtime > 500)
	{
    	Serial.println(-1);
        return -1;
    }
    Serial.println(Reading);
	return Reading;
}

void Robot::Drive(int Speed)
{
    if (Speed > 0)
    {
        int Error = GetError();
        DeriveError = Error - LastError;
        TotalError += Error;
        int Fix = ((Error * P) - (TotalError * I) + (DeriveError * D));
        if (Fix > MAX_FIX)
            Fix = MAX_FIX;
        else if (Fix < -MAX_FIX)
            Fix = -MAX_FIX;
        analogWrite(Motor, Speed);
        SetServo(Fix);
        LastError = Error;
    }
    else
        analogWrite(Motor, 0);
    
}

void Robot::Go()
{
    if (!ReadFront())
    {
        switch (ReadLight())
        {
            case RED_LIGHT:
                RED_H;
                YELLOW_L;
                GREEN_L;
                //while (ReadSen(6) > 50)
                //    Drive(100);
                Drive(0);
                break;

            case RED_YELLOW_LIGHT:
                RED_H;
                YELLOW_H;
                GREEN_L;
                //while (ReadSen(6) > 50)
                //    Drive(100);
                Drive(0);
                break;

            case GREEN_LIGHT:
                RED_L;
                YELLOW_L;
                GREEN_H;
                Drive(60);
                break;

            case FLASHING_GREEN_LIGHT:
                if (millis() - GreenTimer >= 300)
                {
                    GreenTimer = millis();
                    FlashGreen = !FlashGreen;
                    digitalWrite(GREEN_LED, FlashGreen);
                }
                Drive(60);
                break;

            case YELLOW_LIGHT:
                RED_L;
                YELLOW_H;
                GREEN_L;
                //while (ReadSen(6) > 50)
                //    Drive(100);
                Drive(0);
                break;
                
            case 7:
                RED_L;
                YELLOW_L;
                GREEN_L;
                //while (ReadSen(6) > 50)
                //	Drive(100);
                Drive(0);

            default:
                RED_L;
                YELLOW_L;
                GREEN_L;
                Drive(60);
                    break;
        }
    }
    else
    {
        Drive(0);
    }
}

			{0,1,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,1,0,0,0,0,0,0,0},
			{0,0,0,0,1,0,1,1,0,1,0,0},
			{0,0,0,0,1,0,1,0,0,1,0,0},
			{0,0,0,0,1,0,1,0,0,1,0,0},
			{0,0,1,1,1,0,1,0,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,0,1,1,1,1,0,0},
			{0,0,0,0,1,0,0,0,0,0,0,0},
			{0,0,0,0,1,0,0,0,0,0,0,0},
			{0,0,0,0,1,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,1,0}