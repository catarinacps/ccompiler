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

#ifdef VERBOSE
#define V_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#define V_PERROR(f_) perror((f_))
#else
#define V_PRINTF(f_, ...) ((void)0)
#define V_PERROR(f_) ((void)0)
#endif

#ifdef DEBUG
#define D_PRINTF(f_, ...) \
    fprintf(stderr, "%s:%d:%s():", __FILE__, __LINE__, __func__); \
    fprintf(stderr, (f_), ##__VA_ARGS__)
#else
#define D_PRINTF(f_, ...) ((void)0)
#endif

#endif /* _DEBUG_H_ */
