/* Author: Mike Lubinets (aka mersinvald)
 * Date: 29.12.15
 *
 * Translated to C (Dennis Ritchie (Alistair E. Ritchie et al.), Bell Labs, compiled with gcc (RMS, GNU's Not Unix's Not Unix Software Foundation)) from C++ (Bjarne Stroustrup, AT&T Bell Labs) by James Knepper 4 June 2026
 * 
 * See LICENSE */

#include <string.h>
#include <stdint.h>
#include "poly.h"
#include "gf.h"
#include "rs.h"

#define MSG_CNT 3   // message-length polynomials count
#define POLY_CNT 14 // (ecc_length*2)-length polynomials count

#define MAX_GENERATOR_CACHE_SIZE 256
#define MAX_POLYNOMIAL_STACK_SIZE 8192

// template <const uint8_t msg_length,  // Message length without correction code
//           const uint8_t ecc_length>  // Length of correction code

void RSGF_construct_ReedSolomon(ReedSolomon *out, const uint8_t msg_length, const uint8_t ecc_length) {
    const uint8_t   enc_len  = msg_length + ecc_length;
    const uint8_t   poly_len = ecc_length * 2;
    uint8_t** memptr   = &out->memory;
    uint16_t  offset   = 0;

    /* Initialize first six polys manually cause their amount depends on template parameters */

    RSGF_init_polynomial(&out->polynoms[0], ID_MSG_IN, offset, enc_len, memptr);
    offset += enc_len;

    RSGF_init_polynomial(&out->polynoms[1], ID_MSG_OUT, offset, enc_len, memptr);
    offset += enc_len;

    for(uint8_t i = ID_GENERATOR; i < ID_MSG_E; i++) {
        RSGF_init_polynomial(&out->polynoms[i], i, offset, poly_len, memptr);
        offset += poly_len;
    }

    RSGF_init_polynomial(&out->polynoms[5], ID_MSG_E, offset, enc_len, memptr);
    offset += enc_len;

    for(uint8_t i = ID_TPOLY3; i < ID_ERR_EVAL+2; i++) {
        RSGF_init_polynomial(&out->polynoms[i], i, offset, poly_len, memptr);
        offset += poly_len;
    }
}

void RSGF_destruct_ReedSolomon(ReedSolomon *rs) {
    // Dummy destructor, gcc-generated one crashes program
    rs->memory = NULL;
}

/* @brief Message block encoding
 * @param *src - input message buffer      (msg_length size)
 * @param *dst - output buffer for ecc     (ecc_length size at least) */
void RSGF_encode_block(ReedSolomon *rs, const void* src, void* dst) {

    /* Generator cache, it dosn't change for one template parameters */
    static uint8_t generator_cache[MAX_GENERATOR_CACHE_SIZE] = {0};
    static bool    generator_cached = false;

    /* Allocating memory on stack for polynomials storage */
    uint8_t stack_memory[MAX_POLYNOMIAL_STACK_SIZE];
    rs->memory = stack_memory;

    const uint8_t* src_ptr = (const uint8_t*) src;
    uint8_t* dst_ptr = (uint8_t*) dst;

    struct RSGF_Polynomial *msg_in  = &rs->polynoms[ID_MSG_IN];
    struct RSGF_Polynomial *msg_out = &rs->polynoms[ID_MSG_OUT];
    struct RSGF_Polynomial *gen     = &rs->polynoms[ID_GENERATOR];

    // Weird shit, but without resetting msg_in it simply doesn't work
    RSGF_reset_polynomial(msg_in);
    RSGF_reset_polynomial(msg_out);

    // Using cached generator or generating new one
    if(generator_cached) {
        RSGF_set_polynomial(gen, generator_cache, sizeof(generator_cache), 0);
    } else {
        RSGF_find_generator_polynomial(rs);
        memcpy(generator_cache, RSGF_retreive_pointer(gen), gen->length);
        generator_cached = true;
    }

    // Copying input message to internal polynomial
    RSGF_set_polynomial(msg_in, src_ptr, rs->msg_length, 0);
    RSGF_set_polynomial(msg_out, src_ptr, rs->msg_length, 0);
    msg_out->length = msg_in->length + rs->ecc_length;

    // Here all the magic happens
    uint8_t coef = 0; // cache
    for(uint8_t i = 0; i < rs->msg_length; i++){
        coef = RSGF_retreive_pointer(msg_out)[i];
        if(coef != 0){
            for(uint32_t j = 1; j < gen->length; j++){
                RSGF_retreive_pointer(msg_out)[i+j] ^= RSGF_multiply_terms(RSGF_retreive_pointer(gen)[j], coef);
            }
        }
    }

    // Copying ECC to the output buffer
    memcpy(dst_ptr, RSGF_retreive_pointer(msg_out)+rs->msg_length, rs->ecc_length * sizeof(uint8_t));
}

