%{
#include "calc.tab.h" 
%}
DIGIT           [0-9]
WHITESPACE      [\t' '\n\r]


%%

{DIGIT}+        {
                    yylval=atoi(yytext);
                    
                    return (NUMERO);
                }

"*"             {
                    printf("%s\n", yytext);
                    return(MULT);
                }

"-"             {
                    
                    return(MENOS);
                }

"/"             {
                    return(DIV);
                   
                }

"+"             { 
                    
                   
                    return(MAIS);    
                }

"("             {
                   
                    return(ABREPAREN);
                }

")"            {
                    
                    return(FECHAPAREN);
               }
WHITESPACE+     { 
                    return (WHITESPACE);
                }
.               { /* Caractere nao reconhecido */
                    printf("Caractere nao reconhecido: %s\n", yytext);
                }
%%

int yywrap();

int yywrap() {
  return 1;
}
