%{
#include<stdio.h> 
%}

%% 

\n {
	printf("Token and Lexeme: <newline>\n");
	}

[a-z]+ {
	printf("Token: STRING; Lexeme: %s\n", yytext);
	}

"Reverse" {
	printf("Token : REVERSE; Lexeme: Reverse\n");
	}

"#" {
	printf("Token and Lexeme: %s\n", yytext);
}

[()] {
	printf("Token and Lexeme: %s\n", yytext);
}

[a-z|A-Z]+ {
	printf("ERROR\n");
}

("!"|"@"|"$"|"&"|"?"|",") {
	printf("ERROR\n");
}

%%

int yywrap(){}
int main()
{
yylex();
return 0;
}