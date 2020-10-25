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

/**
 * All errors  are defined using  the 'error_t'  type, as an  attempt to
 * easily recognize parameters that intend to carry error codes.
 */
typedef unsigned short error_t;

#define CC_ERR_UNDECLARED       ((error_t)10)
#define CC_ERR_DECLARED         ((error_t)11)
#define CC_ERR_VARIABLE         ((error_t)20)
#define CC_ERR_VECTOR           ((error_t)21)
#define CC_ERR_FUNCTION         ((error_t)22)
#define CC_ERR_WRONG_TYPE       ((error_t)30)
#define CC_ERR_STRING_TO_X      ((error_t)31)
#define CC_ERR_CHAR_TO_X        ((error_t)32)
#define CC_ERR_STRING_SIZE      ((error_t)33)
#define CC_ERR_MISSING_ARGS     ((error_t)40)
#define CC_ERR_EXCESS_ARGS      ((error_t)41)
#define CC_ERR_WRONG_TYPE_ARGS  ((error_t)42)
#define CC_ERR_WRONG_PAR_INPUT  ((error_t)50)
#define CC_ERR_WRONG_PAR_OUTPUT ((error_t)51)
#define CC_ERR_WRONG_PAR_RETURN ((error_t)52)
#define CC_ERR_WRONG_PAR_SHIFT  ((error_t)53)
#define CC_ERR_OOMEM            ((error_t)64)
#define CC_ERR_HASH             ((error_t)65)

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
    error_t     code);

#endif /* _UTILS_DEBUG_H_ */
