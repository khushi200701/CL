%{
#include<stdio.h>
int isMulti = 0;
int blank_lines = 0;
int code_lines = 0;
int comment_lines = 0;
%}

%%

^[ \t]*\n { if(!isMulti) blank_lines++; }

^[ \t]*"/*"(.*)"*/"\n { comment_lines++;  }

^[ \t]*"/*"[^(*\/)\n]*\n { isMulti = 1; }

(.*)"*/"\n {
        isMulti = 0;
        comment_lines++;
}

(.*)\n {
        if(!isMulti) code_lines++;
}

%%

int yywrap(void) {
        return 1;
}

void main(int argc, char* argv[]){
        if(argc == 2){
                yyin = fopen(argv[1],"r");
        }
        yylex();
        printf("No. of blank lines: %d\n",blank_lines);
        printf("No. of code lines: %d\n",code_lines);
        printf("Total No. of comments: %d\n",comment_lines);
}