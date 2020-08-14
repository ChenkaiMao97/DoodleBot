#include"control.h"

using namespace std;

Control::Control(int pin_lift, int pin_left, int pin_right){
	gpioInitialise();
        SERVOPINLIFT = pin_lift;
	SERVOPINLEFT = pin_left;
	SERVOPINRIGHT = pin_right;

	GoTo(lastX, lastY);
	Lift(LIFT_STATE::BETWEEN_NUMS);
}


void Control::Calibrate(){
	// while(true){
	// 	GoTo()
	// }
}

void Control::Lift(LIFT_STATE s){
	int target;

	switch(s){
		case LIFT_STATE::ON_DRAW:
			target = LIFT0;
			break;
		case LIFT_STATE::BETWEEN_NUMS:
			target = LIFT1;
			break;
		case LIFT_STATE::LIFTED:
			target = LIFT2;
			break;
	}

	while(true){
		int increment = lift_k*(target-servoLift);
		servoLift += increment;
		if (increment == 0) break;
		gpioServo(SERVOPINLIFT,servoLift);
		time_sleep(LIFTSPEED);
	}
}

void Control::circle(float bx,float by,float radius, int start,int ende, float sqee, bool clockwise){
	
}


void Control::GoTo(double pX, double pY){
	double dx, dy, c;

	// x, y difference of new point
	dx = pX-lastX;
	dy = pY-lastY;

	// path steps, with each mm taking 6 steps
	c = floor(6 * sqrt(dx * dx + dy * dy));
	if (c < 1) c = 1;

	for(int i=0;i<=c+30;i++){ // overshoot by a bit
		set_XY(lastX + (i * dx / c), lastY + (i * dy / c));
	}
	lastX = pX;
	lastY = pY;
}

void Control::GoHome(){
	Lift(LIFT_STATE::LIFTED);
	GoTo(0, 100);
	Lift(LIFT_STATE::BETWEEN_NUMS);
	cout<< "homed" << endl;
}

double Control::return_angle(double a, double b, double c){
	return acos((a * a + c * c - b * b)/(2 * a * c));
}

void Control::set_XY(double Tx, double Ty){
	double dx, dy, c, a1, a2, Hx, Hy;
	//printf("Tx=%f,Ty=%f\n", Tx, Ty);

	// based on y we set the height by adjusting lift, using a heuristical function"
	//int lift = 2240*Ty/(27.3+Ty);

	// for the left servo
	dx = Tx-O1X;
	dy = Ty-O1Y;

	c = sqrt(dx * dx + dy * dy);
	a1 = atan2(dy, dx);
	a2 = return_angle(L1,L4,c);

        int new_left = (a2 + a1 - M_PI)/M_PI * SERVOFACTOR_LEFT+LEFTSERVONULL;
	printf("new_left: %d, ", new_left);
	printf("angle on the left should be: %f\n", (a2+a1)*180/M_PI);
	gpioServo(SERVOPINLEFT, (a2 + a1 - M_PI)/M_PI * SERVOFACTOR_LEFT+LEFTSERVONULL);

	a2 = return_angle(L4, L1, c);
	double TH_angle = a1 + M_PI - a2 + alpha_0;

	Hx = Tx + L3 * cos(TH_angle);
	Hy = Ty + L3 * sin(TH_angle);
	//printf("Hx=%f, Hy=%f\n",Hx, Hy);

	// now for the right servo
	dx = Hx - O2X;
	dy = Hy - O2Y;

	c = sqrt(dx * dx + dy * dy);
	a1 = atan2(dy,dx);
	a2 = return_angle(L1, L2, c);

	int new_right = (a1 - a2)/M_PI * SERVOFACTOR_RIGHT+RIGHTSERVONULL;
        printf("new_right: %d", new_right);
	printf("angle on the right should be: %f\n", (a1-a2)*180/M_PI);
	gpioServo(SERVOPINRIGHT, (a1 - a2)/M_PI * SERVOFACTOR_RIGHT + RIGHTSERVONULL);

}
