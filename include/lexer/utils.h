/** utils.h
 *
 * @file
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 *
 * @section LICENSE
 *

 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 * Includes some utilities to printing things in the lexer.
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#define PRINT_NAME(TOKEN) printf("%d " #TOKEN " [%s]\n", get_line_number(), yytext)
#define PRINT_SPC_NAME(TOKEN) printf("%d TK_ESPECIAL [%c]\n", get_line_number(), TOKEN)

/**
 * Retrieves the line where the last token was recognized.
 *
 * @return the line number.
 */
unsigned int get_line_number(void);

#endif /* _UTILS_H_ */
