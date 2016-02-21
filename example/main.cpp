#include "../src/avr_lib_spi_master.h"
#include <util/delay.h>

int main(void) {
    DDRB |= _BV(PB2);
    AvrLibSpiMaster spiMaster(&PORTB, PB2, AvrLibSpiMaster::SPI_MODE_0, AvrLibSpiMaster::F_2, AvrLibSpiMaster::MSB);

    while (1) {
        spiMaster.startTransmission();
        spiMaster.transceive(0b01010101);
        spiMaster.transceive(0b01010101);
        uint8_t response = spiMaster.transceive();
        spiMaster.endTransmission();
        _delay_ms(500);
    }
    return 0;
}