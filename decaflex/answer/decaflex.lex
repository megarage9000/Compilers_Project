
%{

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

string found_whitespace = "";
string found_comment = "";
string found_string = "";


// Error source here:
// https://people.cs.aau.dk/~marius/sw/flex/Advanced-Use-of-Flex.html (TODO: look at this!)
// https://stackoverflow.com/questions/656703/how-does-flex-support-bison-location-exactly#comment8854591_5811596

int prev_line_column = 1;
int prev_line_position = 1;
int line_position = 1;
int line_column = 1;

void printError(std::string error){
  std::cout << error << std::endl;
  std::cout << "Lexical error: line " << prev_line_position << ", position = " << prev_line_column << std::endl;
}

// Updating line position
static void update_position() {
  int len = yyleng;
  prev_line_column = line_column;
  prev_line_position = line_position;
  for(int i = 0; i < len; i++){
    if(yytext[i] == '\n'){
      prev_line_column = line_column;
      prev_line_position = line_position;
      line_column = 1;
      line_position++;
    }
    else{
      line_column++;
    }
  }
}

#define YY_USER_ACTION  update_position();

%}

char_literal [^\\']
escaped_char \\(n|r|t|v|f|a|b|\\|'|\") 
not_whitespace [^\t\r\v\f\n ]
whitespace [\t\r\v\f\n ]

%x COMMENT
%x STRING

%%
  /*
    Pattern definitions for all tokens
  */
func                       { return 1; }
int                        { return 2; }
package                    { return 3; }
\{                         { return 4; }
\}                         { return 5; }
\(                         { return 6; }
\)                         { return 7; }
  /* 
    Identifier 
  */
[a-zA-Z\_][a-zA-Z\_0-9]*  { return 8; }
  /* 
    Whitespace rules 
    - For all whitespaces that do have following whitespaces, don't return
    - For all whitespaces that do not have following whitespaces, return
  */
\t/{whitespace}                  { found_whitespace.append("\\t");}
\r/{whitespace}                  { found_whitespace.append("\\r");}
\v/{whitespace}                  { found_whitespace.append("\\v");}
\f/{whitespace}                  { found_whitespace.append("\\f");}
" "/{whitespace}                 { found_whitespace.append(" ");}
\t/{not_whitespace}                  { found_whitespace.append("\\t"); return 9;}
\r/{not_whitespace}                  { found_whitespace.append("\\r"); return 9;}
\v/{not_whitespace}                  { found_whitespace.append("\\v"); return 9;}
\f/{not_whitespace}                  { found_whitespace.append("\\f"); return 9;}
" "/{not_whitespace}                 { found_whitespace.append(" "); return 9;}
\n                                   { found_whitespace.append("\\\\n"); return 9;}
  /*
    Comment rules
  */
\/\/                  { found_comment.append("/"); found_comment.append("/"); BEGIN COMMENT; }
<COMMENT>.*           { found_comment.append(yytext);}
<COMMENT>\n           { found_comment.append("\\\\n"); BEGIN INITIAL; return 10;}
  /*
    Binary operations rules
  */
&&                          { return 11; }
=                           { return 12; }
==                          { return 13; }
\>=                         { return 14; }
\>                          { return 15; }
\<\<                        { return 16; }
\<=                         { return 17; }
\<                          { return 18; }
"-"                         { return 19; }
%                           { return 20; }
\*                          { return 21; }
!=                          { return 22; }
\|\|                        { return 23; }
\+                          { return 24; }
\>\>                        { return 25; }
\/                          { return 26;}
  /*
    Semicolon Rules
  */
;                           { return 27; }
  /*
    Character Literals Rules
  */
"'"({char_literal}|{escaped_char})"'"    { return 28; }
  /*
    String Rules
    - Use state to track escape sequences and newlines
  */
\"                          { found_string.append(yytext); BEGIN STRING; }
<STRING>\"                  { found_string.append(yytext); BEGIN INITIAL; return 29; }    
<STRING>\\/([^nrtvfab\\'\"]+|\n)       {printError("ERROR: unexpected escape sequence in string constant"); BEGIN INITIAL; found_string =""; return -1;}       
<STRING>\n                        {printError("ERROR: newline in string constant"); BEGIN INITIAL;  found_string =""; return -1;}    
<STRING>{char_literal}       {found_string.append(yytext);}
<STRING>{escaped_char}       {found_string.append("\\"); found_string.append(yytext);}
  /*
    EOF?
  */
.                          { cerr << "Error: unexpected character in input" << endl; return -1; }
%%

int main () {
  int token;
  string lexeme;
  while ((token = yylex())) {
    if (token > 0) {
      lexeme.assign(yytext);
      switch(token) {
        case 1: cout << "T_FUNC " << lexeme << endl; break;
        case 2: cout << "T_INT " << lexeme << endl; break;
        case 3: cout << "T_PACKAGE " << lexeme << endl; break;
        case 4: cout << "T_LCB " << lexeme << endl; break;
        case 5: cout << "T_RCB " << lexeme << endl; break;
        case 6: cout << "T_LPAREN " << lexeme << endl; break;
        case 7: cout << "T_RPAREN " << lexeme << endl; break;
        case 8: cout << "T_ID " << lexeme << endl; break;
        case 9: cout << "T_WHITESPACE " << found_whitespace << endl; found_whitespace=""; break;
        case 10: cout << "T_COMMENT " << found_comment << endl; found_comment =""; break;
        case 11: cout << "T_AND && " << endl; break;
        case 12: cout << "T_ASSIGN = " << endl; break;
        case 13: cout << "T_EQ == " << endl; break;
        case 14: cout << "T_GEQ >= " << endl; break;
        case 15: cout << "T_GT > " << endl; break;
        case 16: cout << "T_LEFTSHIFT << " << endl; break;
        case 17: cout << "T_LEQ <= " << endl; break;
        case 18: cout << "T_LT < " << endl; break;
        case 19: cout << "T_MINUS - " << endl; break;
        case 20: cout << "T_MOD % " << endl; break;
        case 21: cout << "T_MULT * " << endl; break;
        case 22: cout << "T_NEQ != " << endl; break;
        case 23: cout << "T_OR || " << endl; break;
        case 24: cout << "T_PLUS + " << endl; break; 
        case 25: cout << "T_RIGHTSHIFT >> " << endl; break;
        case 26: cout << "T_DIV / " << endl; break;
        case 27: cout << "T_SEMICOLON ;" << endl; break;
        case 28: cout << "T_CHARCONSTANT " << lexeme << endl; break;
        case 29: cout << "T_STRINGCONSTANT " << found_string << endl; found_string=""; break;
        default: exit(EXIT_FAILURE);
      }
    } else {
      if (token < 0) {
        exit(EXIT_FAILURE);
      }
    }
  }
  exit(EXIT_SUCCESS);
}
