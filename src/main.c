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

#include "lexer/lexer.h"
#include "lexer/tokens.h"

int main(int argc, char** argv)
{
    int token = 0;

    V_PRINTF("=> Initiating lexer...\n");

    while ((token = yylex())) {
        switch (token) {
        case '~':
        case '@':
        case '`':
        case ',':
        case ';':
        case ':':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case '+':
        case '-':
        case '*':
        case '/':
        case '<':
        case '>':
        case '=':
        case '!':
        case '&':
        case '.':
        case '%':
        case '#':
        case '^':
        case '|':
        case '$':
        case '?':
            PRINT_SPC_NAME(token);
            break;
        case TK_PR_INT:
            PRINT_NAME(TK_PR_INT);
            break;
        case TK_PR_FLOAT:
            PRINT_NAME(TK_PR_FLOAT);
            break;
        case TK_PR_BOOL:
            PRINT_NAME(TK_PR_BOOL);
            break;
        case TK_PR_CHAR:
            PRINT_NAME(TK_PR_CHAR);
            break;
        case TK_PR_STRING:
            PRINT_NAME(TK_PR_STRING);
            break;
        case TK_PR_IF:
            PRINT_NAME(TK_PR_IF);
            break;
        case TK_PR_THEN:
            PRINT_NAME(TK_PR_THEN);
            break;
        case TK_PR_ELSE:
            PRINT_NAME(TK_PR_ELSE);
            break;
        case TK_PR_WHILE:
            PRINT_NAME(TK_PR_WHILE);
            break;
        case TK_PR_DO:
            PRINT_NAME(TK_PR_DO);
            break;
        case TK_PR_INPUT:
            PRINT_NAME(TK_PR_INPUT);
            break;
        case TK_PR_OUTPUT:
            PRINT_NAME(TK_PR_OUTPUT);
            break;
        case TK_PR_RETURN:
            PRINT_NAME(TK_PR_RETURN);
            break;
        case TK_PR_CONST:
            PRINT_NAME(TK_PR_CONST);
            break;
        case TK_PR_STATIC:
            PRINT_NAME(TK_PR_STATIC);
            break;
        case TK_PR_FOREACH:
            PRINT_NAME(TK_PR_FOREACH);
            break;
        case TK_PR_FOR:
            PRINT_NAME(TK_PR_FOR);
            break;
        case TK_PR_SWITCH:
            PRINT_NAME(TK_PR_SWITCH);
            break;
        case TK_PR_CASE:
            PRINT_NAME(TK_PR_CASE);
            break;
        case TK_PR_BREAK:
            PRINT_NAME(TK_PR_BREAK);
            break;
        case TK_PR_CONTINUE:
            PRINT_NAME(TK_PR_CONTINUE);
            break;
        case TK_PR_CLASS:
            PRINT_NAME(TK_PR_CLASS);
            break;
        case TK_PR_PRIVATE:
            PRINT_NAME(TK_PR_PRIVATE);
            break;
        case TK_PR_PUBLIC:
            PRINT_NAME(TK_PR_PUBLIC);
            break;
        case TK_PR_PROTECTED:
            PRINT_NAME(TK_PR_PROTECTED);
            break;
        case TK_PR_END:
            PRINT_NAME(TK_PR_END);
            break;
        case TK_PR_DEFAULT:
            PRINT_NAME(TK_PR_DEFAULT);
            break;
        case TK_OC_LE:
            PRINT_NAME(TK_OC_LE);
            break;
        case TK_OC_GE:
            PRINT_NAME(TK_OC_GE);
            break;
        case TK_OC_EQ:
            PRINT_NAME(TK_OC_EQ);
            break;
        case TK_OC_NE:
            PRINT_NAME(TK_OC_NE);
            break;
        case TK_OC_AND:
            PRINT_NAME(TK_OC_AND);
            break;
        case TK_OC_OR:
            PRINT_NAME(TK_OC_OR);
            break;
        case TK_OC_SL:
            PRINT_NAME(TK_OC_SL);
            break;
        case TK_OC_SR:
            PRINT_NAME(TK_OC_SR);
            break;
        case TK_OC_FORWARD_PIPE:
            PRINT_NAME(TK_OC_FORWARD_PIPE);
            break;
        case TK_OC_BASH_PIPE:
            PRINT_NAME(TK_OC_BASH_PIPE);
            break;
        case TK_LIT_INT:
            PRINT_NAME(TK_LIT_INT);
            break;
        case TK_LIT_FLOAT:
            PRINT_NAME(TK_LIT_FLOAT);
            break;
        case TK_LIT_FALSE:
            PRINT_NAME(TK_LIT_FALSE);
            break;
        case TK_LIT_TRUE:
            PRINT_NAME(TK_LIT_TRUE);
            break;
        case TK_LIT_CHAR:
            PRINT_NAME(TK_LIT_CHAR);
            break;
        case TK_LIT_STRING:
            PRINT_NAME(TK_LIT_STRING);
            break;
        case TK_IDENTIFICADOR:
            PRINT_NAME(TK_IDENTIFICADOR);
            break;
        case TOKEN_ERRO:
            PRINT_NAME(TOKEN_ERRO);
            break;
        default:
            printf("<Invalid Token with code %d>\n", token);
            return 1;
            break;
        }
    }

    yylex_destroy();

    return 0;
}
