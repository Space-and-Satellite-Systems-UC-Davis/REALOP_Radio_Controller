#ifndef _ENCFECAUTH_H_
#define _ENCFECAUTH_H_
#include "Reed-Solomon/rs.h"

#define MAX_FAE_BLOCKS 256
#define FAE_ECC_SIZE 16
#define MAX_FAE_BLOCK_SIZE 256
#define FAE_DECODE_ERROR ((size_t)-1)

typedef struct FAEBlockData {
    size_t nbytes;
    size_t block_size;
} FAEBlockData;

FAEBlockData FAEEncodeStream(char *in, char *out, size_t nbytes, size_t output_block_size);
size_t FAEDecodeBlock(char *input, char *output, size_t size);

#endif // _ENCFECAUTH_H_