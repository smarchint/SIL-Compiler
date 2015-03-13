%{
	#include <stdio.h>
	#include "y.tab.h"
	extern int lineno;
	extern FILE * yyin;
	//why varname has been written at bottom? 
	//ans: it's blocking other RE.

%}

op ['-'|'/'|'+'|'*'|'='|'<'|'>'|'%'|'!']
id [a-zA-Z][a-zA-Z0-9]*
%%
 
[0-9]+ 			{yylval.val= atoi(yytext); return INT;}
{op}			{yylval.val= atoi(yytext);return yytext[0];}
"=="			{return  EQEQ;}
"\n"			{lineno++;}
"read" 			{return READ;}
"write" 		{return WRITE;}
"if" 			{return IF;} 
"while" 		{return WHILE;} 
"do"  			{return DO;}
"then"  		{return THEN;}
"endif"  		{return ENDIF;}
"endwhile"  	{return ENDWHILE;}
"main()"		{return MAIN;}
"begin"     	{return SILBEGIN;}
"end" 			{return END;}
"decl"			{return DECL;}
"enddecl"		{return ENDDECL;}
"bool"			{return GBOOL;}
"Integer"		{return GINT;}
"else"			{return ELSE;}	

"True"			{return TRUE;}
"False"			{return FALSE;}

"<="			{return LE;}
">="			{return GE;}
"!="			{return NE;}

"&&"			{return AND;}
"||"			{return OR;}

{id}			{	
					char * p;
					p=(char *)calloc(strlen(yytext)+1,sizeof(char));
                    strcpy(p,yytext);
                    yylval.id=p;
					return ID;
				}
[;,()[\]{}]		{return yytext[0];}
"exit();"		{return EXIT;}

.  			;
%%

int yywrap(void) {
	return 1;
	//"exit();"	{exit(EXIT_SUCCESS);}
}