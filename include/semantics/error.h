/** @file semantics/error.h
 *
 * @brief Semantic error functions.
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
 * Functions that  are intended to  show pretty error messages  and then
 * crash the program gracefully.
 */

#ifndef _SEMANTICS_ERROR_H_
#define _SEMANTICS_ERROR_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#include "lexer/location.h"
#include "lexer/tools.h"
#include "utils/debug.h"

/* --------------------------------------------------------------------------- */
/* Function prototypes: */

/**
 * Throws a semantic error, complete  with locations and an explanation.
 * The function can receive zero or more locations and, therefore, print
 * their lines and underline correctly.
 *
 * @param error the error class to be returned.
 * @param num_locations number of locations to be read from the elipse.
 * @param elipse locations to print as well.
 */

void cc_semantic_error(
    cc_error_t          error,
    unsigned int        num_locations,
    /* cc_location_t */ ...);

#endif /* _SEMANTICS_ERROR_H_ */
