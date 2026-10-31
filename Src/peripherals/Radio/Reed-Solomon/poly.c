/* Author: Mike Lubinets (aka mersinvald)
 * Date: 29.12.15
 * 
 * Translated to C (Dennis Ritchie, Bell Labs, compiled with gcc (RMS, GNU's Not Unix's Not Unix Software Foundation)) from C++ (Bjarne Stroustrup, AT&T Bell Labs) by James Knepper 4 June 2026
 *
 * See LICENSE */

#include <stdint.h>
#include <string.h>
#include "globals.h"

struct RSGF_Polynomial {
    uint8_t length;
    uint8_t   _id;
    uint8_t   _size;    // Size of reserved memory for this polynomial
    uint16_t  _offset;  // Offset in memory
    uint8_t** _memory;  // Pointer to pointer to memory
};

struct RSGF_Polynomial RSGF_construct_polynomial() {
    struct RSGF_Polynomial out;
    out.length = 0;
    out._memory = NULL;
    return out;
}

struct RSGF_Polynomial RSGF_construct_detailed_polynomial(uint8_t id, uint16_t offset, uint8_t size) {
        struct RSGF_Polynomial out;
        out.length = 0;
        out._id = id;
        out._size = size;
        out._offset = offset;
        out._memory = NULL;
        return out;
}

// Returns pointer to memory of this polynomial
uint8_t* RSGF_retreive_pointer(const struct RSGF_Polynomial *polynomial) {
    return (*polynomial->_memory) + polynomial->_offset;
}
    
/* @brief RSGF_append_polynomial number at the end of polynomial
 * @param num - number to append
 * @return false if polynomial can't be stretched */
bool RSGF_append_polynomial(struct RSGF_Polynomial *polynomial, uint8_t num) {
    if (polynomial->length+1 < polynomial->_size) return false;
    RSGF_retreive_pointer(polynomial)[polynomial->length++] = num;
    return true;
}

/* @brief Polynomial initialization */
void RSGF_init_polynomial(struct RSGF_Polynomial *polynomial, uint8_t id, uint16_t offset, uint8_t size, uint8_t** memory_ptr) {
    polynomial->_id     = id;
    polynomial->_offset = offset;
    polynomial->_size   = size;
    polynomial->length  = 0;
    polynomial->_memory = memory_ptr;
}

/* @brief Polynomial memory zeroing */
void RSGF_reset_polynomial(struct RSGF_Polynomial *polynomial) {
    memset((void*)RSGF_retreive_pointer(polynomial), 0, polynomial->_size);
}

/* @brief Copy polynomial to memory
 * @param src    - source byte-sequence
 * @param size   - size of polynomial
 * @param offset - write offset */
void RSGF_set_polynomial(struct RSGF_Polynomial *polynomial, const uint8_t* src, uint8_t len, uint8_t offset) {
    memcpy(RSGF_retreive_pointer(polynomial)+offset, src, len * sizeof(uint8_t));
    polynomial->length = len + offset;
}

#define poly_max(a, b) ((a > b) ? (a) : (b))

void RSGF_copy_polynomial(struct RSGF_Polynomial *dest, const struct RSGF_Polynomial* src) {
    dest->length = poly_max(dest->length, src->length);
    RSGF_set_polynomial(dest, RSGF_retreive_pointer(src), dest->length, 0);
}

// uint8_t id(struct RSGF_Polynomial *polynomial) {
//     return polynomial->_id;
// }

// uint8_t size(struct RSGF_Polynomial *polynomial) {
//     return polynomial->_size;
// }