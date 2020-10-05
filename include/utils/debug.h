/** debug.h
 *
 * @file
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 * Defines some utility debug macros and other interesting unrelated
 * functions.
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * All errors are defined using the 'error_t' type, as an attempt to
 * easily recognize parameters that intend to carry error codes.
 */
typedef unsigned short error_t;

#define CC_OOMEM ((error_t)128)

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
void cc_die(const char* message, error_t code);

#endif /* _DEBUG_H_ */
