/** @file main.c
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

#include <stdio.h>

extern int yyparse(void);
extern int yylex_destroy(void);

void* arvore = NULL;
void exporta(void* arvore);
void libera(void* arvore);

int main(void)
{
    int ret = yyparse();
    exporta(arvore);
    libera(arvore);
    arvore = NULL;
    yylex_destroy();
    return ret;
}
