#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PROXIMITY_SENSOR PE0
#define VALVE PE1

int main ()
{
	DDRE &= 0;
	DDRE |= 0b11111110;
	PORTE &= 0;
	
	uint8_t proximity_sensor_ticks_counter = 0;
	
	while (1) {
		if ((PINE & (1 << PROXIMITY_SENSOR)) == 0) {
			_delay_ms(10);
			if (proximity_sensor_ticks_counter == 0) {
				// enable valve
				PORTE |= 1 << VALVE;
				_delay_ms(2000);
				PORTE &= ~(1 << VALVE);
			}
			if (proximity_sensor_ticks_counter < 10) {
				proximity_sensor_ticks_counter++;
			}
		} else {
			proximity_sensor_ticks_counter = 0;
		}
	}
}
