# Language Specification

## Lexical Syntax

A procedure definition is a sequence of *tokens* optionally separated by *white space* consisting of spaces, newlines, or comments. Every valid token is one of the following:

 * `ID`: a string consisting of any combination of letters (in the range a-z, A-Z), digits (in the range 0-9) as well as underscores ( _ ) with the exception that it may not start with a digit.
 * `STR`: a string consisting of any combination of letters, digits, and symbols (e.g. $, √) with the exception that it may not start with a digit.
 * `NUM`: a string consisting of only digits separated by at most one dot ( . ) at most one case insensitive "e" which must come after the dot.
 * `LPAREN`: the string "("
 * `RPAREN`: the string ")"
 * `LSQUARE`: the string "["
 * `RSQUARE`: the string "]"
 * `LCURLY`: the string "{"
 * `RCURLY`: the string "}"
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
 * `DOT`: the string "."
 * `COMMA`: the string ","
 * `COLON`: the string ":"
 * `SEMICOLON`: the string ";"
 * `QUESTION`: the string "?"
 * `POUND`: the string "#"
 * `DOLLAR`: the string "$"
 * `QUOTE`: the string ""
 * `APOSTROPHE`: the string "'"
 * `BACKSLASH`: the string "\\"
 * `BACKTICK`: the string "`"
 * `UNDERSCORE`: the string "_"

In addition to the above tokens, the following are also valid tokens and their strings are reserved keywords:

 * `IF`: the string "if"
 * `ELSE`: the string "else"
 * `WHILE`: the string "while"
 * `FOR`: the string "for"
 * `DO`: the string "do"
 * `RETURN`: the string "return"
 * `INT`: the string "int"
 * `FLOAT`: the string "float"
 * `DOUBLE`: the string "double"
 * `LONG`: the string "long"
 * `STRING`: the string "string"
 * `NONE_`: the string "none"
 * `NULL_`: the string "NULL"
 * `NULLPTR`: the string "nullptr"
 * `NEW`: the string "new"
 * `DELETE`: the string "delete"
 * `INCLUDE`: the string "include"
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
   * `params`
   * `paramlist`
   * `type`
   * `dcl`
   * `dcls`
   * `statements`
   * `statement`
   * `lvalue`
   * `string`
   * `expr`
   * `term`
   * `test`
   * `factor`
   * `arglist`
 * start symbol: `globals`
 * production rules:
   * `globals → `
   * `globals → include globals`
   * `globals → procedure globals`
   * `include → POUND INCLUDE LT STR RT`
   * `include → POUND INCLUDE QUOTE STR QUOTE`
   * `procedure → type ID LPAREN params RPAREN LBRACE statements RBRACE`
   * `params → `
   * `params → param params`
   * `param → type ID`
   * `type → INT`
   * `type → INT STAR`
   * `type → DOUBLE`
   * `type → DOUBLE STAR`
   * `type → FLOAT`
   * `type → FLOAT STAR`
   * `type → ID`
   * `type → ID STAR`
   * `statements → `
   * `statements → statement statements`
   * `statement → type STR SEMICOLON`
   * `statement → type STR BECOMES expr SEMICOLON`
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
