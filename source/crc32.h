#ifndef __CRC32_H
#define __CRC32_H
#include <stdio.h>

uint32_t CRC_init();
uint32_t CRC_addByte(uint32_t crc, uint8_t b);
uint32_t CRC_add(uint32_t crc, uint8_t const* data, size_t dataLen);
uint32_t CRC_result(uint32_t crc);

#endif