/* @brief Message encoding
 * @param *src - input message buffer      (msg_length size)
 * @param *dst - output buffer             (msg_length + ecc_length size at least) */
void RSGF_encode_message(ReedSolomon *rs, const void* src, void* dst) {
    uint8_t* dst_ptr = (uint8_t*) dst;

    // Copying message to the output buffer
    memcpy(dst_ptr, src, rs->msg_length * sizeof(uint8_t));

    // Calling RSGF_encode_block to write ecc to out[ut buffer
    RSGF_encode_block(rs, src, dst_ptr+rs->msg_length);
}

bool RSGF_find_error_locator(ReedSolomon *rs, const struct RSGF_Polynomial *synd, struct RSGF_Polynomial *erase_loc, size_t erase_count) {
    struct RSGF_Polynomial *error_loc = &rs->polynoms[ID_ERRORS_LOC];
    struct RSGF_Polynomial *err_loc   = &rs->polynoms[ID_TPOLY1];
    struct RSGF_Polynomial *old_loc   = &rs->polynoms[ID_TPOLY2];
    struct RSGF_Polynomial *temp      = &rs->polynoms[ID_TPOLY3];
    struct RSGF_Polynomial *temp2     = &rs->polynoms[ID_TPOLY4];

    if(erase_loc != NULL) {
        RSGF_copy_polynomial(err_loc, erase_loc);
        RSGF_copy_polynomial(old_loc, erase_loc);
    } else {
        err_loc->length = 1;
        old_loc->length = 1;
        RSGF_retreive_pointer(err_loc)[0]  = 1;
        RSGF_retreive_pointer(old_loc)[0]  = 1;
    }

    uint8_t synd_shift = 0;
    if(synd->length > rs->ecc_length) {
        synd_shift = synd->length - rs->ecc_length;
    }

    uint8_t K = 0;
    uint8_t delta = 0;
    uint8_t index;

    for(uint8_t i = 0; i < rs->ecc_length - erase_count; i++){
        if(erase_loc != NULL)
            K = erase_count + i + synd_shift;
        else
            K = i + synd_shift;

        delta = RSGF_retreive_pointer(synd)[K];
        for(uint8_t j = 1; j < err_loc->length; j++) {
            index = err_loc->length - j - 1;
            delta ^= RSGF_multiply_terms(RSGF_retreive_pointer(err_loc)[index], RSGF_retreive_pointer(synd)[K-j]);
        }

        RSGF_append_polynomial(old_loc, 0);
    
        if(delta != 0) {
            if(old_loc->length > err_loc->length) {
                RSGF_scale_polynomial(old_loc, temp, delta);
                RSGF_scale_polynomial(err_loc, old_loc, RSGF_inverse(delta));
                RSGF_copy_polynomial(err_loc, temp);
            }
            RSGF_scale_polynomial(old_loc, temp, delta);
            RSGF_add_polynomials(err_loc, temp, temp2);
            RSGF_copy_polynomial(err_loc, temp2);
        }
    }

    uint32_t shift = 0;
    while(err_loc->length && RSGF_retreive_pointer(err_loc)[shift] == 0) shift++;

    uint32_t errs = err_loc->length - shift - 1;
    if(((errs - erase_count) * 2 + erase_count) > rs->ecc_length){
        return false; /* Error count is greater than we can fix! */
    }

    memcpy(RSGF_retreive_pointer(error_loc), RSGF_retreive_pointer(err_loc) + shift, (err_loc->length - shift) * sizeof(uint8_t));
    error_loc->length = (err_loc->length - shift);
    return true;
}

bool RSGF_find_errors(ReedSolomon *rs, const struct RSGF_Polynomial *error_loc, size_t msg_in_size) {
    struct RSGF_Polynomial *err = &rs->polynoms[ID_ERRORS];

    uint8_t errs = error_loc->length - 1;
    err->length = 0;

    for(uint8_t i = 0; i < msg_in_size; i++) {
        if(RSGF_evaluate_polynomial(error_loc, RSGF_power(2, i)) == 0) {
            RSGF_append_polynomial(err, msg_in_size - 1 - i);
        }
    }

    /* Sanity check:
     * the number of err/errata positions found
     * should be exactly the same as the length of the errata locator polynomial */
    if(err->length != errs)
        /* couldn't find error locations */
        return false;
    return true;
}

