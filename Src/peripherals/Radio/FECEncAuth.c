#include "FECEncAuth.h"

RadioFECBlockArray blockify(char *buffer, size_t nbytes, size_t block_size) {
    RadioFECBlockArray out;
    out.block_size = block_size;
    out.data = buffer;
    out.nblocks = (nbytes - 1) / (block_size) + 1;
}

struct RadioFECBlock EncFECAuth(RadioFECBlockArray blocks, uint64_t index) {
    
}

RadioFECBlockArray EncFECAuthStream(char *buffer, size_t nbytes, size_t block_size) {
    RadioFECBlockArray in = blockify(buffer, nbytes, block_size);
    char workpad[WORKPAD_SIZE];
    size_t new_size;
    uint64_t new_nblocks;
    for (int index = 0; index < in.nblocks; index++) {
        struct RadioFECBlock block = EncFECAuth(in, index);
    }
}