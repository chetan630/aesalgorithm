#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "key_schedule.h"
#include "aes.h"

int main()
{
    uint8_t key[16] =
    {
        0x24, 0x75, 0xA2, 0xb3, 0x34, 0x75, 0x56, 0x88, 0x31, 0xe2, 0x12, 0x00, 0x13, 0xaa, 0x54, 0x87
    };

    uint8_t plaintext[16] =
    {
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    uint8_t w[44][4];

    key_expansion(key, w);

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