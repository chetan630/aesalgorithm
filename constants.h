#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

/* AES S-Boxes */
extern const uint8_t sbox[256];
extern const uint8_t inv_sbox[256];

/* Round Constants */
extern const uint8_t rcon[10];

#endif // CONSTANTS_H