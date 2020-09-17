/** main.c
 *
 * @file
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 */

#include <stdio.h>

#include "parser/parser.tab.h"
#include "lexer/scanner.h"

int main(void)
{
    int ret = yyparse();

    yylex_destroy();

    return ret;
}
