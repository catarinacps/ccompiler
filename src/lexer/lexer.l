/** lexer.l - Lexer specification definition
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 */

%{
#include "../../include/lexer/lexer.h"
%}

whitespace [[:blank:]]

%%

{whitespace}+ {}

%%
