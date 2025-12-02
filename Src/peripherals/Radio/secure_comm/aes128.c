#include "aes128.h"

const uint8_t key[] = {0xeb, 0x5d, 0x27, 0x83, 0x44, 0x85, 0x38, 0x8a,
                       0x30, 0xb4, 0x59, 0xa8, 0x0a, 0x91, 0x89, 0x54};
const uint8_t iv[] = {0x50, 0xfe, 0x3c, 0x6a, 0x6d, 0x0d, 0xda, 0x6a,
                      0xe7, 0xf0, 0x46, 0x27, 0xae, 0xf6, 0x09, 0x75};
struct AES_ctx StructofAES;

/**
 * Encrypts a maximum length message of 256 bytes by the AES-128 CBC method of
 * operation based on the length specified. The CBC method "requires" the
 * message to be padded with the PKCS#7 scheme and therefore changes the length
 * of the message.
 *
 * Output: Stores encrypted message and length of message
 * back into given respective pointers.
 * @param Dest: The 256-byte message you want to encrypt.
 * @param n: A pointer that stores the address of the length of the message.
 */
void Encrypt_Array(uint8_t *PlainText, size_t *n) {
  if (*n > MAX_BYTES_AES_MESSAGE)
    return;
  // Calculate Padding
  else if (*n != MAX_BYTES_AES_MESSAGE) {
    size_t remainder = AES_BLOCKLEN - (*n % AES_BLOCKLEN);
    memset(PlainText + *n, remainder, remainder);
    // Set new length that is a multiple of 16.
    *n += remainder;
  }

  // Encrypt
  AES_init_ctx_iv(&StructofAES, key, iv);
  AES_CBC_encrypt_buffer(&StructofAES, PlainText, *n);
}

/**
 * Decrypts a maximum length message of 256 bytes by the AES-128 CBC method of
 * operation and stores the message
 * back into the given pointer.
 * YOU MUST USE THE LENGTH GIVEN BY THE ENCRYPT_ARRAY FUNCTION.

 * @param EncryptedText: The 256-byte message you want to decrypt.
 * @param n: The length of the message.
 */
void Decrypt_Array(uint8_t *EncryptedText, size_t n) {
  if (n > MAX_BYTES_AES_MESSAGE)
    return;

  // Decrypt
  AES_init_ctx_iv(&StructofAES, key, iv);
  AES_CBC_decrypt_buffer(&StructofAES, EncryptedText, n);

  // Remove Padding
  unsigned int RemovePadding = *(EncryptedText + n - 1);
  memset(EncryptedText + (n - RemovePadding), '\0', RemovePadding);
}

/**
 * Tests the Encrypt_Array and Decrypt_Array functions with
 * a starting message being "hello".
 */
void testFunction_AES128_Round_Trip(void) {

  // Configuration
  uint8_t finalMessage[256] = "hello!a";
  const uint8_t startMessage[256] = "hello";
  printf("%s", "Starting Message: ");
  printf("%s", finalMessage);
  printf("%s", "\nEncrypted Message: \n ");

  // Complete Cryptography Actions
  size_t length = 5;
  size_t *lengthPointer = &length;
  Encrypt_Array(finalMessage, lengthPointer);
  printf("%s", finalMessage);
  Decrypt_Array(finalMessage, length);

  // Comparison back to starting point
  if (0 == memcmp(finalMessage, startMessage, 256)) {
    printf("\nSuccessful Decryption");
  } else {
    printf("\nFailure to Decrypt, Message: ");
    printf("%s", finalMessage);
  }
}
