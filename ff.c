#include <pololu/orangutan.h>
#include "camcom.h"
#include "I2C_master.h"

int main()
{
	unsigned int t;

	I2C_init();

	clear();
	lcd_goto_xy(0, 0);
	print("Pokey");

	const unsigned char servoPins[] = { IO_D0 };
	servos_start(servoPins, sizeof(servoPins));

#ifdef DISABLED
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

	// Motor test
	lcd_goto_xy(0, 1);
	print("motors  ");

	for (t = 0; t < 2000; t++) {
		if (t < 500 || t >= 1500) {
			set_motors(50, -50);
		} else {
			set_motors(-50, 50);
		}
		delay_ms(1);
	}
	set_motors(0, 0);
#endif

	I2C_start(TWI_CAMERA<<1);
	I2C_write(CAM_COM_GET_OBJECTS);
	I2C_stop();
	delay_ms(100);
	I2C_start((TWI_CAMERA<<1)|1);
	uint8_t o = I2C_read_nack();
	I2C_stop();

	lcd_goto_xy(0, 1);
	print("ready   ");

	while(1) {
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
