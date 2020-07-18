#pramga once

#include<iostream>
#include<pigpio.h>
#include<signal.h>
#include<math.h>


#define NUM_GPIO 26

#define MIN_WIDTH 500 
#define MAX_WIDTH 2500

enum LIFT_STATE
{
	ON_DRAW,
	BETWEEN_NUMS,
	LIFED
};


class Control(){
public:
	Control(int pin_lift, int pin_left, int pin_right);
	void Calibrate();

	void DrawNumber(float bx, float by, int num, float scale);

	void Lift(LIFT_STATE s);
	void GoTo(double px, double py);
	void GoHome();
	void Clear();

private:
	int SERVOFACTOR = 1920;

	int LEFTSERVONULL=1810;
	int RIGHTSERVONULL=970;

	int LIFT0=1650;
	int LIFT1=1500;
	int LIFT2=1350;
	float lift_k=0.5;

	int SERVOPINLEFT = 4;
	int SERVOPINRIGHT = 17;
	int SERVOPINLIFT = 27;

	int LIFTSPEED = 0.2; // the time it waits between each lifting step

	// geometry dimensions in millimeter, see reference graph
	float L1 = 61.5;
	float L2 = 120;
	float L3 = 22.63; // 16 * 2^0.5
	float L4 = 136.94; //sqrt( L2^2+L3^2-2*L2*L3*cos(135) )
	float alpha_0 = 0.6683; //acos((L3^2+L4^2-L2^2)/(2*L3*L4))

	float O1X = -30;
	float O1Y = -41.7;
	float O2X = 30;
	float O2Y = -41.7;

	//volatile double lastX = 35;
	//volatile double lastY = 50;
	volatile int servoLift = 1500;

	void circle(float bx,float by,float radius, int start,int ende, float sqee, bool clockwise);

	double return_angle(double a, double b, double c);

	void set_XY(double Tx, double Ty);

}