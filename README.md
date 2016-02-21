# AVR SPI-Master Library
Library to use the SPI interface of AVR microcontrollers in master mode.

## Reference
### Methods
    AvrLibSpiMaster::AvrLibSpiMaster(uint8_t &SS_PORT, uint8_t SS_PIN, AvrLibSpiMaster::SPI_MODE, AvrLibSpiMaster::SPI_SPEED, AvrLibSpiMaster::DATA_ORDER);
Instantiate the object with specific configuration
* `&SS_PORT` - The Port to use for slave select (e.g. PORTB)
* `SS_PIN` - The Pin to use for slave select (e.g. PB2)
* `SPI_MODE` - One of the four SPI modes (e.g. AvrLibSpiMaster::SPI_MODE_0 )
* `SPI_SPEED` - The SPI bus frequency (e.g. F_2 means System Clock divided by 2)
* `DATA_ORDER` - MSB or LSB first (e.g. AvrLibSpiMaster::MSB)

    void AvrLibSpiMaster::startTransmission()
Set up the SPI registers and pull down slave select. This musst get called before exchanging data with the slave.

    uint8_t AvrLibSpiMaster::transceive(uint8_t data)
Send one byte `data` to the slave and receive the data send by the client in return.

    uint8_t AvrLibSpiMaster::transceive()
Alias for `AvrLibSpiMaster::transceive(0x00)`, useful if you only want to receive data.

    void AvrLibSpiMaster::endTransmission()
Pull up slave select and disable the SPI interface to reduce power consumption

### ENUMs
* AvrLibSpiMaster::SPI_MODE
    * SPI_MODE_0 (CPOL = 0; CPHA = 0)
    * SPI_MODE_1 (CPOL = 0; CPHA = 1)
    * SPI_MODE_2 (CPOL = 1; CPHA = 0)
    * SPI_MODE_3 (CPOL = 1; CPHA = 1)
* AvrLibSpiMaster::SPI_SPEED
Divides the system clock frequency by a specific value. Posible values are:
    * F_2
    * F_4
    * F_8
    * F_16
    * F_32
    * F_64
    * F_128
* AvrLibSpiMaster::DATA_ORDER
    * MSB - Send most significant bit first
    * LSB - Send least signifcant bit first

## startTransmission() and endTransmission()
It is not required to use the `startTransmission()` and `endTransmission()` methods all the time.  
`startTransmission()` only sets the required registers for the SPI interface and pulls the slave select line low.  
`endTransmission()` pulls slave select high again and disables the SPI interface to reduce power consumption.  
If for example you are only using one SPI slave and pool it every few milliseconds you can call `startTransmission()` directly after instantiating the object to setup the SPI registers. After that you can manage the slave select output by yourself.
Also if you are using multiple slaves with the same SPI settings you can call `startTransmission()` one time and then manage the slave selection by yourself.
In this cases you may NOT call `endTransmission()` because it will disable the SPI interface at all.

## Basic usage example
1. Instantiate object

        AvrLibSpiMaster spiMaster(&SS_PORT, SS_PIN, AvrLibSpiMaster::SPI_MODE, AvrLibSpiMaster::SPI_SPEED, AvrLibSpiMaster::DATA_ORDER);

2. Start a transmission, this sets up the SPI registers and pulls SS low

        void spiMaster.startTransmission()

3. Send and receive some Data

        uint8_t spiMaster.transceiv(uint8_t) // send and receive in one function
        uint8_t spiMaster.transceiv() // just receive, automatically sends 0x00

4. End the transmission, this pulls SS high and disables SPI (to reduce power consumption)

        spiMaster.endTransmission()

## Tested MCUs
This Library is not MCU independent because AVR Libc does not define which port and pins to use for the SPI output.  
There is a subfolder `spi_io` which includes SPI IO definitions. If there is no SPI IO definition for your MCU feel free to create one.

Library is tested and working on the following MCUs:

* ATmega328P

## License
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