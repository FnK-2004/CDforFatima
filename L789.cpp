#include <iostream>
#include <cctype>   // for isspace

using namespace std;

int curr = 0; 
char str[100]; 

void Program();
void declaration();
void id_list();
void id();
void statement_list();
void statement();
void assign_stat();
void expn();
void term();
void factor();
void decision_stat();
void match(char expected);
void ignore_space();
void ignore_newline();
void invalid();
void valid();

int main() {
    cout<<"Enter the code (end with $): ";
    cin.getline(str, sizeof(str), '#');        
    Program(); 
    if (str[curr] == '$') {
        valid(); 
    } else {
        invalid(); 
    }
    return 0;
}

void Program() {
    ignore_newline();
    if (str[curr] == 'm') {
        match('m');
        match('a');
        match('i');
        match('n');
        match('(');
        match(')');
        ignore_newline();
        // Parse declaration / statement list / ??
        if (str[curr] == '{') {
            match('{');
            ignore_newline();
            if (str[curr] == 'i') {
                declaration();
            }
            ignore_newline();
            while (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c' ) {
                statement_list();
            }
            ignore_newline();
            match('}');
        } else {
            invalid();
        }
    } else {
        invalid();
    }
}

void declaration() {
    // Parse int id_list / ??
    if (str[curr] == 'i') {
        match('i');
        match('n');
        match('t');
        curr++;
        id_list();
        // Make the semicolon optional
        if (str[curr] == ';') {
            match(';');
        }
    }
}

void id_list() {
    ignore_space();
    // Parse id / id, id_list
    if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c') {
        id();
        if (str[curr] == ',') {
            match(',');
            id_list();
        }
    }
}

void id() {
    // Parse a / b / c
    ignore_space();
    if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c') {
        match(str[curr]);
        ignore_space();
    }
}

void statement_list() {
    // Parse statement statement_list / ??
    if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c') {
        statement();
        statement_list();
    } else if (str[curr] == '}' || str[curr] == '$') {
        return;
    }
}

void statement() {
    // Parse assign_stat; / decision_stat
    if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c') {
        assign_stat();
        match(';');
        ignore_newline();
    }
}

void assign_stat() {
    ignore_newline();// Parse id=num/expn
    if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c') {
        id();
        match('=');
        expn();
    }
}
void expn() {
    // Parse term
    ignore_space();
    if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c' || str[curr] == '(' || (str[curr] >= '0' && str[curr] <= '9')) {
        ignore_space();
        term();
        ignore_space();
        if (str[curr] == '+') {
            match('+');
            ignore_space();
            expn();
        }
    }
}

void term() {
    // Parse factor
    ignore_space();
    if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c' || str[curr] == '(' || (str[curr] >= '0' && str[curr] <= '9')) {
        ignore_space();
        factor();
        ignore_space();
        // Optionally parse * term
        if (str[curr] == '*') {
            match('*');
            ignore_space();
            term();
        }
    }
}

void factor() {
    // Parse (expn) / id / num
    ignore_space();
    if (str[curr] == '(') {
        match('(');
        ignore_space();
        expn();
        ignore_space();
        match(')');
        ignore_space();
    }
    else if (str[curr] == 'a' || str[curr] == 'b' || str[curr] == 'c') {
        id();
    } else if (str[curr] >= '0' && str[curr] <= '9') {
        // Numeric constant (can be multiple digits)
        while (str[curr] >= '0' && str[curr] <= '9') {
            curr++;
        }
    } else {
        invalid();
    }
}


void match(char expected) {
    if (str[curr] == expected) {
        curr++;
    } else {
        invalid();
    }
}

void invalid() {
    cout<<"\n---------INVALID!---------\n";
    exit(0);
}

void valid() {
    cout<<"\n---------VALID!---------\n";
    exit(0);
}

void ignore_space(){
    while (isspace(str[curr])) {
        curr++;}
}

void ignore_newline(){        //ignore newline and space
    while (isspace(str[curr]) || str[curr]=='\n') {
        curr++;
    }
}

/*
main(){
int a,c;
a=3+4;
a=6;
}$#

main(){
int a,c;
a=3+4;
a=6;
if (a+b){a=4;}
}$#
*/

