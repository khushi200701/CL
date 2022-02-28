/*   declarations   */


%{
#include <stdio.h>
#include <string.h>
int yylex(void);
void yyerror(char *);
int yydebug=0;   /*  set to 1 if using with yacc's debug/verbose flags   */
char *reverse(char *);
%}

%union {
    /*int iValue;*/
    char *str;
};

%token  <str>  STRING
%token  <str>  REVERSE
%type  <str>  start
%type  <str>  expr
%left '#'
%start  start



%%       /*   rules section. I have given the coversion of the production rules S->E|\epsilon for your referrence. You need to write it for the rest prodctions.   */


start    :    start expr  '\n'        {  printf("%s\n", $2);   }
	 |    start '\n' { } 
         |         /*  allow "empty" expression  */           {     }
         ;

expr     :    STRING    {$$ = $1;}
         |    expr '#' expr  { char* s = malloc(sizeof(char)*(strlen($1) + strlen($3)+1));
	     		       strcpy(s,$1);
		               strcat(s,$3);
		               $$ = s;}
	 |    REVERSE '(' STRING ')' { char* s1 = malloc(sizeof(char)*(strlen($3)));
					s1=reverse($3);
					$$ = s1;}
         ;


%%      /*   programs   */


char *reverse(char *str1)
/*  Reverse the string  str1.
*/
{
   int length, c;
   char *begin, *end, temp;
 
   length = strlen(str1);
   begin  = str1;
   end    = str1;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
   return str1; 
}



int main(void) {
    yyparse();
    return 0;
}

