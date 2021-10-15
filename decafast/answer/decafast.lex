%{
#include "default-defs.h"
#include "decafast.tab.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int lineno = 1;
int tokenpos = 1;

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
    Pattern definitions for all tokens 
  */


  /*
    Keyword Rules
  */
func                       { return 1; }
int                        { return 2; }
package                    { return T_PACKAGE; }
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
\{                         { return T_LCB; }
\}                         { return T_RCB; }
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
[a-zA-Z\_][a-zA-Z\_0-9]*   { yylval.sval = new string(yytext); return T_ID; } /* note that identifier pattern must be after all keywords */
  /* 
    Whitespace Rules 
    - For all whitespaces that do have following whitespaces, don't return
    - For all whitespaces that do not have following whitespaces, return
  */
  /*
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
  */
[\t\r\n\a\v\b ]+           { } /* ignore whitespace */

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

int yyerror(const char *s) {
  cerr << lineno << ": " << s << " at char " << tokenpos << endl;
  return 1;
}

