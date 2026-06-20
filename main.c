#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "constants.h"
#include "key_schedule.h"
#include "aes.h"

static void clear_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

static int read_input_line(char *buffer,
                           size_t size,
                           const char *prompt)
{
    printf("%s", prompt);

    if (!fgets(buffer, (int)size, stdin))
    {
        return 0;
    }

    size_t len = strcspn(buffer, "\r\n");

    if (buffer[len] == '\r' || buffer[len] == '\n')
    {
        buffer[len] = '\0';
    }
    else
    {
        buffer[len] = '\0';
        clear_stdin();
    }

    return 1;
}

int main(void)
{
    char key_input[18];
    char plaintext_input[18];

    uint8_t key[16];
    uint8_t plaintext[16];
    uint8_t ciphertext[16];
    uint8_t decrypted[16];

    int i;

    /* Read Inputs */
    if (!read_input_line(key_input,
                         sizeof(key_input),
                         "Enter 16 character key : "))
    {
        return 1;
    }

    if (!read_input_line(plaintext_input,
                         sizeof(plaintext_input),
                         "Enter 16 character plaintext : "))
    {
        return 1;
    }

    /* Validate Length */
    if (strlen(key_input) != 16)
    {
        printf("\nError: Key must be exactly 16 characters.\n");
        return 1;
    }

    if (strlen(plaintext_input) != 16)
    {
        printf("\nError: Plaintext must be exactly 16 characters.\n");
        return 1;
    }

    /* Convert to byte arrays */
    memcpy(key, key_input, 16);
    memcpy(plaintext, plaintext_input, 16);

    /* Display Key */
    printf("\nKey (HEX):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%02X ", key[i]);
    }
    printf("\n");

    /* Display Plaintext */
    printf("\nPlaintext (HEX):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    /*
     * ============================
     * Encryption
     * ============================
     */
    aes_encrypt_block(plaintext,
                      key,
                      ciphertext);

    printf("\n========================\n");
    printf("AES Encryption\n");
    printf("========================\n");

    printf("\nCiphertext (HEX):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    printf("\nCiphertext (DECIMAL):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%3d ", ciphertext[i]);
    }
    printf("\n");

    printf("\nCiphertext (ASCII):\n");
    for (i = 0; i < 16; i++)
    {
        if (ciphertext[i] >= 32 &&
            ciphertext[i] <= 126)
        {
            printf("%c", ciphertext[i]);
        }
        else
        {
            printf(".");
        }
    }
    printf("\n");

    /*
     * ============================
     * Decryption
     * ============================
     */
    aes_decrypt_block(ciphertext,
                      key,
                      decrypted);

    printf("\n========================\n");
    printf("AES Decryption\n");
    printf("========================\n");

    printf("\nRecovered Plaintext (HEX):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%02X ", decrypted[i]);
    }
    printf("\n");

    printf("\nRecovered Plaintext (ASCII):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    /*
     * ============================
     * Verification
     * ============================
     */
    if (memcmp(plaintext,
               decrypted,
               16) == 0)
    {
        printf("\nAES Encryption/Decryption Test : PASS\n");
    }
    else
    {
        printf("\nAES Encryption/Decryption Test : FAIL\n");
    }

    return 0;
}