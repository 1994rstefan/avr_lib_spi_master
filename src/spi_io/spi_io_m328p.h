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

#ifndef AVR_LIB_SPI_MASTER_SPI_IO_H
#  error "Include <spi_io/spi_io.h> instead of this file."
#endif

#ifndef AVR_LIB_SPI_MASTER_SPI_IO_XXX
#  define AVR_LIB_SPI_MASTER_SPI_IO_XXX "spi_io_m328p.h"
#else
#  error "Attempt to include more than one <spi_io/spi_io_XXX.h> file."
#endif

#define DDR_SPI	DDRB
#define DD_MOSI	DDB3
#define DD_MISO	DDB4
#define DD_SCK	DDB5