#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "key_schedule.h"
#include "aes.h"

int main()
{
    uint8_t key[16] =
    {
        0x2B,0x7E,0x15,0x16,
        0x28,0xAE,0xD2,0xA6,
        0xAB,0xF7,0x15,0x88,
        0x09,0xCF,0x4F,0x3C
    };

    uint8_t w[44][4];
    key_expansion(key, w);

    uint8_t plaintext[16] =
    {
        0x32,0x43,0xF6,0xA8,
        0x88,0x5A,0x30,0x8D,
        0x31,0x31,0x98,0xA2,
        0xE0,0x37,0x07,0x34
    };

    uint8_t state[4][4];
    uint8_t round_key[4][4];

    create_state(plaintext, state);

    printf("Initial State:\n");
    print_state(state);

    // ----------------------------
    // Round 0
    // ----------------------------
    get_round_key(w, 0, round_key);
    add_round_key(state, round_key);

    printf("\nAfter Round 0 (AddRoundKey):\n");
    print_state(state);

    // ----------------------------
    // Rounds 1 to 9
    // ----------------------------
    for(int round = 1; round <= 9; round++)
    {
        printf("\n========================\n");
        printf("Round %d\n", round);

        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);

        get_round_key(w, round, round_key);
        add_round_key(state, round_key);

        print_state(state);
    }

    // ----------------------------
    // Final Round (Round 10)
    // ----------------------------
    printf("\n========================\n");
    printf("Final Round (10)\n");

    sub_bytes(state);
    shift_rows(state);

    get_round_key(w, 10, round_key);
    add_round_key(state, round_key);

    printf("\nCipher Text State:\n");
    print_state(state);

    return 0;
}