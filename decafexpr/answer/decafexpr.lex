%{
#include "default-defs.h"
#include "decafexpr.tab.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

string found_whitespace = "";
string found_comment = "";
string found_string = "";
int char_val = -1 ;
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

int escape_to_ascii(string escape_char) {
  escape_char = escape_char.substr(1,2);
  if(escape_char == "\\a") return 7;
  if(escape_char == "\\b") return 8;
  if(escape_char == "\\t") return 9;
  if(escape_char == "\\n") return 10;
  if(escape_char == "\\v") return 11;
  if(escape_char == "\\f") return 12;
  if(escape_char == "\\r") return 13;
  return escape_char[1];
}

string get_actual_escape_char(string escape_char) {
  if(escape_char == "\\a") return "\a";
  if(escape_char == "\\b") return "\b";
  if(escape_char == "\\t") return "\t";
  if(escape_char == "\\n") return "\n";
  if(escape_char == "\\v") return "\v";
  if(escape_char == "\\f") return "\f";
  if(escape_char == "\\r") return "\r";
  return escape_char;
}

#define YY_USER_ACTION  update_position();

%}

char_literal [^']
escaped_char \\(n|r|t|v|f|a|\\|b|\'|\")
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
func                       { return T_FUNC; }
int                        { return T_INTTYPE; }
package                    { return T_PACKAGE; }
bool                       { return T_BOOLTYPE; }
break                      { return T_BREAK; }
continue                   { return T_CONTINUE; }
else                       { return T_ELSE; }
extern                     { return T_EXTERN; }
false                      { return T_FALSE; }
for                        { return T_FOR; }
if                         { return T_IF; }
null                       { return T_NULL; }
return                     { return T_RETURN; }
string                     { return T_STRINGTYPE; }
true                       { return T_TRUE; }
var                        { return T_VAR; }
void                       { return T_VOID; }
while                      { return T_WHILE; }
  /*
    Special Character/Unary Operator Rules
  */
\{                         { return T_LCB; }
\}                         { return T_RCB; }
\(                         { return T_LPAREN; }
\)                         { return T_RPAREN; }
;                          { return T_SEMICOLON; }
,                          { return T_COMMA; }
\.                         { return T_DOT; }
!                          { return T_NOT; }
\[                         { return T_LSB; }
\]                         { return T_RSB; }
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
\/\/                  { BEGIN COMMENT; }
<COMMENT>.*           { }
<COMMENT>\n           { BEGIN INITIAL; }
  /*
    Binary operations Rules
  */
&&                          { return T_AND; }
=                           { return T_ASSIGN; }
==                          { return T_EQ; }
\>=                         { return T_GEQ; }
\>                          { return T_GT; }
\<\<                        { return T_LEFTSHIFT; }
\<=                         { return T_LEQ; }
\<                          { return T_LT; }
"-"                         { return T_MINUS; }
%                           { return T_MOD; }
\*                          { return T_MULT; }
!=                          { return T_NEQ; }
\|\|                        { return T_OR; }
\+                          { return T_PLUS; }
\>\>                        { return T_RIGHTSHIFT; }
\/                          { return T_DIV; }
  /*
    Character Literals Rules
  */
"'"({char_literal}|{escaped_char})"'"  {
                                          int val;
                                          if(yyleng == 4){
                                            val = escape_to_ascii(yytext);
                                          }
                                          else{
                                            val = static_cast<int>(yytext[1]);
                                          }
                                          yylval.inval = val; return T_INTCONSTANT; 
                                        }
"'"({char_literal})({char_literal})+"'"   { std::cout << yytext << '\n'; printError("ERROR: char constant length is greater than one"); return -1; }
"'"({char_literal}|{escaped_char})       { printError("ERROR: unterminated char constant"); return -1;}
"'""'"                                   { printError("ERROR: char constant has zero width"); return -1;}
  /*
    String Rules
    - Use state to track escape sequences and newlines
  */
\"                          { BEGIN STRING; }
<STRING>\"                  { 
                              yylval.sval = new string(found_string); 
                              found_string=""; 
                              BEGIN INITIAL; return T_STRINGCONSTANT; }    
<STRING><<EOF>>                     {printError("ERROR: string constant is missing closing delimiter"); return -1;}
<STRING>\\/([^nrtvfab\\'\"]*)       {printError("ERROR: unexpected escape sequence in string constant"); BEGIN INITIAL; found_string =""; return -1;}       
<STRING>\n                          {printError("ERROR: newline in string constant"); BEGIN INITIAL;  found_string =""; return -1;}    
<STRING>{char_literal}                     {
  found_string.append(yytext);
  }
<STRING>{escaped_char} {
  found_string.append(std::string(yytext));
  }
  /*
    Integer Rules
  */
{decimal_digit}      {yylval.inval = std::stoi(yytext); return T_INTCONSTANT;} 
{hex_digit}                       {
                                  std::stringstream ss;
                                  int val;
                                  ss << std::hex << yytext;
                                  ss >> val;     
                                  yylval.inval = val; 
                                  return T_INTCONSTANT;
                                  } 
  /*
    EOF?
  */
.                          { cerr << "Error: unexpected character in input" << endl; return -1; }
%%

int yyerror(const char *s) {
  printError(s);
  return 1;
}
