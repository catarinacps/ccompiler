/** @file utils/debug.h
 *
 * @copyright (C) 2020 Henrique Silva
 *
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the  terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 * Defines some utility debug macros and other interesting unrelated
 * functions.
 */

#ifndef _UTILS_DEBUG_H_
#define _UTILS_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * All errors  are defined using  the 'error_t'  type, as an  attempt to
 * easily recognize parameters that intend to carry error codes.
 */
typedef uint8_t cc_error_t;

#define CC_OK                   ((cc_error_t)0)
#define CC_ERR_UNDECLARED       ((cc_error_t)10)
#define CC_ERR_DECLARED         ((cc_error_t)11)
#define CC_ERR_VARIABLE         ((cc_error_t)20)
#define CC_ERR_VECTOR           ((cc_error_t)21)
#define CC_ERR_FUNCTION         ((cc_error_t)22)
#define CC_ERR_WRONG_TYPE       ((cc_error_t)30)
#define CC_ERR_STRING_TO_X      ((cc_error_t)31)
#define CC_ERR_CHAR_TO_X        ((cc_error_t)32)
#define CC_ERR_STRING_SIZE      ((cc_error_t)33)
#define CC_ERR_MISSING_ARGS     ((cc_error_t)40)
#define CC_ERR_EXCESS_ARGS      ((cc_error_t)41)
#define CC_ERR_WRONG_TYPE_ARGS  ((cc_error_t)42)
#define CC_ERR_WRONG_PAR_INPUT  ((cc_error_t)50)
#define CC_ERR_WRONG_PAR_OUTPUT ((cc_error_t)51)
#define CC_ERR_WRONG_PAR_RETURN ((cc_error_t)52)
#define CC_ERR_WRONG_PAR_SHIFT  ((cc_error_t)53)
#define CC_ERR_OOMEM            ((cc_error_t)64)
#define CC_ERR_HASH             ((cc_error_t)65)

#ifdef VERBOSE
#define V_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#define V_PERROR(f_) perror((f_))
#else
#define V_PRINTF(f_, ...) ((void)0)
#define V_PERROR(f_) ((void)0)
#endif

#ifdef DEBUG
#define D_PRINTF(f_, ...)                                         \
    fprintf(stderr, "%s:%d:%s():", __FILE__, __LINE__, __func__); \
    fprintf(stderr, (f_), ##__VA_ARGS__)
#else
#define D_PRINTF(f_, ...) ((void)0)
#endif

/**
 * Gracefully leaves a message before dying with the given error code.
 *
 * @param message the string literal to print.
 * @param code the error code to throw.
 */
void cc_die(
    char const* message,
    cc_error_t  code);

#endif /* _UTILS_DEBUG_H_ */
