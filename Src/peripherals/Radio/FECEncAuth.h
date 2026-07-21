#include "Reed-Solomon/rs.h"

#define WORKPAD_SIZE 65536

struct RadioFECBlock {
    char *data;
    size_t block_size;
};

typedef struct RadioFECBlockArray {
    char *data; // the actual bytes
    size_t block_size; // the size of each FEC-Enc-Auth block
    uint64_t nblocks; // the number of blocks (this times the block size is the number of bytes)
} RadioFECBlockArray;