/** @file semantics/error.c
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
 */

#include "semantics/error.h"

void cc_semantic_error(
    cc_error_t          error,
    unsigned int        num_locations,
    /* cc_location_t */ ...)
{
    va_list ap;
    va_start(ap, num_locations);

    fputs("error: ", stderr);

    switch (error) {
    case CC_ERR_UNDECLARED:
        fputs("undeclared identifier symbol\n", stderr);
        break;
    case CC_ERR_DECLARED:
        fputs("symbol was already declared\n", stderr);
        break;
    case CC_ERR_VARIABLE:
        fputs("variable symbol used as one of another kind\n", stderr);
        break;
    case CC_ERR_VECTOR:
        fputs("vector symbol used as one of another kind\n", stderr);
        break;
    case CC_ERR_FUNCTION:
        fputs("function symbol used as one of another kind\n", stderr);
        break;
    case CC_ERR_WRONG_TYPE:
        fputs("value type incompatible to symbol type\n", stderr);
        break;
    case CC_ERR_STRING_TO_X:
        fputs("conversion of string symbol\n", stderr);
        break;
    case CC_ERR_CHAR_TO_X:
        fputs("conversion of character symbol\n", stderr);
        break;
    case CC_ERR_STRING_SIZE:
        fputs("receiving string symbol of incompatible size\n", stderr);
        break;
    case CC_ERR_MISSING_ARGS:
        fputs("function symbol received less arguments than expected\n", stderr);
        break;
    case CC_ERR_EXCESS_ARGS:
        fputs("function symbol received more arguments than expected\n", stderr);
        break;
    case CC_ERR_WRONG_TYPE_ARGS:
        fputs("declared arguments of incompatible type to received symbols\n", stderr);
        break;
    case CC_ERR_WRONG_PAR_INPUT:
        fputs("parameter to input incompatible to int or float\n", stderr);
        break;
    case CC_ERR_WRONG_PAR_OUTPUT:
        fputs("parameter to output incompatible to int or float\n", stderr);
        break;
    case CC_ERR_WRONG_PAR_RETURN:
        fputs("return statement type incompatible to the function's type\n", stderr);
        break;
    case CC_ERR_WRONG_PAR_SHIFT:
        fputs("shift parameter greater than 16\n", stderr);
        break;
    default:
        break;
    }

    /* print error lines accordingly */

    for (uint16_t i = 0; i < num_locations; i++) {
        cc_print_location(va_arg(ap, cc_location_t), stderr);
        fputs("\n", stderr);
    }

    va_end(ap);

    exit(error);
}
