#include "EncFECAuth.h"
#include "print_scan.h"

void testFunction_FAE() {
    char nonce[] = "HELLO TOBIAS I MAKE THE GLOBULINS";
    char enc[256] = "\0";
    char dec[256] = "\0";
    while (true) {
        FAEBlockData bd = FAEEncodeStream(nonce, &enc[0], sizeof nonce, 249);
        bd = FAEDecodeStream(&enc[0], &dec[0], bd.nbytes, bd.block_size);
        printMsg("%c", strcmp(dec, nonce) == 0 ? 'T' : 'F');
    }
}
