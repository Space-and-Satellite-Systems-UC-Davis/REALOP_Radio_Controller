#include "EncFECAuth.h"
#include "Reed-Solomon/rs.h"
#include "secure_comm/aes128.h"

size_t FAEEncodeBlock(char *input, char *output, uint64_t index, size_t block_size, size_t end_size, char *workpad) {
    if (end_size == 0) memcpy(workpad, input + block_size * index, block_size);
    else {
        memcpy(workpad, input + block_size * index, end_size);
        memset(workpad + block_size * index + end_size, 0, block_size - end_size);
    }
    size_t length = block_size;
    Encrypt_Array(workpad, &length);
    // TODO if needed: separate authentication (e.g. append a shared private key to result in a workpad and hash, then appent hash to message)
    ReedSolomon rs = {length, FAE_ECC_SIZE};
    RSGF_construct_ReedSolomon(&rs, length, FAE_ECC_SIZE);
    length += rs.ecc_length;
    RSGF_encode_message(&rs, workpad, output + index*length);
    return length;
}

/**
 * @param in                    input data
 * @param out                   buffer for output data, at least MAX_FAE_BLOCKS * MAX_FAE_BLOCK_SIZE in size
 * @param nbytes                number of bytes in the input data
 * @param output_block_size     number of bytes in each output block
 * @returns                     the number of bytes in the output stream
 */
FAEBlockData FAEEncodeStream(char *in, char *out, size_t nbytes, size_t output_block_size) {
    FAEBlockData block_data;
    char workpad[MAX_FAE_BLOCK_SIZE];

    size_t input_block_size = output_block_size - FAE_ECC_SIZE;
    input_block_size = ((input_block_size / AES_BLOCKLEN) * AES_BLOCKLEN);
    uint64_t nblocks = (nbytes - 1) / input_block_size + 1;
    for (int index = 0; index < nblocks - 1; index++) {
        FAEEncodeBlock(in, out, index, input_block_size, 0, &workpad[0]);
    }
    output_block_size = FAEEncodeBlock(in, out, nblocks - 1, input_block_size, nbytes % input_block_size, &workpad[0]);
    block_data.block_size = output_block_size;
    block_data.nbytes = output_block_size * nblocks;
    return block_data;
}

size_t FAEDecodeBlock(char *input, char *output, uint64_t index, size_t block_size, char *workpad) {
    size_t length;
    length = block_size;
    ReedSolomon rs = {length - FAE_ECC_SIZE, FAE_ECC_SIZE};
    RSGF_construct_ReedSolomon(&rs, length - FAE_ECC_SIZE, FAE_ECC_SIZE);
    RSGF_decode_message(&rs, output + index*length, workpad, NULL, 0);
    length -= FAE_ECC_SIZE;
    // TODO if needed: check authentication (e.g. append a shared private key to contents in workpad and hash, check that hash matches)
    Decrypt_Array(workpad, &length);
    memcpy(output, workpad, length);
    return length;
}

/**
 * @param in                stream of bytes to be decoded
 * @param out               storage area for a stream of decoded bytes
 * @param nbytes            the number of bytes in the input stream
 * @param input_block_size  the size of the blocks in the input stream
 */
FAEBlockData FAEDecodeStream(char *in, char *out, size_t nbytes, size_t input_block_size) {
    FAEBlockData block_data;
    char workpad[MAX_FAE_BLOCK_SIZE];
    size_t output_block_size;

    uint64_t nblocks = (nbytes - 1) / input_block_size + 1;
    for (int index = 0; index < nblocks; index++) {
        output_block_size = FAEDecodeBlock(in, out, index, input_block_size, workpad);
    }
    block_data.block_size = output_block_size;
    block_data.nbytes = output_block_size * nblocks;
    return block_data;
}
