#ifndef AES_H
#define AES_H

#include <stdint.h>


void add_round_key(uint8_t state[4][4], uint8_t round_key[4][4]);

void create_state(uint8_t plaintext[16], uint8_t state[4][4]);
void print_state(uint8_t state[4][4]);

void sub_bytes(uint8_t state[4][4]); 
void shift_rows(uint8_t state[4][4]);
void mix_columns(uint8_t state[4][4]);
uint8_t xtime(uint8_t x);

#endif // AES_H