/*Definition Section*/
%{
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include "sym.h"
   #include "symname.h"
   
	int yylineno = 0;
%}

alphanumeral 	[A-Za-z0-9]
id        		[a-zA-z_][a-zA-z_0-9]*
float			([0-9]*[.])?[0-9]+
whitespaces  	[ \t\r\f\v]+
variable (?:\w+\s+)([a-zA-Z_][a-zA-Z0-9]+)
types ("void"|"char"|"short"|"int"|"long"|"float"|"double"|"signed"|"unsigned")

/*	REGULAR EXPRESSION SECTION	*/
%%
"#"(" "*)"include"(" "+)?((<(\\.|[^>])+>)|(\"(\\.|[^"])+\"))(" "*)					                		{return symHEADER;}
"#"(" "*)"define"(" "+){id}(" "+)(.*)(" "*) 																{return symDEFINE;}
"#"(" "*)"undef"(" "+){id}(" "*) 																			{return symUNDEF;}
("auto"|"register"|"static"|"extern"|"typedef")(" "+){id}+(.*)";"											{return STORAGE;}
{types}(" "+){id}"("(.*)(" "*)("\n"*)(.*)")"(" "*)(";"*)													{return FUNC;}
"("(" "*){types}(" "*)")"																					{return CHANGETYPE;}	
{types}(" "+){id}+(.*)";"																					{return TYPE;}	
"const"|"volatile"																							{return QUAL;}
"enum"																										{return ENUM;}
"case"																										{return CASE;}	
"default"																									{return DEFAULT;}
"if"																										{return IF;}
"switch"																									{return SWITCH;}
"else"																										{return ELSE;}
"for"																										{return FOR;}
"do"																										{return DO;}
"while"																										{return WHILE;}
"goto"																										{return GOTO;}
"continue"(" "*)";"																							{return CONTINUE;}
"break"(" "*)";"																							{return BREAK;}
("struct"|"union")(" "+){id}																				{return struct_const;}
"return"([ ]+)(.*)";"																						{return RETURN;}
"sizeof("(.*)")"																							{return SIZEOF;}
("//"(\\.|[^\n])*[\n])																						{return SINGLE_COMMENT;}
[/][*]([^*]|[*]*[^*/])*[*]+[/]("\n")                                                                        {return MULTI_COMMENT;}
"NULL"																										{return _NULL;}
{whitespaces}																								{return WHITESPACES;}
\"([^\n"]*)\"																								{return STRING;}
"'"([A-Za-z0-9]|["/".])"'"																					{return CHAR;}
{id}																										{return ID;}
<<EOF>>   																									{return -1;}
%%

/*call the yywrap function*/
int yywrap(){ return 1; }

int main(int argc, char *argv[])
{
  yyin = fopen("lexinput.cpp", "r");
  yyout = fopen("out_src.cpp","w");
  FILE* yyout_comment = fopen("out_comment.cpp","w");
  FILE* cmd_result = fopen("cmd_result.txt","w");
  symnameinit();
  
  char temp[64], code[128];
  
  /*call the yylex function.*/
  while (1)
  {
    int token = yylex();
    if (token == -1) break;
	count[token]++;
	if(token == WHITESPACES){
		//printf(yytext);
		fprintf(cmd_result, "%s", yytext);
	}else{
		printf("%s: %s\n",names[token],yytext);
		fprintf(cmd_result, "%s: %s\n",names[token],yytext);
	}
	
	
	if(token == SINGLE_COMMENT || token == MULTI_COMMENT){
		fprintf(yyout_comment, "%s", yytext);
	}else{
		fprintf(yyout, "%s", yytext);
	}
  }
  
  printf("================== 統計 =====================\n");
  fprintf(cmd_result, "================== 統計 =====================\n");
  for(int i=0;i<64;i++){
	if(count[i] != 0)
		printf("%20s 出現 %d 次\n", names[i], count[i]);
		fprintf(cmd_result, "%20s 出現 %d 次\n", names[i], count[i]);
  }

  fclose(yyout_comment);
  return 0;
}