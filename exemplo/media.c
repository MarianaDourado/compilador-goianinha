%{
    #include<stdio.h>
    #include<stdlib.h>
%}
dgt [0-9]
%%
{dgt}+ return atoi(yytext);
%%
void main(){
    int val, total=0, n=0;
    while((val = yylex()) > 0){
        total += val;
        n++;
    }
    if(n>0) printf("media = %d\n", total/n);
}