%{ 
int check=0;
%}

%% 
[a-g_][a-g0-5_]*   { check=1;}
" " {return 0;}
%% 


int yywrap() { } 

int main()  
{ 
	yylex();
	if(check==1)
		printf(" It is an Identifier: ");
	return 0;
   } 