%{
    #include<bits/stdc++.h>
    using namespace std;
%}
dgt [0-9]
%%
{dgt}+ return atoi(yytext);
%%
int main(){
    int val, total=0, n=0;
    while((val = yylex()) > 0){
        total += val;
        n++;
    }
    if(n>0) cout << "media = " << total/n << "\n";
    return 0;
}