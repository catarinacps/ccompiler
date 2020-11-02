/** @file location.h
 * Definition of the location of a match.
 *
 * @copyright (C) 2020 Henrique Silva
 *
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 * This header contains only the definition  of the location of a match,
 * which is basically a pair of unsigned integers.
 */

#ifndef _LOCATION_H_
#define _LOCATION_H_

#include <stdint.h>

typedef struct {
    uint32_t line;
    uint32_t column;
    uint16_t length;
} cc_location_t;

#endif /* _LOCATION_H_ */
