#ifndef _ENCFECAUTH_H_
#define _ENCFECAUTH_H_
#include "Reed-Solomon/rs.h"

#define MAX_FAE_BLOCKS 256
#define FAE_ECC_SIZE 16
#define MAX_FAE_BLOCK_SIZE 256

typedef struct FAEBlockData {
    size_t nbytes;
    size_t block_size;
} FAEBlockData;

/**
 * @param in            input data
 * @param out           buffer for output data, at least MAX_FAE_BLOCKS * MAX_FAE_BLOCK_SIZE in size
 * @param nbytes        number of bytes in the input data
 * @param block_size    number of bytes in each output block
 * @returns             the number of bytes in the output stream
 */
FAEBlockData FAEEncodeStream(char *in, char *out, size_t nbytes, size_t block_size);

/**
 * @param in                stream of bytes to be decoded
 * @param out               storage area for a stream of decoded bytes
 * @param nbytes            the number of bytes in the input stream
 * @param input_block_size  the size of the blocks in the input stream
 */
FAEBlockData FAEDecodeStream(char *in, char *out, size_t nbytes, size_t input_block_size);
#endif // _ENCFECAUTH_H_