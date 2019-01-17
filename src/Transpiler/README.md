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
 * `NEGATE`: the string "~"
 * `NOT`: the string "!"
 * `PLUS_EQUALS`: the string "+="
 * `MINUS_EQUALS`: the string "-="
 * `STAR_EQUALS`: the string "*="
 * `SLASH_EQUALS`: the string "/="
 * `PCT_EQUALS`: the string "%="
 * `CARET_EQUALS`: the string "^="
 * `AMP_EQUALS`: the string "&="
 * `PIPE_EQUALS`: the string "|="
 * `PLUS_PLUS`: the string "++"
 * `MINUS_MINUS`: the string "--"
 * `STAR_STAR`: the string "**"
 * `SLASH_SLASH`: the string "//"
 * `AMP_AMP`: the string "&&"
 * `LT_LT`: the string "<<"
 * `GT_GT`: the string "<<"
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
   * `term`
   * `boolean`
   * `factor`
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
   * `statement → IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement elsestatement`
   * `elseifstatement → `
   * `elseifstatement → ELSE IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement`
   * `elsestatement → `
   * `elsestatement → ELSE LBRACE statements RBRACE`
   * `statement → RETURN expr SEMICOLON`
   * `boolean → expr`
   * `boolean → expr GT expr`
   * `boolean → expr GE expr`
   * `boolean → expr LT expr`
   * `boolean → expr LE expr`
   * `boolean → expr NE expr`
   * `boolean → expr EQUALS_EQUALS expr`
   * `boolean → boolean AMP_AMP boolean`
   * `boolean → boolean PIPE_PIPE boolean`
   * `expr → term`
   * `expr → expr PLUS term`
   * `expr → expr MINUS term`
   * `term → factor`
   * `term → term STAR factor`
   * `term → term STAR_STAR factor`
   * `term → term SLASH factor`
   * `term → term SLASH_SLASH factor`
   * `term → term PCT factor`
   * `factor → NUM`
   * `factor → NONE_`
   * `factor → NULLPTR`
   * `factor → TRUE_`
   * `factor → FALSE_`
   * `factor → LPAREN expr RPAREN`
   * `factor → ID LSQUARE expr RSQUARE`
   * `factor → ID LSQUARE expr COLON expr RSQUARE`
   * `factor → ID LPAREN RPAREN`
   * `factor → ID LPAREN arglist RPAREN`
   * `factor → ID DOT ID`
   * `factor → ID DOT ID LPAREN RPAREN`
   * `factor → ID DOT ID LPAREN arglist RPAREN`
   * `factor → ID`
   * `factor → AMP lvalue`
   * `factor → STAR factor`
   * `factor → QUOTE string QUOTE`
   * `factor → ID QUOTE string QUOTE`
   * `arglist → expr`
   * `arglist → expr COMMA arglist`
   * `string → `
   * `string → ID`
   * `string → STR`
   * `lvalue → ID`
   * `lvalue → STAR factor`
   * `lvalue → LPAREN lvalue RPAREN`
