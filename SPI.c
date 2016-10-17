#include <avr/io.h>

#include "SPI.h"

SPI_t *SPI;
PORT_t *CSPort;
uint8_t CS;

void SPI_Init(SPI_t *spi, PORT_t *csPort, uint8_t cs)
{
	SPI = spi;
	CSPort = csPort;
	CS = cs;
	// Set CS to high
	CSPort->OUTSET = CS;
	// Configure CS as output
	CSPort->DIRSET = CS;
}

uint8_t SPI_ReadByte(void)
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

void SPI_Begin(void)
{	// Send CS low
	CSPort->OUTCLR = CS;
}

void SPI_End(void)
{	// Send CS high
	CSPort->OUTSET = CS;
}
