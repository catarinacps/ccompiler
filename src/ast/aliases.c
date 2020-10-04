/** aliases.c
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

#include "ast/aliases.h"

void exporta(void* raiz)
{
    cc_print_ast((cc_ast_t*)raiz);

    return;
}

void libera(void* raiz)
{
    cc_free_ast((cc_ast_t*)raiz);

    if (yylinebuf != NULL) {
        free(yylinebuf);
        yylinebuf_len = 0;
    }

    return;
}
