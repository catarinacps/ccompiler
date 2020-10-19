/** @file types.h
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
 * Header with the definition of all types of the language.
 */

#ifndef _TYPES_H_
#define _TYPES_H_

typedef enum {
    cc_type_string,
    cc_type_float,
    cc_type_int,
    cc_type_char,
    cc_type_bool
} cc_type_t;

#endif /* _TYPES_H_ */
