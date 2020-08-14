#include<control.h>
#include<signal.h>
#include<pigpio.h>

Control control(27,4,17);

void setup(){
	//control.Calibrate();
	control.GoHome();
}

void stop(int signum)
{

}


int main(){
	if (gpioInitialise() < 0) return -1;
	//gpioSetSignalFunc(SIGINT, stop);

        setup();
	while(true){
		// testing GoTo()
		float goto_x, goto_y;
		int lift_input;
		printf("Please input two float numbers and one int number for goto_x, goto_y and lift servo control: ");
		scanf("%f %f %d", &goto_x, &goto_y, &lift_input);
		control.GoTo(goto_x, goto_y);
		gpioServo(control.SERVOPINLIFT,lift_input);
		time_sleep(0.1);
	}

	printf("\ntidying up\n");
        gpioServo(control.SERVOPINLIFT, 0);
        gpioServo(control.SERVOPINLEFT, 0);
        gpioServo(control.SERVOPINRIGHT, 0);


	gpioTerminate();
	return 0;
}

