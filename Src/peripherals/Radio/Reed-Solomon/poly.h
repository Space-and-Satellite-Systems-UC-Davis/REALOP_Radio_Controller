/* Author: Mike Lubinets (aka mersinvald)
 * Date: 29.12.15
 * 
 * Translated to C (Dennis Ritchie, Bell Labs, compiled with gcc (RMS, GNU's Not Unix's Not Unix Software Foundation)) from C++ (Bjarne Stroustrup, AT&T Bell Labs) by James Knepper 4 June 2026
 *
 * See LICENSE */

#ifndef POLY_H
#define POLY_H
#include <stdint.h>
#include <string.h>
#include "globals.h"

#if !defined RS_DEBUG && !defined __CC_ARM && !defined RS_NO_ASSERT
#include <assert.h>
#else
#define assert(dummy)
#endif

struct RSGF_Polynomial {
    uint8_t length;
    uint8_t   _id;
    uint8_t   _size;    // Size of reserved memory for this polynomial
    uint16_t  _offset;  // Offset in memory
    uint8_t** _memory;  // Pointer to pointer to memory
};

struct RSGF_Polynomial RSGF_construct_polynomial();

struct RSGF_Polynomial RSGF_construct_detailed_polynomial(uint8_t id, uint16_t offset, uint8_t size);

// Returns pointer to memory of this polynomial
uint8_t* RSGF_retreive_pointer(const struct RSGF_Polynomial *polynomial);
    
/* @brief RSGF_append_polynomial number at the end of polynomial
 * @param num - number to append
 * @return false if polynomial can't be stretched */
bool RSGF_append_polynomial(struct RSGF_Polynomial *polynomial, uint8_t num);

/* @brief Polynomial initialization */
void RSGF_init_polynomial(struct RSGF_Polynomial *polynomial, uint8_t id, uint16_t offset, uint8_t size, uint8_t** memory_ptr);

/* @brief Polynomial memory zeroing */
void RSGF_reset_polynomial(struct RSGF_Polynomial *polynomial);

/* @brief Copy polynomial to memory
 * @param src    - source byte-sequence
 * @param size   - size of polynomial
 * @param offset - write offset */
void RSGF_set_polynomial(struct RSGF_Polynomial *polynomial, const uint8_t* src, uint8_t len, uint8_t offset);

#define poly_max(a, b) ((a > b) ? (a) : (b))

void RSGF_copy_polynomial(struct RSGF_Polynomial *dest, const struct RSGF_Polynomial* src);

// uint8_t id(struct RSGF_Polynomial *polynomial) {
//     return polynomial->_id;
// }

// uint8_t size(struct RSGF_Polynomial *polynomial) {
//     return polynomial->_size;
// }

#endif // POLY_H