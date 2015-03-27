#include <pololu/orangutan.h>
#include "gbcam/camcom.h"
#include "I2C_master.h"

void fan_init(void);
void fan_on(void);
void fan_off(void);
void encoder_init(void);

unsigned int eright = 0; // encoder right counter
unsigned int eleft = 0;  // encoder left counter

int main()
{
	unsigned int t;

	I2C_init();

	clear();
	lcd_goto_xy(0, 0);
	print("Pokey");

	const unsigned char servoPins[] = { IO_C2 };
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

#ifdef DISABLE
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

	while(1) {
		red_led(0);
		green_led(1);

//		delay_ms(100);

		I2C_start(TWI_CAMERA, 0); // write register
		I2C_write(CAM_COM_GET_OBJECTS); // command
		I2C_stop();
		delay_ms(100);
		I2C_start(TWI_CAMERA, 1); // read values
		uint8_t o = I2C_read(I2C_NACK);
		I2C_stop();

		if (o == 0) {
			lcd_goto_xy(0, 1);
			print_hex(0);
		}

		while(o--) {
			I2C_start(TWI_CAMERA, 1);
			uint8_t left   = I2C_read(I2C_ACK); // ack
			uint8_t top    = I2C_read(I2C_ACK); // ack
			uint8_t right  = I2C_read(I2C_ACK); // ack
			uint8_t bottom = I2C_read(o); // nack if last object, else ack
			lcd_goto_xy(0, 1);
			print_hex((left + right)>>1);
			I2C_stop();
		}

		red_led(1);
		green_led(0);
		
		delay_ms(100);
	}

	return 0;
}

/**
 * Prepare fan control
 */
inline void fan_init() {
	PORTC &= ~(1<<PC2);
	DDRC |= (1<<PC2);
}

/**
 * Run the fan on PC2
 */
inline void fan_on() {
	PORTC |= (1<<PC2);
}

inline void fan_off() {
	PORTC &= ~(1<<PC2);
}
	

/**
 * Initialize dual encoder pins using PC0, PC1, set up interrupts
 */
inline void encoder_init() {
	PCMSK1 |= (1<<PCINT8)|(1<<PCINT9);		// Enable PC0 (PCINT8), PC1 (PCINT9)
	PCICR |= (1<<PCIE1);					// Enable PCINT1 interrupts
	DDRC &= ~((1<<PC0)|(1<<PC1));			// Ensure PC0, PC1 are inputs
	eright = eleft = 0;							// Reset counters
	sei();
}

/**
 * Interrupt handler for PCINT8/PCINT9
 */
ISR(PCINT1_vect) {
	static uint8_t last = 0;
	static uint8_t change = 0;
	
	change = PINC ^ last;
	
	if (change & (1<<PC0)) {
		eright++;
	}
	
	if (change & (1<<PC1)) {
		eleft++;
	}
	
	last = PINC;
}

