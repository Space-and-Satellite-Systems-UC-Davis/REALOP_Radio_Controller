/* Author: Mike Lubinets (aka mersinvald)
 * Date: 29.12.15
 *
 * Translated to C (Dennis Ritchie (Alistair E. Ritchie et al.), Bell Labs, compiled with gcc (RMS, GNU's Not Unix's Not Unix Software Foundation)) from C++ (Bjarne Stroustrup, AT&T Bell Labs) by James Knepper 4 June 2026
 * 
 * See LICENSE */

#ifndef RS_HPP
#define RS_HPP
#include <string.h>
#include <stdint.h>
#include "poly.h"

#if !defined RS_DEBUG && !defined __CC_ARM && !defined RS_NO_ASSERT
#include <assert.h>
#else
#define assert(dummy)
#endif

#define MSG_CNT 3   // message-length polynomials count
#define POLY_CNT 14 // (ecc_length*2)-length polynomials count

#define MAX_GENERATOR_CACHE_SIZE 256
#define MAX_POLYNOMIAL_STACK_SIZE 8192

// template <const uint8_t msg_length,  // Message length without correction code
//           const uint8_t ecc_length>  // Length of correction code

typedef struct ReedSolomon {
    // Pointer for polynomials memory on stack
    const uint8_t msg_length;
    const uint8_t ecc_length;
    uint8_t* memory;
    struct RSGF_Polynomial polynoms[MSG_CNT + POLY_CNT];
} ReedSolomon;

enum RSGF_POLY_ID {
    ID_MSG_IN = 0,
    ID_MSG_OUT,
    ID_GENERATOR,   // 3
    ID_TPOLY1,      // T for Temporary
    ID_TPOLY2,

    ID_MSG_E,       // 5

    ID_TPOLY3,     // 6
    ID_TPOLY4,

    ID_SYNDROMES,
    ID_FORNEY,

    ID_ERASURES_LOC,
    ID_ERRORS_LOC,

    ID_ERASURES,
    ID_ERRORS,

    ID_COEF_POS,
    ID_ERR_EVAL
    };

void RSGF_construct_ReedSolomon(ReedSolomon *out, const uint8_t msg_length, const uint8_t ecc_length);

void RSGF_destruct_ReedSolomon(ReedSolomon *rs);

/* @brief Message block encoding
 * @param *src - input message buffer      (msg_length size)
 * @param *dst - output buffer for ecc     (ecc_length size at least) */
void RSGF_encode_block(ReedSolomon *rs, const void* src, void* dst);

/* @brief Message encoding
 * @param *src - input message buffer      (msg_length size)
 * @param *dst - output buffer             (msg_length + ecc_length size at least) */
void RSGF_encode_message(ReedSolomon *rs, const void* src, void* dst);

bool RSGF_find_error_locator(ReedSolomon *rs, const struct RSGF_Polynomial *synd, struct RSGF_Polynomial *erase_loc, size_t erase_count);

bool RSGF_find_errors(ReedSolomon *rs, const struct RSGF_Polynomial *error_loc, size_t msg_in_size);

/* @brief Message block decoding
 * @param *src         - encoded message buffer   (msg_length size)
 * @param *ecc         - ecc buffer               (ecc_length size)
 * @param *msg_out     - output buffer            (msg_length size at least)
 * @param *erase_pos   - known errors positions (default NULL)
 * @param erase_count  - count of known errors (default 0)
 * @return RESULT_SUCCESS if successful, error code otherwise */
int RSGF_decode_block(ReedSolomon *rs, const void* src, const void* ecc, void* dst, uint8_t* erase_pos, size_t erase_count);

/* @brief Message block decoding
 * @param *src         - encoded message buffer   (msg_length + ecc_length size)
 * @param *msg_out     - output buffer            (msg_length size at least)
 * @param *erase_pos   - known errors positions (default NULL)
 * @param erase_count  - count of known errors (default 0)
 * @return RESULT_SUCCESS if successful, error code otherwise */
int RSGF_decode_message(ReedSolomon *rs, const void* src, void* dst, uint8_t* erase_pos, size_t erase_count);

void RSGF_find_generator_polynomial(ReedSolomon *rs);

void RSGF_calculate_syndromes(ReedSolomon *rs, const struct RSGF_Polynomial *msg);

void RSGF_find_errata_locator(ReedSolomon *rs, const struct RSGF_Polynomial *epos);

void RSGF_find_error_evaluator(ReedSolomon *rs, const struct RSGF_Polynomial *synd, const struct RSGF_Polynomial *errata_loc, struct RSGF_Polynomial *dst, uint8_t ecclen);

void RSGF_correct_errata(ReedSolomon *rs, const struct RSGF_Polynomial *synd, const struct RSGF_Polynomial *err_pos, const struct RSGF_Polynomial *msg_in);

void RSGF_calculate_forney_syndromes(ReedSolomon *rs, const struct RSGF_Polynomial *synd, const struct RSGF_Polynomial *erasures_pos, size_t msg_in_size);

#endif // RS_HPP
