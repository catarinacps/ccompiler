/** utils.c
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

#include "parser/utils.h"

void yyerror(char const *s)
{
    fprintf(stderr, "%d: %s at %s\n", yylineno, s, yytext);
}