/* @brief Message block decoding
 * @param *src         - encoded message buffer   (msg_length size)
 * @param *ecc         - ecc buffer               (ecc_length size)
 * @param *msg_out     - output buffer            (msg_length size at least)
 * @param *erase_pos   - known errors positions (default NULL)
 * @param erase_count  - count of known errors (default 0)
 * @return RESULT_SUCCESS if successful, error code otherwise */
int RSGF_decode_block(ReedSolomon *rs, const void* src, const void* ecc, void* dst, uint8_t* erase_pos, size_t erase_count) {

    const uint8_t *src_ptr = (const uint8_t*) src;
    const uint8_t *ecc_ptr = (const uint8_t*) ecc;
    uint8_t *dst_ptr = (uint8_t*) dst;

    const uint8_t src_len = rs->msg_length + rs->ecc_length;
    const uint8_t dst_len = rs->msg_length;

    bool ok;

    /* Allocation memory on stack */
    uint8_t stack_memory[MAX_POLYNOMIAL_STACK_SIZE];
    rs->memory = stack_memory;

    struct RSGF_Polynomial *msg_in  = &rs->polynoms[ID_MSG_IN];
    struct RSGF_Polynomial *msg_out = &rs->polynoms[ID_MSG_OUT];
    struct RSGF_Polynomial *epos    = &rs->polynoms[ID_ERASURES];

    // Copying message to polynomials memory
    RSGF_set_polynomial(msg_in, src_ptr, rs->msg_length, 0);
    RSGF_set_polynomial(msg_in, ecc_ptr, rs->ecc_length, rs->msg_length);
    RSGF_copy_polynomial(msg_out, msg_in);

    // Copying known errors to polynomial
    if(erase_pos == NULL) {
        epos->length = 0;
    } else {
        RSGF_set_polynomial(epos, erase_pos, erase_count, 0);
        for(uint8_t i = 0; i < epos->length; i++){
            RSGF_retreive_pointer(msg_in)[RSGF_retreive_pointer(epos)[i]] = 0;
        }
    }

    // Too many errors
    if(epos->length > rs->ecc_length) return 1;

    struct RSGF_Polynomial *synd   = &rs->polynoms[ID_SYNDROMES];
    struct RSGF_Polynomial *eloc   = &rs->polynoms[ID_ERRORS_LOC];
    struct RSGF_Polynomial *reloc  = &rs->polynoms[ID_TPOLY1];
    struct RSGF_Polynomial *err    = &rs->polynoms[ID_ERRORS];
    struct RSGF_Polynomial *forney = &rs->polynoms[ID_FORNEY];

    // Calculating syndrome
    RSGF_calculate_syndromes(rs, msg_in);

    // Checking for errors
    bool has_errors = false;
    for(uint8_t i = 0; i < synd->length; i++) {
        if(RSGF_retreive_pointer(synd)[i] != 0) {
            has_errors = true;
            break;
        }
    }

    // Goto considered harmful
    if(has_errors) {
        RSGF_calculate_forney_syndromes(rs, synd, epos, src_len);
        RSGF_find_error_locator(rs, forney, NULL, epos->length);

        // Reversing syndrome
        // TODO optimize through special RSGF_Polynomial flag
        reloc->length = eloc->length;
        for(int8_t i = eloc->length-1, j = 0; i >= 0; i--, j++){
            RSGF_retreive_pointer(reloc)[j] = RSGF_retreive_pointer(eloc)[i];
        }

        // Find errors
        ok = RSGF_find_errors(rs, reloc, src_len);
        if(!ok) return 1;

        // Error happened while finding errors (so helpful :D)
        if(err->length == 0) return 1;

        /* Adding found errors with known */
        for(uint8_t i = 0; i < err->length; i++) {
            RSGF_append_polynomial(epos, RSGF_retreive_pointer(err)[i]);
        }

        // Correcting errors
        RSGF_correct_errata(rs, synd, epos, msg_in);
    }

    // Writing corrected message to output buffer
    msg_out->length = dst_len;
    memcpy(dst_ptr, RSGF_retreive_pointer(msg_out), msg_out->length * sizeof(uint8_t));
    return 0;
}

/* @brief Message block decoding
 * @param *src         - encoded message buffer   (msg_length + ecc_length size)
 * @param *msg_out     - output buffer            (msg_length size at least)
 * @param *erase_pos   - known errors positions (default NULL)
 * @param erase_count  - count of known errors (default 0)
 * @return RESULT_SUCCESS if successful, error code otherwise */
