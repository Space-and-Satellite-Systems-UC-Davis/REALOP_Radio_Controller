#include "EncFECAuth.h"
#include "Reed-Solomon/rs.h"
#include "print_scan.h"

void testFunction_FAE() {
    char nonce[224] = "HELLO TOBIAS I MAKE THE GLOBULINS";
    char enc[256] = "\0";
    char dec[256] = "\0";
    ReedSolomon rs = {224, 16};
    RSGF_construct_ReedSolomon(&rs, 224, 16);
    uint8_t memory[MAX_POLYNOMIAL_STACK_SIZE];
    rs.memory = memory;
    while (true) {
        RSGF_encode_message(&rs, nonce, enc);
        RSGF_decode_message(&rs, enc, dec, NULL, 0);
        if (strcmp(dec, nonce) == 0) break;
    }
    while (true) {
        dec[0] = '\0';
        FAEBlockData bd = FAEEncodeStream(nonce, enc, sizeof nonce, 249);
        bd = FAEDecodeStream(enc, dec, bd.nbytes, bd.block_size);
        if (strcmp(dec, nonce) == 0) break;
    }
    while (true) {
        dec[0] = '\0';
    	FAEBlockData bd = FAEEncodeStream(nonce, enc, sizeof nonce, 249);
    	enc[113] = 'g';
    	enc[117] = '?';
    	bd = FAEDecodeStream(enc, dec, bd.nbytes, bd.block_size);
    	if (strcmp(dec, nonce) == 0) break;
    }
    while (true) {
    	printMsg(":)");
    }
}
