#ifndef ROBO_TRAFFIC
#define ROBO_TRAFFIC
#include <Arduino.h>

#define PIN 0
#define MIN 1
#define MAX 2

#define RED_LED 26
#define YELLOW_LED 24
#define GREEN_LED 22

#define RED_H digitalWrite(RED_LED, HIGH)
#define RED_L digitalWrite(RED_LED, LOW)
#define YELLOW_H digitalWrite(YELLOW_LED, HIGH)
#define YELLOW_L digitalWrite(YELLOW_LED, LOW)
#define GREEN_H digitalWrite(GREEN_LED, HIGH)
#define GREEN_L digitalWrite(GREEN_LED, LOW)

#define LEFT 1
#define RIGHT 2

#define RED_LIGHT            0
#define RED_YELLOW_LIGHT     1
#define GREEN_LIGHT          2
#define FLASHING_GREEN_LIGHT 3
#define YELLOW_LIGHT         4

#define MAX_FIX 100

class Robot
{
private:
    double* const P = nullptr;
    double* const I = nullptr;
    double* const D = nullptr;
	
	int MaxSpeed = 0;
    
    long int TotalError = 0;
    int DeriveError = 0;
    int LastError = 0;

    long int GreenTimer = 0;
    bool FlashGreen = true;

  	long int IRtime = 0;
  	int Reading = 11;

    int Motor;
    int Servo[3];
    void SetServo(int Val);

    int Sens[7][3];
    int ReadSen(int Num);

    bool ReadFront();

    int LeftSensVal();
    int RightSensVal();
    int GetError();

    int ReadLight();

    void Drive(int Speed);

public:
    Robot(double P, double I, double D, int MaxSpeed = 100)
    {
        *(this->P) = P;
        *(this->I) = I;
        *(this->D) = D;
		this->MaxSpeed = MaxSpeed;
        pinMode(RED_LED, OUTPUT);
        pinMode(YELLOW_LED, OUTPUT);
        pinMode(GREEN_LED, OUTPUT);
    }

    ~Robot()
    {
        free(P);
        free(I);
        free(D);
    }
    
    void AverageSen();
    
    void SetupServo(int Pin, int Left, int Right);
    void SetMotor(int Pin);
    void SetSens(int Sensors[7][3]);
    
    void Go();
};
#endif
