#include <stdio.h>
#include "timer.h"
#include <unistd.h>

int main()
{
	Timer t;
	
	timerReset(&t);
	usleep(124000);
	timerDisp("t", &t);

	return 0;
}