int RSGF_decode_message(ReedSolomon *rs, const void* src, void* dst, uint8_t* erase_pos, size_t erase_count) {
    const uint8_t *src_ptr = (const uint8_t*) src;
    const uint8_t *ecc_ptr = src_ptr + rs->msg_length;

    return RSGF_decode_block(rs, src, ecc_ptr, dst, erase_pos, erase_count);
}

void RSGF_find_generator_polynomial(ReedSolomon *rs) {
    struct RSGF_Polynomial *gen = rs->polynoms + ID_GENERATOR;
    RSGF_retreive_pointer(gen)[0] = 1;
    gen->length = 1;

    struct RSGF_Polynomial *mulp = rs->polynoms + ID_TPOLY1;
    struct RSGF_Polynomial *temp = rs->polynoms + ID_TPOLY2;
    mulp->length = 2;

    for(int8_t i = 0; i < rs->ecc_length; i++){
        RSGF_retreive_pointer(mulp)[0] = 1;
        RSGF_retreive_pointer(mulp)[1] = RSGF_power(2, i);

        RSGF_multiply_polynomials(gen, mulp, temp);

        RSGF_copy_polynomial(gen, temp);
    }
}

void RSGF_calculate_syndromes(ReedSolomon *rs, const struct RSGF_Polynomial *msg) {
    struct RSGF_Polynomial *synd = &rs->polynoms[ID_SYNDROMES];
    synd->length = rs->ecc_length+1;
    RSGF_retreive_pointer(synd)[0] = 0;
    for(uint8_t i = 1; i < rs->ecc_length+1; i++){
        RSGF_retreive_pointer(synd)[i] = RSGF_evaluate_polynomial(msg, RSGF_power(2, i-1));
    }
}

void RSGF_find_errata_locator(ReedSolomon *rs, const struct RSGF_Polynomial *epos) {
    struct RSGF_Polynomial *errata_loc = &rs->polynoms[ID_ERASURES_LOC];
    struct RSGF_Polynomial *mulp = &rs->polynoms[ID_TPOLY1];
    struct RSGF_Polynomial *addp = &rs->polynoms[ID_TPOLY2];
    struct RSGF_Polynomial *apol = &rs->polynoms[ID_TPOLY3];
    struct RSGF_Polynomial *temp = &rs->polynoms[ID_TPOLY4];

    errata_loc->length = 1;
    RSGF_retreive_pointer(errata_loc)[0]  = 1;

    mulp->length = 1;
    addp->length = 2;

    for(uint8_t i = 0; i < epos->length; i++){
        RSGF_retreive_pointer(mulp)[0] = 1;
        RSGF_retreive_pointer(addp)[0] = RSGF_power(2, RSGF_retreive_pointer(epos)[i]);
        RSGF_retreive_pointer(addp)[1] = 0;

        RSGF_add_polynomials(mulp, addp, apol);
        RSGF_multiply_polynomials(errata_loc, apol, temp);

        RSGF_copy_polynomial(errata_loc, temp);
    }
}

void RSGF_find_error_evaluator(ReedSolomon *rs, const struct RSGF_Polynomial *synd, const struct RSGF_Polynomial *errata_loc, struct RSGF_Polynomial *dst, uint8_t ecclen) {
    struct RSGF_Polynomial *mulp = &rs->polynoms[ID_TPOLY1];
    RSGF_multiply_polynomials(synd, errata_loc, mulp);

    struct RSGF_Polynomial *divisor = &rs->polynoms[ID_TPOLY2];
    divisor->length = ecclen+2;

    RSGF_reset_polynomial(divisor);
    RSGF_retreive_pointer(divisor)[0] = 1;

    RSGF_divide_polynomials(mulp, divisor, dst);
}

