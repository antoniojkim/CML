# Language Specification

## Lexical Syntax

A procedure definition is a sequence of *tokens* optionally separated by *white space* consisting of spaces, newlines, or comments. Every valid token is one of the following:

 * `ID`: a string consisting of any combination of letters (in the range a-z, A-Z), digits (in the range 0-9) as well as underscores ( _ ) with the exception that it may not start with a digit.
 * `STR`: a string consisting of any combination of letters, digits, and symbols (e.g. $, √)
 * `NUM`: a string consisting of only digits separated by at most one dot ( . ) at most one case insensitive "e" which must come after the dot.
 * `LPAREN`: the string "("
 * `RPAREN`: the string ")"
 * `LSQUARE`: the string "["
 * `RSQUARE`: the string "]"
 * `LBRACE`: the string "{"
 * `RBRACE`: the string "}"
 * `EQUALS`: the string "="
 * `EQUALS_EQUALS`: the string "=="
 * `NE`: the string "!="
 * `QE`: the string "?="
 * `LT`: the string "<"
 * `GT`: the string ">"
 * `LE`: the string "<="
 * `GE`: the string ">="
 * `PLUS`: the string "+"
 * `MINUS`: the string "-"
 * `STAR`: the string "*"
 * `SLASH`: the string "/"
 * `PCT`: the string "%"
 * `CARET`: the string "^"
 * `AMP`: the string "&"
 * `PIPE`: the string "|"
 * `TILDE`: the string "~"
 * `EXCL`: the string "!"
 * `PLUS_EQUALS`: the string "+="
 * `MINUS_EQUALS`: the string "-="
 * `STAR_EQUALS`: the string "*="
 * `SLASH_EQUALS`: the string "/="
 * `PCT_EQUALS`: the string "%="
 * `CARET_EQUALS`: the string "^="
 * `AMP_EQUALS`: the string "&="
 * `PIPE_EQUALS`: the string "|="
 * `GT_GT_EQUALS`: the string ">>="
 * `LT_LT_EQUALS`: the string "<<="
 * `PLUS_PLUS`: the string "++"
 * `MINUS_MINUS`: the string "--"
 * `STAR_STAR`: the string "**"
 * `SLASH_SLASH`: the string "//"
 * `AMP_AMP`: the string "&&"
 * `LT_LT`: the string "<<"
 * `GT_GT`: the string ">>"
 * `L_ARROW`: the string "<-"
 * `R_ARROW`: the string "->"
 * `PIPE_PIPE`: the string "||"
 * `COLON_COLON`: the string "::"
 * `DOT`: the string "."
 * `COMMA`: the string ","
 * `COLON`: the string ":"
 * `SEMICOLON`: the string ";"
 * `QUESTION`: the string "?"
 * `POUND`: the string "#"
 * `DOLLAR`: the string "$"
 * `QUOTE`: the string """
 * `APOSTROPHE`: the string "'"
 * `BACKSLASH`: the string "\\"
 * `BACKTICK`: the string "`"
 * `UNDERSCORE`: the string "_"
 * `BOF_`: the string "BOF"
 * `EOF_`: the string "EOF"

In addition to the above tokens, the following are also valid tokens and their strings are reserved keywords:

 * `IF`: the string "if"
 * `ELSE`: the string "else"
 * `WHILE`: the string "while"
 * `FOR`: the string "for"
 * `DO`: the string "do"
 * `RETURN`: the string "return"
 * `BOOL`: the string "bool"
 * `INT`: the string "int"
 * `FLOAT`: the string "float"
 * `DOUBLE`: the string "double"
 * `LONG`: the string "long"
 * `TRUE_`: the string "true"
 * `FALSE_`: the string "false"
 * `NONE_`: the string "none"
 * `NULL_`: the string "NULL"
 * `VOID`: the string "void"
 * `NULLPTR`: the string "nullptr"
 * `NEW`: the string "new"
 * `DELETE`: the string "delete"
 * `INCLUDE`: the string "include"
 * `UNSIGNED`: the string "unsigned"
 * `DEF`: the string "def"
 * `FUNCTION`: the string "function"
 * `VAR`: the string "var"

White space consists of any sequence of the following:

 * `SPACE`: ascii 32
 * `TAB`: ascii 9
 * `NEWLINE`: ascii 10
 * `COMMENT`: the string "//" followed by all the characters up to and including the next newline
 * `MULTILINE_COMMENT`: all characters wrapped by the two strings "/\*" and "\*/"

## Context-free Syntax

A context-free grammar for a valid CML program is:

 * terminal symbols: the set of valid tokens above
 * nonterminal symbols:
   * `globals`
   * `include`
   * `procedure`
   * `main`
   * `param`
   * `params`
   * `vtype`
   * `type`
   * `signedtype`
   * `dcl`
   * `dcls`
   * `statements`
   * `statement`
   * `elseifstatement`
   * `elsestatement`
   * `lvalue`
   * `string`
   * `expr`
   * `expr1`
   * `expr2`
   * `expr3`
   * `expr4`
   * `expr5`
   * `expr6`
   * `expr7`
   * `expr8`
   * `expr9`
   * `expr10`
   * `expr11`
   * `expr12`
   * `expr13`
   * `expr14`
   * `expr15`
   * `expr16`
   * `arglist`
   * `whitespace`
 * start symbol: `globals`
 * production rules:
   * `globals → `
   * `globals → include globals`
   * `globals → procedure globals`
   * `include → POUND INCLUDE LT ID GT`
   * `include → POUND INCLUDE QUOTE ID QUOTE`
   * `procedure → vtype ID LPAREN params RPAREN LBRACE statements RBRACE`
   * `params → `
   * `params → dcl params`
   * `dcl → vtype ID`
   * `dcl → vtype ID EQUALS expr`
   * `vtype → signedtype type`
   * `vtype → signedtype type STAR`
   * `vtype → signedtype type AMP`
   * `signedtype → `
   * `signedtype → UNSIGNED`
   * `type → BOOL`
   * `type → INT`
   * `type → LONG`
   * `type → LONG LONG`
   * `type → DOUBLE`
   * `type → FLOAT`
   * `type → ID`
   * `type → VOID`
   * `statements → `
   * `statements → statements statement`
   * `statement → dcl SEMICOLON`
   * `statement → IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement elsestatement`
   * `elseifstatement → `
   * `elseifstatement → ELSE IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement`
   * `elsestatement → `
   * `elsestatement → ELSE LBRACE statements RBRACE`
   * `statement → RETURN expr SEMICOLON`
   * `expr → expr16`
   * `expr1 → factor`
   * `expr1 → lvalue`
   * `expr1 → ID COLON_COLON expr1`
   * `expr2 → expr1`
   * `expr2 → LPAREN expr RPAREN`
   * `expr2 → expr2 PLUS_PLUS`
   * `expr2 → expr2 MINUS_MINUS`
   * `expr2 → ID LPAREN RPAREN`
   * `expr2 → ID LPAREN arglist RPAREN`
   * `expr2 → ID LSQUARE expr RSQUARE`
   * `expr2 → ID LSQUARE expr COLON expr RSQUARE`
   * `expr2 → QUOTE string QUOTE`
   * `expr2 → ID QUOTE string QUOTE`
   * `expr2 → expr2 DOT expr2`
   * `expr2 → expr2 DOT expr2 LPAREN RPAREN`
   * `expr2 → expr2 DOT expr2 LPAREN arglist RPAREN`
   * `expr2 → expr2 R_ARROW expr1`
   * `expr2 → expr2 L_ARROW expr1`
   * `expr3 → expr2`
   * `expr3 → PLUS_PLUS expr2`
   * `expr3 → MINUS_MINUS expr2`
   * `expr3 → PLUS expr2`
   * `expr3 → MINUS expr2`
   * `expr3 → EXCL expr2`
   * `expr3 → TILDE expr2`
   * `expr3 → STAR expr2`
   * `expr3 → AMP expr2`
   * `expr4 → expr3`
   * `expr4 → expr4 STAR_STAR expr3`
   * `expr5 → expr4`
   * `expr5 → expr5 STAR expr4`
   * `expr5 → expr5 SLASH expr4`
   * `expr6 → expr5`
   * `expr6 → expr6 PLUS expr5`
   * `expr6 → expr6 MINUS expr5`
   * `expr7 → expr6`
   * `expr7 → expr7 GT_GT expr6`
   * `expr7 → expr7 LT_LT expr6`
   * `expr8 → expr7`
   * `expr9 → expr8`
   * `expr9 → expr9 GT expr8`
   * `expr9 → expr9 LT expr8`
   * `expr9 → expr9 GE expr8`
   * `expr9 → expr9 LE expr8`
   * `expr10 → expr9`
   * `expr10 → expr10 EQUALS_EQUALS expr9`
   * `expr10 → expr10 NE expr9`
   * `expr10 → expr10 QE expr9`
   * `expr11 → expr10`
   * `expr11 → expr11 AMP expr10`
   * `expr12 → expr11`
   * `expr12 → expr12 CARET expr11`
   * `expr13 → expr12`
   * `expr13 → expr13 PIPE expr12`
   * `expr14 → expr13`
   * `expr14 → expr14 AMP_AMP expr13`
   * `expr15 → expr14`
   * `expr15 → expr15 PIPE_PIPE expr14`
   * `expr16 → expr15`
   * `expr16 → lvalue EQUALS expr15`
   * `expr16 → lvalue PLUS_EQUALS expr15`
   * `expr16 → lvalue MINUS_EQUALS expr15`
   * `expr16 → lvalue STAR_EQUALS expr15`
   * `expr16 → lvalue SLASH_EQUALS expr15`
   * `expr16 → lvalue PCT_EQUALS expr15`
   * `expr16 → lvalue GT_GT_EQUALS expr15`
   * `expr16 → lvalue LT_LT_EQUALS expr15`
   * `expr16 → lvalue AMP_EQUALS expr15`
   * `expr16 → lvalue CARET_EQUALS expr15`
   * `expr16 → lvalue PIPE_EQUALS expr15`
   * `factor → NUM`
   * `factor → NONE_`
   * `factor → NULLPTR`
   * `factor → TRUE_`
   * `factor → FALSE_`
   * `factor → ID`
   * `arglist → expr`
   * `arglist → expr COMMA arglist`
   * `string → `
   * `string → ID`
   * `string → STR`
   * `lvalue → ID`
   * `lvalue → STAR expr2`
   * `lvalue → LPAREN lvalue RPAREN`
