/* Author: Mike Lubinets (aka mersinvald)
 * Date: 29.12.15
 *
 * Translated to C (Dennis Ritchie, Bell Labs, compiled with gcc (RMS, GNU's Not Unix's Not Unix Software Foundation)) from C++ (Bjarne Stroustrup, AT&T Bell Labs) by James Knepper 4 June 2026
 * 
 * See LICENSE */
#ifndef GF_H
#define GF_H
#include <stdint.h>
#include <string.h>
#include "poly.h"

#if !defined RS_DEBUG && !defined __CC_ARM && !defined RS_NO_ASSERT
#include <assert.h>
#else
#define assert(dummy)
#endif

/* ################################
 * # OPERATIONS OVER GALOIS FIELDS #
 * ################################ */

/* @brief Addition in Galois Fields
 * @param x - left operand
 * @param y - right operand
 * @return x + y */
uint8_t RSGF_add_terms(uint8_t x, uint8_t y);

/* ##### GF subtraction ###### */
/* @brief Subtraction in Galois Fields
 * @param x - left operand
 * @param y - right operand
 * @return x - y */
uint8_t RSGF_subtract_terms(uint8_t x, uint8_t y);

/* @brief Multiplication in Galois Fields
 * @param x - left operand
 * @param y - right operand
 * @return x * y */
uint8_t RSGF_multiply_terms(uint16_t x, uint16_t y);

/* @brief Division in Galois Fields
 * @param x - dividend
 * @param y - divisor
 * @return x / y */
uint8_t RSGF_divide_terms(uint8_t x, uint8_t y);

/* @brief X in power Y w
 * @param x     - operand
 * @param power - power
 * @return x^power */
uint8_t RSGF_power(uint8_t x, intmax_t power);

/* @brief Inversion in Galois Fields
 * @param x - number
 * @return inversion of x */
uint8_t RSGF_inverse(uint8_t x);

/* ##########################
 * # POLYNOMIALS OPERATIONS #
 * ########################## */

/* @brief Multiplication polynomial by scalar
 * @param &p    - source polynomial
 * @param &newp - destination polynomial
 * @param x     - scalar */
void
RSGF_scale_polynomial(const struct RSGF_Polynomial *p, struct RSGF_Polynomial *newp, uint16_t x);

/* @brief Addition of two polynomials
 * @param &p    - right operand polynomial
 * @param &q    - left operand polynomial
 * @param &newp - destination polynomial */
void
RSGF_add_polynomials(const struct RSGF_Polynomial *p, const struct RSGF_Polynomial *q, struct RSGF_Polynomial *newp);


/* @brief Multiplication of two polynomials
 * @param &p    - right operand polynomial
 * @param &q    - left operand polynomial
 * @param &newp - destination polynomial */
void
RSGF_multiply_polynomials(const struct RSGF_Polynomial *p, const struct RSGF_Polynomial *q, struct RSGF_Polynomial *newp);

/* @brief Division of two polynomials
 * @param &p    - right operand polynomial
 * @param &q    - left operand polynomial
 * @param &newp - destination polynomial */
void
RSGF_divide_polynomials(const struct RSGF_Polynomial *p, const struct RSGF_Polynomial *q, struct RSGF_Polynomial *newp);

/* @brief Evaluation of polynomial in x
 * @param &p - polynomial to evaluate
 * @param x  - evaluation point */
int8_t
RSGF_evaluate_polynomial(const struct RSGF_Polynomial *p, uint16_t x);

#endif /* GF_H */