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
 * !NOTE! The length pointer's value will change!
 *
 * Output: Stores encrypted message and length of message
 * back into given respective pointers.
 * @param Dest: The 256-byte message you want to encrypt.
 * @param n: A pointer that stores the address of the length of the message.
 */
void Encrypt_Array(uint8_t *PlainText, size_t *length) {
  if (*length > MAX_BYTES_AES_MESSAGE)
    return;
  else if (*length < MAX_BYTES_AES_MESSAGE && *length % AES_BLOCKLEN != 0) {
    // Calculate Padding
    unsigned int remainder = AES_BLOCKLEN - (*length % AES_BLOCKLEN);
    memset(PlainText + *length, remainder, remainder);
    // Set new length that is a multiple of 16.
    *length += remainder;
  }
    // Encrypt
    AES_init_ctx_iv(&StructofAES, key, iv);
    AES_CBC_encrypt_buffer(&StructofAES, PlainText, *length);
 
}

/**
 * Decrypts a maximum length message of 256 bytes by the AES-128 CBC method of
 * operation and stores the message
 * back into the given pointer.
 * YOU MUST USE THE LENGTH GIVEN BY THE ENCRYPT_ARRAY FUNCTION.

 * @param EncryptedText: The 256-byte message you want to decrypt.
 * @param n: Pointer to the length of the message.
 */
void Decrypt_Array(uint8_t *EncryptedText, size_t *length) {
  if (length > MAX_BYTES_AES_MESSAGE)
    return;

  // Decrypt
  AES_init_ctx_iv(&StructofAES, key, iv);
  AES_CBC_decrypt_buffer(&StructofAES, EncryptedText, length);

  // Remove Padding
  if ((EncryptedText[*length - 1]) <= 15) {
    unsigned int RemovePadding = *(EncryptedText + *length - 1);
    memset(EncryptedText + (*length - RemovePadding), '\0', RemovePadding);
    *length -= RemovePadding;
  }
}

/**
 * Tests the Encrypt_Array and Decrypt_Array functions with
 * a starting message being "hello".
 */
void testFunction_AES128_Round_Trip(void) {

  // Configuration
  uint8_t finalMessage[256] = "hello!a";
  const uint8_t startMessage[256] = "hello!a";
  printf("%s", "\nStarting Message: ");
  printf("%s", finalMessage);
  printf("%s", "\nEncrypted Message: \n ");

  // Complete Cryptography Actions
  size_t length = 7;
  size_t *lengthPointer = &length;
  Encrypt_Array(finalMessage, lengthPointer);
  printf("%s", finalMessage);
  Decrypt_Array(finalMessage, *lengthPointer);

  // Comparison back to starting point
  if (0 == memcmp(finalMessage, startMessage, 256)) {
    printf("\nSuccessful Decryption");
  } else {
    printf("\nFailure to Decrypt, Message: ");
    printf("%s", finalMessage);
  }
}
/*
 * Test the full message of 256 bytes.
*/
void testFunction_AES128_FullSize_Message_Round_Trip(void){
  uint8_t finalMessage[256] =
      "j7Gk2Lp9WxQt1mN5bV8zR4tY0uI3oP6aS9dF2gHg5jK8lZ1xC4vB7nM0qW3deR6tY9uI2oP5"
      "aS8dF1gH4jK7lZ0xC3vB6nM9qW2eR5tY8uI1oP4aS7dF0gH3jK6lZ9xC2vB5nM8qW1eR4tY7"
      "uI0oP3aS6adF9gH2jK5lZb8xC1vB4nM7qW0eR3tY6uI9oP2aS5dF8gH1jK4lZ7xC0fvB3nM6"
      "qW9eR2tY5uI8oP1aS4dF7gH0jK3lZ6xC9vB2nM5q";
  const uint8_t startMessage[256] =
      "j7Gk2Lp9WxQt1mN5bV8zR4tY0uI3oP6aS9dF2gHg5jK8lZ1xC4vB7nM0qW3deR6tY9uI2oP5"
      "aS8dF1gH4jK7lZ0xC3vB6nM9qW2eR5tY8uI1oP4aS7dF0gH3jK6lZ9xC2vB5nM8qW1eR4tY7"
      "uI0oP3aS6adF9gH2jK5lZb8xC1vB4nM7qW0eR3tY6uI9oP2aS5dF8gH1jK4lZ7xC0fvB3nM6"
      "qW9eR2tY5uI8oP1aS4dF7gH0jK3lZ6xC9vB2nM5q";

  printf("%s", "\nStarting Message: ");
  printf("%s", finalMessage);
  printf("%s", "\nEncrypted Message: \n ");

  // Complete Cryptography Actions
  size_t length = 256;
  size_t *lengthPointer = &length;
  Encrypt_Array(finalMessage, lengthPointer);
  printf("%s", finalMessage);
  Decrypt_Array(finalMessage, *lengthPointer);

  // Comparison back to starting point
  if (0 == memcmp(finalMessage, startMessage, 256)) {
    printf("\nSuccessful Decryption");
  } else {
    printf("\nFailure to Decrypt, Message: ");
    printf("%s", finalMessage);
  }
}
