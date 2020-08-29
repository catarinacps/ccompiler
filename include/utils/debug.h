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

#ifdef DEBUG
#define D_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#define D_PERROR(f_) perror((f_))
#else
#define D_PRINTF(f_, ...) ((void)0)
#define D_PERROR(f_) ((void)0)
#endif

#endif /* _DEBUG_H_ */
