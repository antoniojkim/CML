# Language Specification

## Lexical Syntax

A procedure definition is a sequence of *tokens* optionally separated by *white space* consisting of spaces, newlines, or comments. Every valid token is one of the following:

 * `STR`: a string consisting of any combination of letters (in the range a-z, A-Z), digits (in the range 0-9) as well as underscores ( _ ) with the exception that it may not start with a digit.
 * `NUM`: a string consisting of only digits separated by at most one dot ( . ) at most one case insensitive "e" which must come after the dot.
 * `LPAREN`: the string "("
 * `RPAREN`: the string ")"
 * `LSQUARE`: the string "["
 * `RSQUARE`: the string "]"
 * `LCURLY`: the string "{"
 * `RCURLY`: the string "}"
 * `LCURLY`: the string "{"
 * `RCURLY`: the string "}"
 * `BECOMES`: the string "="
 * `EQ`: the string "=="
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
 * `PIPE_PIPE`: the string "||"
 * `L_ARROW`: the string "<-"
 * `R_ARROW`: the string "->"
 * `PIPE_PIPE`: the string "||"
 * `COMMA`: the string ","
 * `COLON`: the string ":"
 * `SEMICOLON`: the string ";"
 * `QUESTION`: the string "?"
 * `POUND`: the string "#"

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
 * `None`: the string "null"
 * `NULLPTR`: the string "nullptr"
 * `NEW`: the string "new"
 * `DELETE`: the string "delete"
 * `INCLUDE`: the string "include"

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
   * `procedure`
   * `main`
   * `params`
   * `paramlist`
   * `type`
   * `dcl`
   * `dcls`
   * `statements`
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
   * `globals → POUND INCLUDE LT STR RT globals`
   * `globals → POUND INCLUDE QUOTE STR QUOTE globals`
   * `globals → procedure globals`
   * `globals → main globals`
   * `globals → dcls globals`
   * `procedure → type`
