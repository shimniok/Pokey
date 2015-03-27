#include <pololu/orangutan.h>

int main()
{
	unsigned int t;

	clear();
	lcd_goto_xy(0, 0);
	print(" Pokey");

	const unsigned char servoPins[] = { IO_D0 };
	servos_start(servoPins, sizeof(servoPins));

	// Init Fan motor controller
	for (t = 1000; t <= 2000; t += 10) {
		set_servo_target(0, t);
		delay_ms(10);
	}
	delay_ms(3000);
	for (t = 2000; t >= 1000; t -= 20) {
		set_servo_target(0, t);
		delay_ms(10);
	}
	delay_ms(2000);

	while(1)
	{
		red_led(0);
		green_led(1);

		delay_ms(100);

		red_led(1);
		green_led(0);
		
		delay_ms(100);
	}

	return 0;
}

// Local Variables: **
// mode: C **
// c-basic-offset: 4 **
// tab-width: 4 **
// indent-tabs-mode: t **
// end: **
