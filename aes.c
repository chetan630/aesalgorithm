#include "aes.h"
#include "constants.h"
#include <stdio.h>
#include <stdint.h>


void create_state(uint8_t plaintext[16], uint8_t state[4][4])
{
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            state[row][col] = plaintext[col * 4 + row];
        }
    }
}

void print_state(uint8_t state[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            printf("%02X ", state[row][col]);
        }
        printf("\n");
    }
}

void add_round_key(uint8_t state[4][4], uint8_t round_key[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            state[row][col] ^= round_key[row][col];
        }
    }
}


void sub_bytes(uint8_t state[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            state[row][col] = sbox[state[row][col]];
        }
    }
}

void shift_rows(uint8_t state[4][4])
{
    uint8_t temp;

    // Row 1: Shift left by 1
    temp = state[1][0];
    for (int col = 0; col < 3; col++)
    {
        state[1][col] = state[1][col + 1];
    }
    state[1][3] = temp;

    // Row 2: Shift left by 2
    uint8_t temp1 = state[2][0];
    uint8_t temp2 = state[2][1];
    for (int col = 0; col < 2; col++)
    {
        state[2][col] = state[2][col + 2];
    }
    state[2][2] = temp1;
    state[2][3] = temp2;

    // Row 3: Shift left by 3 (or right by 1)
    temp = state[3][3];
    for (int col = 3; col > 0; col--)
    {
        state[3][col] = state[3][col - 1];
    }
    state[3][0] = temp;
}


void mix_columns(uint8_t state[4][4])
{
    for(int col = 0; col < 4; col++)
    {
        uint8_t a = state[0][col];
        uint8_t b = state[1][col];
        uint8_t c = state[2][col];
        uint8_t d = state[3][col];

        uint8_t r0 = xtime(a) ^ (xtime(b) ^ b) ^ c ^ d;
        uint8_t r1 = a ^ xtime(b) ^ (xtime(c) ^ c) ^ d;
        uint8_t r2 = a ^ b ^ xtime(c) ^ (xtime(d) ^ d);
        uint8_t r3 = (xtime(a) ^ a) ^ b ^ c ^ xtime(d);

        state[0][col] = r0;
        state[1][col] = r1;
        state[2][col] = r2;
        state[3][col] = r3;
    }

}

uint8_t xtime(uint8_t x)
{
    return (x << 1) ^ ((x & 0x80) ? 0x1B : 0x00);
}