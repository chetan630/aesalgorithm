#ifndef AES_H
#define AES_H

#include <stdint.h>

/* Common Functions */
void create_state(uint8_t input[16], uint8_t state[4][4]);
void print_state(uint8_t state[4][4]);

/* Round Key */
void add_round_key(uint8_t state[4][4],
                   uint8_t round_key[4][4]);

/* Encryption Functions */
void sub_bytes(uint8_t state[4][4]);
void shift_rows(uint8_t state[4][4]);
void mix_columns(uint8_t state[4][4]);
uint8_t xtime(uint8_t x);

/* Decryption Functions */
void inv_sub_bytes(uint8_t state[4][4]);
void inv_shift_rows(uint8_t state[4][4]);
void inv_mix_columns(uint8_t state[4][4]);

/* Galois Field Multiplication */
uint8_t gf_mul(uint8_t a, uint8_t b);

/* Complete Block Operations */
void aes_encrypt_block(uint8_t plaintext[16],
                       uint8_t key[16],
                       uint8_t ciphertext[16]);

void aes_decrypt_block(uint8_t ciphertext[16],
                       uint8_t key[16],
                       uint8_t plaintext[16]);

#endif // AES_H