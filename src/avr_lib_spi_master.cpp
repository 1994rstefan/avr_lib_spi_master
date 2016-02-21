/*
    AVR SPI-Master Library
    Copyright (C) 2016 Stefan Reisinger <dev@stefan-reisinger.at>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "avr_lib_spi_master.h"

AvrLibSpiMaster::AvrLibSpiMaster(volatile uint8_t *ss_port, uint8_t ss_pin,
                                 AvrLibSpiMaster::SPI_MODE spi_mode,
                                 AvrLibSpiMaster::SPI_SPEED spi_speed,
                                 AvrLibSpiMaster::DATA_ORDER data_order) {
    register_SPCR = _BV(SPE) | _BV(MSTR);

    switch (spi_mode) {
        case SPI_MODE_0:
            // nothing to do
            break;
        case SPI_MODE_1:
            register_SPCR |= _BV(CPHA);
            break;
        case SPI_MODE_2:
            register_SPCR |= _BV(CPOL);
            break;
        case SPI_MODE_3:
            register_SPCR |= _BV(CPHA);
            register_SPCR |= _BV(CPOL);
            break;
    }

    switch (spi_speed) {
        case F_2:
        case F_4:
            // nothing to do
            break;
        case F_8:
        case F_16:
            register_SPCR |= _BV(SPR0);
            break;
        case F_32:
        case F_64:
            register_SPCR |= _BV(SPR1);
            break;
        case F_128:
            register_SPCR |= _BV(SPR0);
            register_SPCR |= _BV(SPR1);
            break;
    }

    if (spi_speed == F_2 || spi_speed == F_8 || spi_speed == F_32) {
        register_SPSR |= _BV(SPI2X);
    }

    switch (data_order) {
        case LSB:
            register_SPCR |= _BV(DORD);
            break;
        case MSB:
            // nothing to do
            break;
    }

    port_ss = ss_port;
    pin_ss = (uint8_t) _BV(ss_pin);
    *port_ss |= pin_ss;
}

void AvrLibSpiMaster::startTransmission() {
    DDR_SPI |= _BV(DD_MOSI) | _BV(DD_SCK);
    DDR_SPI &= ~(_BV(DD_MISO));

    SPSR = register_SPSR;
    SPCR = register_SPCR;

    *port_ss &= ~(pin_ss);
}

void AvrLibSpiMaster::endTransmission() {
    SPCR &= ~(_BV(SPE));
    *port_ss |= pin_ss;
}

uint8_t AvrLibSpiMaster::transceive(uint8_t data) {
    SPDR = data;
    while (!(SPSR & _BV(SPIF)));
    return SPDR;
}

uint8_t AvrLibSpiMaster::transceive() {
    SPDR = 0;
    while (!(SPSR & _BV(SPIF)));
    return SPDR;
}