void RSGF_correct_errata(ReedSolomon *rs, const struct RSGF_Polynomial *synd, const struct RSGF_Polynomial *err_pos, const struct RSGF_Polynomial *msg_in) {
    struct RSGF_Polynomial *c_pos     = &rs->polynoms[ID_COEF_POS];
    struct RSGF_Polynomial *corrected = &rs->polynoms[ID_MSG_OUT];
    c_pos->length = err_pos->length;

    for(uint8_t i = 0; i < err_pos->length; i++)
        RSGF_retreive_pointer(c_pos)[i] = msg_in->length - 1 - RSGF_retreive_pointer(err_pos)[i];

    /* uses t_poly 1, 2, 3, 4 */
    RSGF_find_errata_locator(rs, c_pos);
    struct RSGF_Polynomial *errata_loc = &rs->polynoms[ID_ERASURES_LOC];

    /* reversing syndromes */
    struct RSGF_Polynomial *rsynd = &rs->polynoms[ID_TPOLY3];
    rsynd->length = synd->length;

    for(int8_t i = synd->length-1, j = 0; i >= 0; i--, j++) {
        RSGF_retreive_pointer(rsynd)[j] = RSGF_retreive_pointer(synd)[i];
    }

    /* getting reversed error evaluator polynomial */
    struct RSGF_Polynomial *re_eval = &rs->polynoms[ID_TPOLY4];

    /* uses T_POLY 1, 2 */
    RSGF_find_error_evaluator(rs, rsynd, errata_loc, re_eval, errata_loc->length-1);

    /* reversing it back */
    struct RSGF_Polynomial *e_eval = &rs->polynoms[ID_ERR_EVAL];
    e_eval->length = re_eval->length;
    for(int8_t i = re_eval->length-1, j = 0; i >= 0; i--, j++) {
        RSGF_retreive_pointer(e_eval)[j] = RSGF_retreive_pointer(re_eval)[i];
    }

    struct RSGF_Polynomial *X = &rs->polynoms[ID_TPOLY1]; /* this will store errors positions */
    X->length = 0;

    int16_t l;
    for(uint8_t i = 0; i < c_pos->length; i++){
        l = 255 - RSGF_retreive_pointer(c_pos)[i];
        RSGF_append_polynomial(X, RSGF_power(2, -l));
    }

    /* Magnitude polynomial
       Shit just got real */
    struct RSGF_Polynomial *E = &rs->polynoms[ID_MSG_E];
    RSGF_reset_polynomial(E);
    E->length = msg_in->length;

    uint8_t Xi_inv;

    struct RSGF_Polynomial *err_loc_prime_temp = &rs->polynoms[ID_TPOLY2];

    uint8_t err_loc_prime;
    uint8_t y;

    for(uint8_t i = 0; i < X->length; i++){
        Xi_inv = RSGF_inverse(RSGF_retreive_pointer(X)[i]);

        err_loc_prime_temp->length = 0;
        for(uint8_t j = 0; j < X->length; j++){
            if(j != i){
                RSGF_append_polynomial(err_loc_prime_temp, RSGF_subtract_terms(1, RSGF_multiply_terms(Xi_inv, RSGF_retreive_pointer(X)[j])));
            }
        }

        err_loc_prime = 1;
        for(uint8_t j = 0; j < err_loc_prime_temp->length; j++){
            err_loc_prime = RSGF_multiply_terms(err_loc_prime, RSGF_retreive_pointer(err_loc_prime_temp)[j]);
        }

        y = RSGF_evaluate_polynomial(re_eval, Xi_inv);
        y = RSGF_multiply_terms(RSGF_power(RSGF_retreive_pointer(X)[i], 1), y);

        RSGF_retreive_pointer(E)[RSGF_retreive_pointer(err_pos)[i]] = RSGF_divide_terms(y, err_loc_prime);
    }

    RSGF_add_polynomials(msg_in, E, corrected);
}

void RSGF_calculate_forney_syndromes(ReedSolomon *rs, const struct RSGF_Polynomial *synd, const struct RSGF_Polynomial *erasures_pos, size_t msg_in_size) {
    struct RSGF_Polynomial *erase_pos_reversed = &rs->polynoms[ID_TPOLY1];
    struct RSGF_Polynomial *forney_synd = &rs->polynoms[ID_FORNEY];
    erase_pos_reversed->length = 0;

    for(uint8_t i = 0; i < erasures_pos->length; i++){
        RSGF_append_polynomial(erase_pos_reversed, msg_in_size - 1 - RSGF_retreive_pointer(erasures_pos)[i]);
    }

    RSGF_reset_polynomial(forney_synd);
    RSGF_set_polynomial(forney_synd, RSGF_retreive_pointer(synd)+1, synd->length-1, 0);

    uint8_t x;
    for(uint8_t i = 0; i < erasures_pos->length; i++) {
        x = RSGF_power(2, RSGF_retreive_pointer(erase_pos_reversed)[i]);
        for(int8_t j = 0; j < forney_synd->length - 1; j++){
            RSGF_retreive_pointer(forney_synd)[j] = RSGF_multiply_terms(RSGF_retreive_pointer(forney_synd)[j], x) ^ RSGF_retreive_pointer(forney_synd)[j+1];
        }
    }
}
