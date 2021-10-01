
%{

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

string foundWhitespace = "";

/* 
<WHITESPACE>\r                  { foundWhitespace.append("\\r");}
<WHITESPACE>\a                  { foundWhitespace.append("\\a");}
<WHITESPACE>\v                  { foundWhitespace.append("\\v");}
<WHITESPACE>\b                  { foundWhitespace.append("\\b");}
<WHITESPACE>\n                  { foundWhitespace.append("\\n");}
<WHITESPACE>" "                 { foundWhitespace.append(" ");} 
*/

%}

char_literal [^\\']
escaped_char \\(n|r|t|v|f|a|b|\\|'|\")
whitespace [\t\r\v\f\n ]

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
;                           { return 27; }
  /* 
    Identifier 
  */
[a-zA-Z\_][a-zA-Z\_0-9]*  { return 8; }
  /* 
    Whitespace rules 
  */

\t                  { foundWhitespace.append("\\t");}
\r                  { foundWhitespace.append("\\r");}
\v                  { foundWhitespace.append("\\v");}
\f                  { foundWhitespace.append("\\f");}
" "                 { foundWhitespace.append("BLANK_SPACE");}
\n                  { foundWhitespace.append("\\n"); return 9;}

  /*
    Binary operations
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
    Character Literals
  */
"'"({char_literal}|{escaped_char})"'"    { return 28;}
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
        case 9: cout << "T_WHITESPACE " << foundWhitespace << endl; foundWhitespace=""; break;
        case 10: cout << "T_WHITESPACE \\n" << endl; break;
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
