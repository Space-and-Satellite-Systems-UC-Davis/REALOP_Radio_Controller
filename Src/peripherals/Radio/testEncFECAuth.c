#include "EncFECAuth.h"
#include "Reed-Solomon/rs.h"
#include "print_scan.h"

void testFunction_FAE() {
    char nonce[] = "HELLO TOBIAS I MAKE THE GLOBULINS";
    char enc[256] = "\0";
    char dec[256] = "\0";
    ReedSolomon rs;
    RSGF_construct_ReedSolomon(&rs, 224, 16);
    while (true) {
        RSGF_encode_message(&rs, nonce, enc);
        RSGF_decode_message(&rs, enc, dec, NULL, 0);
        if (strcmp(dec, nonce) == 0) break;
    }
    while (true) {
        FAEBlockData bd = FAEEncodeStream(nonce, &enc[0], sizeof nonce, 249);
        bd = FAEDecodeStream(&enc[0], &dec[0], bd.nbytes, bd.block_size);
        printMsg("%c", strcmp(dec, nonce) == 0 ? 'T' : 'F');
    }
}
