#include <pololu/orangutan.h>
#include <util/delay.h>

void encoder_init(void);

unsigned long e0, e1;

int main()
{
	clear();
	lcd_goto_xy(0, 0);
	print(" Pokey");

	encoder_init();

	while (1) {
		lcd_goto_xy(0, 0);
		print_long(e0);
		lcd_goto_xy(0, 1);
		print_long(e1);
		_delay_ms(20);
	}

	return 0;
}

/**
 * Initialize dual encoder pins using PC0, PC1, set up interrupts
 */
void encoder_init() {
	PCMSK1 |= (1<<PCINT8)|(1<<PCINT9);		// Enable PC0 (PCINT8), PC1 (PCINT9)
	PCICR |= (1<<PCIE1);					// Enable PCINT1 interrupts
	DDRC &= ~((1<<PC0)|(1<<PC1));			// Ensure PC0, PC1 are inputs
	e0 = e1 = 0;							// Reset counters
	sei();
}

ISR(PCINT1_vect) {
	static uint8_t last = 0;
	static uint8_t change = 0;
	
	change = PINC ^ last;
	
	if (change & (1<<PC0)) {
		e0++;
	}
	
	if (change & (1<<PC1)) {
		e1++;
	}
	
	last = PINC;
}
