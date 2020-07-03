#include <avr/io.h>
#include <i2c_bitbanging.h>

int main()
{
    initI2C();
    while (1)
    {
        DDRB |= 0x01<<7;

        sendStartCondition();
        uint8_t ack = sendByte((0x18<<1)&0xFE);
        sendStopCondition();
        if (ack) {
            PORTB |= 0x01<<7;
        }
        WaitMs(500);
        PORTB &= ~(0x01<<7);
        WaitMs(1000);
    }
}