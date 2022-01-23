%{
#include<stdio.h>
int total_lines = 0;
int isMulti = 0;
int keywords = 0;
int braces = 0;
int assignment = 0;
%}

Keyword int|char|float|void|for|do|while|if|else|return|auto|break|const|continue

%%

\n { total_lines++; }

^[ \t]*"/*"(.*)"*/" {  }

^[ \t]*"/*"[^(\/*)\n]* { isMulti = 1; }

(.*)"*/" { isMulti = 0; }

[ \t]*{Keyword}/" " {
        if(!isMulti){
                keywords++;
        } 
}

[{}()] {
        if(!isMulti) {
                braces++;
        }
}

= { 
        if(!isMulti) {
                assignment++;
        }
}

. ;

%%

int yywrap(void) {
        return 1;
}

void main(int argc, char* argv[]){
        if(argc == 2){
                yyin = fopen(argv[1],"r");
        }
        yylex();
        printf("No. of braces: %d\n",braces);
        printf("No. of keywords: %d\n",keywords);
        printf("No. of assignments: %d\n",assignment);
}