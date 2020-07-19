#include<control.h>

Control control(27,4,17);

void setup(){
	//control.Calibrate();
	control.GoHome();
}

int main(){
	// setup();
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
	gpioTerminate();
	return 0;
}

