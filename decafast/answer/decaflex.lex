
%{

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

string found_whitespace = "";
string found_comment = "";
string found_string = "";

// Use YY_USER_ACTION to define function
// that tracks line position and line column

int prev_line_column = 1;
int prev_line_position = 1;
int line_position = 1;
int line_column = 1;

void printError(std::string error){
  std::cerr << error << std::endl;
  std::cerr << "Lexical error: line " << prev_line_position << ", position = " << prev_line_column << std::endl;
} 

// Updating line position and line column,
// used for error checking
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
hex_digit 0(x|X)[0-9a-zA-Z]+
decimal_digit [0-9]+

%x COMMENT
%x STRING

%%
  /*
    Keyword Rules
  */
func                       { return 1; }
int                        { return 2; }
package                    { return 3; }
bool                       { return 49; }
break                      { return 30; }
continue                   { return 31; }
else                       { return 32; }
extern                     { return 33; }
false                      { return 34; }
for                        { return 35; }
if                         { return 36; }
null                       { return 37; }
return                     { return 38; }
string                     { return 39; }
true                       { return 40; }
var                        { return 41; }
void                       { return 42; }
while                      { return 43; }
  /*
    Special Character/Unary Operator Rules
  */
\{                         { return 4; }
\}                         { return 5; }
\(                         { return 6; }
\)                         { return 7; }
;                          { return 27; }
,                          { return 44; }
\.                         { return 45; }
!                          { return 46; }
\[                         { return 47; }
\]                         { return 48; }
  /* 
    Identifier Rule
  */
[a-zA-Z\_][a-zA-Z\_0-9]*  { return 8; }
  /* 
    Whitespace Rules 
    - For all whitespaces that do have following whitespaces, don't return
    - For all whitespaces that do not have following whitespaces, return
  */
\t/{whitespace}                  { found_whitespace.append("\t");}
\r/{whitespace}                  { found_whitespace.append("\r");}
\v/{whitespace}                  { found_whitespace.append("\v");}
\f/{whitespace}                  { found_whitespace.append("\f");}
" "/{whitespace}                 { found_whitespace.append(" ");}
\n/{whitespace}                  { found_whitespace.append("\\n");}
\t/{not_whitespace}                  { found_whitespace.append("\t"); return 9;}
\r/{not_whitespace}                  { found_whitespace.append("\r"); return 9;}
\v/{not_whitespace}                  { found_whitespace.append("\v"); return 9;}
\f/{not_whitespace}                  { found_whitespace.append("\f"); return 9;}
" "/{not_whitespace}                 { found_whitespace.append(" "); return 9;}
\n                                   { found_whitespace.append("\\n"); return 9;}

  /*
    Comment Rules
  */
\/\/                  { found_comment.append("/"); found_comment.append("/"); BEGIN COMMENT; }
<COMMENT>.*           { found_comment.append(yytext);}
<COMMENT>\n           { found_comment.append("\\n"); BEGIN INITIAL; return 10;}
  /*
    Binary operations Rules
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
\/                          { return 26; }
  /*
    Character Literals Rules
  */
"'"({char_literal}|{escaped_char})"'"    { return 28; }
"'"({char_literal}|{escaped_char})({char_literal}|{escaped_char})+"'"?    { printError("ERROR: char constant length is greater than one"); return -1; }
"'"({char_literal}|{escaped_char})       { printError("ERROR: unterminated char constant"); return -1;}
"'""'"                                   { printError("ERROR: char constant has zero width"); return -1;}
  /*
    String Rules
    - Use state to track escape sequences and newlines
  */
\"                          { found_string.append(yytext); BEGIN STRING; }
<STRING>\"                  { found_string.append(yytext); BEGIN INITIAL; return 29; }    
<STRING><<EOF>>                     {printError("ERROR: string constant is missing closing delimiter"); return -1;}
<STRING>\\/([^nrtvfab\\'\"]*)       {printError("ERROR: unexpected escape sequence in string constant"); BEGIN INITIAL; found_string =""; return -1;}       
<STRING>\n                          {printError("ERROR: newline in string constant"); BEGIN INITIAL;  found_string =""; return -1;}    
<STRING>{char_literal}|{escaped_char}       {found_string.append(yytext);}
  /*
    Integer Rules
  */
{decimal_digit}|{hex_digit}       {return 50;} 
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
        case 2: cout << "T_INTTYPE " << lexeme << endl; break;
        case 3: cout << "T_PACKAGE " << lexeme << endl; break;
        case 4: cout << "T_LCB " << lexeme << endl; break;
        case 5: cout << "T_RCB " << lexeme << endl; break;
        case 6: cout << "T_LPAREN " << lexeme << endl; break;
        case 7: cout << "T_RPAREN " << lexeme << endl; break;
        case 8: cout << "T_ID " << lexeme << endl; break;
        case 9: cout << "T_WHITESPACE " << found_whitespace << endl; found_whitespace=""; break;
        case 10: cout << "T_COMMENT " << found_comment << endl; found_comment =""; break;
        case 11: cout << "T_AND " << lexeme << endl; break;
        case 12: cout << "T_ASSIGN " << lexeme << endl; break;
        case 13: cout << "T_EQ " << lexeme << endl; break;
        case 14: cout << "T_GEQ " << lexeme << endl; break;
        case 15: cout << "T_GT " << lexeme << endl; break;
        case 16: cout << "T_LEFTSHIFT " << lexeme << endl; break;
        case 17: cout << "T_LEQ " << lexeme << endl; break;
        case 18: cout << "T_LT " << lexeme << endl; break;
        case 19: cout << "T_MINUS " << lexeme << endl; break;
        case 20: cout << "T_MOD " << lexeme << endl; break;
        case 21: cout << "T_MULT " << lexeme << endl; break;
        case 22: cout << "T_NEQ " << lexeme << endl; break;
        case 23: cout << "T_OR " << lexeme << endl; break;
        case 24: cout << "T_PLUS " << lexeme << endl; break; 
        case 25: cout << "T_RIGHTSHIFT " << lexeme << endl; break;
        case 26: cout << "T_DIV " << lexeme << endl; break;
        case 27: cout << "T_SEMICOLON " << lexeme << endl; break;
        case 28: cout << "T_CHARCONSTANT " << lexeme << endl; break;
        case 29: cout << "T_STRINGCONSTANT " << found_string << endl; found_string=""; break;
        case 30: cout << "T_BREAK " << lexeme << endl; break;
        case 31: cout << "T_CONTINUE " << lexeme << endl; break;
        case 32: cout << "T_ELSE " << lexeme << endl; break;
        case 33: cout << "T_EXTERN " << lexeme << endl; break;
        case 34: cout << "T_FALSE" << endl; break;
        case 35: cout << "T_FOR " << lexeme << endl; break;
        case 36: cout << "T_IF " << lexeme << endl; break;
        case 37: cout << "T_NUL" << lexeme << endl; break;
        case 38: cout << "T_RETURN " << lexeme << endl; break;
        case 39: cout << "T_STRINGTYPE " << lexeme << endl; break;
        case 40: cout << "T_TRUE" << endl; break;
        case 41: cout << "T_VAR " << lexeme << endl; break;
        case 42: cout << "T_VOID " << lexeme << endl; break;
        case 43: cout << "T_WHILE " << lexeme << endl; break; 
        case 44: cout << "T_COMMA " << lexeme << endl; break;
        case 45: cout << "T_DOT" << endl; break;
        case 46: cout << "T_NOT" << endl; break;
        case 47: cout << "T_LSB " << lexeme << endl; break;
        case 48: cout << "T_RSB " << lexeme << endl; break;
        case 49: cout << "T_BOOLTYPE " << lexeme << endl; break;
        case 50: cout << "T_INTCONSTANT " << lexeme << endl; break;
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
