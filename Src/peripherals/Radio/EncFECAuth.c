#include "EncFECAuth.h"
#include "Reed-Solomon/rs.h"
#include "secure_comm/aes128.h"



/* Encrypted bytes per block (multiple of 16); the rest of the block is parity. 0 = unusable size. */
static size_t FAEEncSize(size_t x) {
    if (x > 255 || x <= FAE_ECC_SIZE) return 0;
    size_t p = ((x - FAE_ECC_SIZE) / AES_BLOCKLEN) * AES_BLOCKLEN;
    if (p == 0 || p > MAX_BYTES_AES_MESSAGE || p > MAX_FAE_BLOCK_SIZE) return 0;
    return p;
}

/* Message bytes carried by a full block. A block with fewer bytes is the last one. */
size_t FAEPayloadSize(size_t x) {
    size_t p = FAEEncSize(x);
    return p ? p - 1 : 0;
}

/**
 * @param in                 data to send
 * @param out                must hold (nbytes / FAEPayloadSize(output_block_size) + 1) * output_block_size bytes
 * @param nbytes             number of bytes in `in`
 * @param output_block_size  size of every block on the wire (max 255)
 * @returns                  block_size = output_block_size, nbytes = total bytes written to out
 *                           (both 0 on error). Transmit out in block_size pieces.
 */
FAEBlockData FAEEncodeStream(char *in, char *out, size_t nbytes, size_t output_block_size) {
    FAEBlockData bd = {0};
    uint8_t w[256];

    size_t p = FAEEncSize(output_block_size);
    if (p == 0) return bd;

    size_t payload = p - 1;
    size_t nblocks = nbytes / payload + 1;

    for (size_t i = 0; i < nblocks; i++) {
        size_t n = nbytes - i * payload;
        if (n > payload) n = payload;

        w[0] = (uint8_t)n;
        memcpy(w + 1, in + i * payload, n);
        memset(w + 1 + n, 0, payload - n);

        if (AES_Encrypt_Blocks(w, p) != 0) return (FAEBlockData){0};

        ReedSolomon rs = {p, output_block_size - p};                      /* fresh state per block */
        RSGF_construct_ReedSolomon(&rs, p, output_block_size - p);
        RSGF_encode_message(&rs, (char *)w, out + i * output_block_size);
    }

    bd.block_size = output_block_size;
    bd.nbytes     = nblocks * output_block_size;
    return bd;
}

/**
 * @param input   one received block (exactly `size` bytes, not modified)
 * @param output  receives the decoded message bytes; must hold FAEPayloadSize(size) bytes
 * @param size    size of the received block
 * @returns       number of message bytes written to output,
 *                or FAE_DECODE_ERROR if the block is uncorrectable or invalid
 */
size_t FAEDecodeBlock(char *input, char *output, size_t size) {
    uint8_t w[256];

    size_t p = FAEEncSize(size);
    if (p == 0) return FAE_DECODE_ERROR;

    ReedSolomon rs = {p, size - p};
    RSGF_construct_ReedSolomon(&rs, p, size - p);
    if (RSGF_decode_message(&rs, input, (char *)w, NULL, 0) < 0) return FAE_DECODE_ERROR;

    if (AES_Decrypt_Blocks(w, p) != 0) return FAE_DECODE_ERROR;

    size_t n = w[0];
    if (n > p - 1) return FAE_DECODE_ERROR;
    memcpy(output, w + 1, n);
    return n;
}