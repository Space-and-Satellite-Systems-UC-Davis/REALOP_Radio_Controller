#include "aes128.h"

const uint8_t key[] = {0xeb, 0x5d, 0x27, 0x83, 0x44, 0x85, 0x38, 0x8a,
                 0x30, 0xb4, 0x59, 0xa8, 0x0a, 0x91, 0x89, 0x54};
const uint8_t iv[] = {0x50, 0xfe, 0x3c, 0x6a, 0x6d, 0x0d, 0xda, 0x6a,
             0xe7, 0xf0, 0x46, 0x27, 0xae, 0xf6, 0x09, 0x75};
struct AES_ctx StructofAES;

/**
 * Encrypts a message by the AES-128 CBC method of operation and stores it back into the given parameter.
 * Pads zeros if needed.
 * @param Dest: The 256-byte message you want to encrypt.
 */
void Encrypt_Array(uint8_t *Dest) {
  AES_init_ctx_iv(&StructofAES, key, iv);
  AES_CBC_encrypt_buffer(&StructofAES, Dest, MAX_BYTES_MESSAGE);
}

/**
 * Decrypts a message by the AES-128 CBC method of operation and stores it back into
 * given parameter.
 * @param Dest: The 256-byte message you want to decrypt.
 */
void Decrypt_Array(uint8_t *EncryptedText) {
  AES_init_ctx_iv(&StructofAES, key, iv);
  AES_CBC_decrypt_buffer(&StructofAES, EncryptedText, MAX_BYTES_MESSAGE);
}

/**
 * Tests the Encrypt_Array and Decrypt_Array functions with 
 * a starting message being "hello".
 */
void testFunction_AES128_Round_Trip(void) {
  uint8_t finalMessage[256] = {'h', 'e', 'l', 'l', 'o'};
  const uint8_t startMessage[256] = {'h', 'e', 'l', 'l', 'o'};
  printf("%s", finalMessage);
  printf("%s", "\n Encrypted Message: \n ");
  Encrypt_Array(finalMessage);
  printf("%s", finalMessage);
  Decrypt_Array(finalMessage);
  if (0 == memcmp(finalMessage, startMessage, 256)) {
    printf("\nSuccessful Decryption");
  }else{
    printf("\nFailure to Decrypt");
  }
}
