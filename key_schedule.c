
#include "constants.h"
#include "key_schedule.h"

extern const uint8_t rcon[10];

void g(uint8_t word[4], int round)
{
    rot_word(word);
    sub_word(word);
    add_rcon(word, round);
}

// rotation of 1 byte to the left
void rot_word(uint8_t word[4])
{
    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}


void sub_word(uint8_t word[4])
{
    for(int i=0;i<4;i++)
    {
        word[i] = sbox[word[i]];
    }
}

void add_rcon(uint8_t word[4], int round)
{
    word[0] ^= rcon[round];
}

void xor_words(uint8_t result[4],
               uint8_t a[4],
               uint8_t b[4])
{
    for(int i=0;i<4;i++)
        result[i] = a[i] ^ b[i];
}


void key_expansion(uint8_t key[16], uint8_t w[44][4])
{
    // first 4 words are the key itself
    for(int i=0;i<4;i++)
    {
        w[i][0] = key[4*i];
        w[i][1] = key[4*i + 1];
        w[i][2] = key[4*i + 2];
        w[i][3] = key[4*i + 3];
    }

    for(int i=4;i<44;i++)
    {
        uint8_t temp[4];
        temp[0] = w[i-1][0];
        temp[1] = w[i-1][1];
        temp[2] = w[i-1][2];
        temp[3] = w[i-1][3];

        if(i % 4 == 0)
            g(temp, i/4 - 1);

        xor_words(w[i], w[i-4], temp);
    }
}

void get_round_key(uint8_t w[44][4], int round, uint8_t round_key[4][4])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            round_key[j][i] = w[round * 4 + i][j];
        }
    }
}