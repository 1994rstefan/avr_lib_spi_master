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

#ifndef AVR_LIB_SPI_MASTER_H
#define AVR_LIB_SPI_MASTER_H

#include <stdint.h>
#include <avr/io.h>
#include "spi_io/spi_io.h"


class AvrLibSpiMaster {
public:
    enum SPI_MODE {
        SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3
    };
    enum SPI_SPEED {
        F_2, F_4, F_8, F_16, F_32, F_64, F_128
    };
    enum DATA_ORDER {
        LSB, MSB
    };

    AvrLibSpiMaster(volatile uint8_t *ss_port, uint8_t ss_pin, AvrLibSpiMaster::SPI_MODE spi_mode,
                    AvrLibSpiMaster::SPI_SPEED spi_speed, AvrLibSpiMaster::DATA_ORDER data_order);

    void startTransmission();

    void endTransmission();

    uint8_t transceive(uint8_t data);

    uint8_t transceive();

private:
    uint8_t register_SPCR;
    uint8_t register_SPSR;
    volatile uint8_t *port_ss;
    uint8_t pin_ss;
};


#endif //AVR_LIB_SPI_MASTER_H
