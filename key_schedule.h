#ifndef KEY_SCHEDULE_H
#define KEY_SCHEDULE_H

#include <stdint.h>

//multiple of 4 
void rot_word(uint8_t word[4]);
void sub_word(uint8_t word[4]);
void add_rcon(uint8_t word[4], int round);
void xor_words(uint8_t result[4],
               uint8_t a[4],
               uint8_t b[4]);
void g(uint8_t word[4], int round);

void key_expansion(uint8_t key[16], uint8_t w[44][4]);

void get_round_key(uint8_t w[44][4], int round, uint8_t round_key[4][4]);

#endif
