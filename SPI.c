#include <avr/io.h>

#include "SPI.h"

SPI_t *SPI;

void SPI_Init(SPI_t *spi)
{
	SPI = spi;
}

uint8_t SPI_ReadByte()
{	// Initiate transfer
	uint8_t retval = SPI->DATA;
	// Wait until the byte is completely shifted in
	while (!(SPI->STATUS & SPI_IF_bm));
	// Return the value
	return retval;
}

void SPI_ReadBytes(uint8_t *buffer, uint8_t length)
{
	for (uint8_t i = 0; i < length; i++)
	{
		buffer[i] = SPI_ReadByte();
	}
}

void SPI_WriteByte(uint8_t data)
{	// Initiate transfer
	SPI->DATA = data;
	// Wait until the byte is completely shifted out
	while (!(SPI->STATUS & SPI_IF_bm));
}

void SPI_WriteBytes(uint8_t *buffer, uint8_t length)
{
	for (uint8_t i = 0; i < length; i++)
	{
		SPI_WriteByte(buffer[i]);
	}
}
