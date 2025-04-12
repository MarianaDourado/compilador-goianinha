DIGIT           [0-9]
ID              [a-z][a-z0-9]*
WHITESPACE      [\t\n\r' ']

%%

{DIGIT}+        {
                printf("Inteiro: %s\n", yytext);
                }

{DIGIT}+"."{DIGIT}*     {
                printf("Real: %s\n", yytext);
                }
for	        {printf("Achei um for\n");}
{ID}+           {
                printf("Identificador: %s\n", yytext);
                }

{WHITESPACE}+   /* Elimina espaços em branco */

.               { /* Caractere nao reconhecido */
                printf("Caractere nao reconhecido: %s\n", yytext);
                }
%%

int yywrap();

/*main() {
  yylex();
}
*/
int yywrap() {
  return 1;
}
