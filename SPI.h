#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void SPI_Init(SPI_t *spi, PORT_t *csPort, uint8_t cs);

uint8_t SPI_ReadByte(void);
void SPI_ReadBytes(uint8_t *buffer, uint8_t length);

void SPI_WriteByte(uint8_t data);
void SPI_WriteBytes(uint8_t *buffer, uint8_t length);

void SPI_Begin(void);
void SPI_End(void);

#endif
