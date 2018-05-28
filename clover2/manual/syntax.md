# Clover2 構文

拡張BNFで構文を書きます。

```
alpha             ::= 'a'|...|'z'|'A'|...|'Z'
num               ::= '0'|...|'9'
num_postfix       ::= 'y'|"uy"|'s'|"us"|'l'|'ul'|'u'
float             ::= ('1'|...|'9') ('0'|...|'9')* '.' ('0'|...|'9')+ ('f'|'F')?
integer           ::= ('1'|...|'9') ('0'|...|'9')* num_postfix?
hex_number        ::= '0x' ('0'|...|'9'|'a'|...|'f'|'A'|...|'F')+ num_postfix?
oct_number        ::= '0' ('0'|...|'7')* num_postfix?
boolean           ::= "true" | "false"
slash_word        ::= ("./"|"../")? alpha (alpha|'_'|'/')*
word              ::= alpha (alpha | '_')*
annotation        ::= '@' (alpha (alpha | num | '-' | '_' | '[' | ']')* )?
ann               ::= '@' (alpha | '_')*

class_type        ::= word
type              ::= "lambda" ('(' type_list? ')')? (':' type)? '[]'? annotation?
                    | word ('<' type_list '>')? '[]'? annotation?
type_list         ::= type (',' type)*

literal           ::= ("-"|"+")? (float | integer) | hex_number | oct_number
                    | boolean | "null" | charactor_literal | string_literal
                    | path_literal | buffer_literal | regexp_literal

charactor_literal ::= "'" '\' ('n'|'t'|'r'|'a'|'\'|'0'|.) "'"
                    | "'" [0 - 127] "'" | "'" utf8 "'"
string_expression ::= '{' expression '}'
escape_sequence   ::= '\' ('0'|'n'|'t'|'r'|'a'|'\'|string_expression|.)
string_literal    ::= '"' (not('"'|'\') | escape_sequence)* '"'
path_literal      ::= ("P"|"p") '"' (not('"'|'\') | escape_sequence)* '"'
buffer_literal    ::= ("B"|"b") '"' (not('"'|'\') | escape_sequence)* '"'
regexp_literal    ::= '/' ('\' '\' '{' | '\' string_expression | not "/")* "/"
                      ('g'|'i'|'s'|'m'|'A'|'D'|'U'|'x')*

collection_expression
                  ::= list | equalable_list | sortable_list
                    | array_value | array | equalable_array | sortable_array
                    | hash | tuple

array_value       ::= '[' expressions ']'
array             ::= "array" '{' expressions '}'
equalable_array   ::= ("equalable_array" | "earray") '{' expressions '}'
sortable_array    ::= ("sortable_array" | "sarray") '{' expressions '}'
list              ::= "list" '{' expressions '}'
equalable_list    ::= ("equalable_list" | "elist") '{' expressions '}'
sortable_list     ::= ("sortable_list" | "slist") '{' expressions '}'
hash              ::= "hash" '{' (expression_pair (',' expression_pair)*)? '}'
tuple             ::= "tuple" '{' expressions '}'

expressions       ::= (expression (',' expression)*)?
expression_pair   ::= expression ":" expression

control_expression::= normal_block | if_expression
                    | while_expression | for_expression | "break"
                    | throw_expression | try_expression
                    | return_expression | new_expression
                    | "closure" block_object | "lambda" block_object | function
                    | iniherit

normal_block      ::= block
if_expression     ::= "if" "(" expression ")" block
                      ("elif" "(" expression ")" block)*
                      ("else" block)?
while_expression  ::= "while" "(" expression ")" block
for_expression    ::= "for" "(" expression ";" expression ";" expression ")" block
throw_expression  ::= "throw" expression
try_expression    ::= "try" block "catch" "(" param_list ")" block
return_expression ::= "return" expression?
new_expression    ::= "new" type_for_new method_params
block_object      ::= "(" param_list ")" (':' type)? block 
function          ::= "def" word "(" param_list ")" (':' type)? block
iniherit          ::= "inherit" method_params

param             ::= word ":" type
param_list        ::= (param ("," param)*)?
block             ::= "{" (expression ";"?)* "}"
type_for_new      ::= word ('<' type_list '>')? ('[' expression "]")?

assign_expression ::= slash_word ':=' expression
                    | slash_word ':' type '=' expression
                    | slash_word '=' expression
                    | slash_word assign_operator expression
assign_operator   ::= "+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|="

method_expression ::= slash_word type '.' word method_params
                    | slash_word type '.' word (assign_operator|'==') expression
                    | slash_word method_params
                    | slash_word command_method_params
                      ("||" word command_method_params|"&&"|";"|"\n")*

method_params     ::= ('(' (expression ann (',' expression ann)*)? ')')?
                      simple_lambda_params?
simple_lambda_params
                  ::= '{' ("|" param_list "|" (':' type)?)? (expression ";"?)* '}'
command_method_params
                  ::= ";" | "\n" | '${' (not '}')* '}'
                    | "$" (alpha|num|'_')* | '\' . | '"' . * '"' | "'" . * "'" *

expression_node   ::= collection_expression | assign_expression | method_expression
                    | literal | slash_word | '(' expression ')' | '&' expression

postposition_operator
                  ::= '..' word (method_params|(assign_operator|'==') expression)?
                    | '[' expression "]" ((assign_operator|'==') expression)?
                    | '->' type ('==' expression)?
                    | '++' | '--'
expression_monadic::= ("++"|"--"|"~"|"!") expression_monadic
                    | expression_node postposition_operator*
expression_implements
                  ::= expression_monadic ("implements" word)*
expression_mult   ::= expression_implements (("*"|"/"|"%") expression_implements)*
expression_add    ::= expression_mult (("+"|"-") expression_mult)*
expression_shift  ::= expression_add (("<<=" | ">>=") expression_add)*
expression_comparison
                  ::= expression_shift ((">="|"<="|">"|"<") expression_shift)*
expression_equal  ::= expression_comparison (("=="|"!=") expression_comparison)*
expression_and    ::= expression_equal ("&" expression_equal)*
expression_xor    ::= expression_and ("^" expression_and)*
expression_or     ::= expression_xor ("|" expression_xor)*
expression_lor    ::= expression_or (("&&"|"||") expression_lor)*
expression_conditional
                  ::= expression_lor ("?" expression ":" expression)*
expression        ::= expression_conditional
```
