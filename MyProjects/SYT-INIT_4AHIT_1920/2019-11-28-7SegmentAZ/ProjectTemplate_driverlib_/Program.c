#include <avr/io.h>
#include "Wait.h"

void SegmentAusgabe(uint8_t pos) {
	uint8_t patterns[10];
	patterns[0] = 0x3F;
	patterns[1] = 0x06;
	patterns[2] = 0x5B;
	patterns[3] = 0x4F;
	patterns[4] = 0x66;
	patterns[5] = 0x6D;
	patterns[6] = 0x7D;
	patterns[7] = 0x07;
	patterns[8] = 0x7F;
	patterns[9] = 0x6F;

	if (pos >= 0 && pos <= 9) {
		PORTA = patterns[pos];
	}
}

int main()
{
	DDRA = 0xFF;
	DDRC |= (0x01 << 6 | 0x01 << 7);
    while (1)
    {
		for (uint8_t i = 0; i < 100; i++) {
			uint8_t es = i % 10;
			uint8_t zs = (i - es) / 10;
			for (uint8_t j = 0; j < 100; j++) {
				if (zs != 0) {
					PORTC = 0x01 << 7;
					SegmentAusgabe(zs);
				}
				WaitMs(5);
				PORTC = 0x01 << 6;
				SegmentAusgabe(es);
				WaitMs(5);
			}
		}
    }
}











