%{ 
int check=0;
%}

%% 
[a-g_][a-g0-5_]*   { check=1;
printf("Identifier: %s\n", yytext);
	}
[h-zH-Z6-9]*   { check=0;
printf(" Non Identifier: %s\n", yytext);
}
" " {
return 0;}
%% 


int yywrap() { } 

int main()  
{ 
	yylex();
	return 0;
}