/*
 * aes128.h
 *
 * 	- October 15, 2025
 * 		Author : Tanishq
 * 		Log    : AES128 Encryption Task
 */                                                                            \
#ifndef ENCRYPTION_AES123_H_
#define ENCRYPTION_AES123_H_

#include "aes.h"
#include <_string.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_BYTES_MESSAGE 256

void Encrypt_Array(uint8_t *Dest);
void Decrypt_Array(uint8_t *EncryptedText);

#endif