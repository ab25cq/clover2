# String class

The character string represents the character enclosed in double quotes.
```
    > "ABC"
    ABC
```
The concatenation of strings uses append.
```
    > "ABC".append("DEF")
    ABCDEF
```
The character string of Clover 2 is variable length. You can increase the memory of the stored character string.
String comparison uses equals.
```
    > "ABC".equals("ABC")
    true
    > "ABC".equals("DEF")
    false
```
Use chars to get the character at the location (index) where the string is located.
```
    > "ABC".chars (1)
    B
```
Index 0 is the first number. 1 is the second letter. In recent languages ​​indexes are often started from 0. Languages ​​starting from 1 existed in the past. (BASIC, PASCAL, etc.). Although it may be sensuously strange, it is more advantageous to start with 0 in consideration of the comparison operator. For example
```
    a: String = "ABC";
    for (i: int = 0; i < 3; i ++) {
        a.chars(i).printint ();
    }

output
    A
    B
    C
```

If this starts with index 1, I think that it feels unnatural because you have to write for (i: int = 1; i & lt; = 3; i ++) {...}. Therefore, in recent languages ​​indexes are often determined to be 0 as the first number.

The negative number of the index is the character counted from the back.
```
    > "ABC".chars(-1)
    C
    > "ABC".chars(-2)
    B
```
To obtain a substring, use subString.
```
    > "ABCDEFG".subString(1,3)
    BC
```
It does not include the character of the index of the second argument of subString.

Specifying a negative number results in an index counted from the back.
```
    > "ABCDEFG".subString(3, -1)
    DEFG
    > "ABCDEFG".subString(3, -2)
    DEF
```
To compare strings we use compare.
```
    > "ABC".compare("BCD");
    -1
    > "DEF".compare("ABC");
    3
```
A negative number is returned if the argument comes later. If the argument comes before it, it returns a positive number.
Well, as we are Japanese we do not compare Japanese much, but when doing alphabet processing
It will be useful.
I think that it is often the case that I do not know either the negative number or the positive number, but think that I think like this.
```
    > "ABC".compare("BCD") <0
    true
    > "BCD".compare("ABC")> 0
    true
```
> 0 is true if the object side is greater than the argument. It is <0 if the object side is smaller than the argument. > 0 or <0 holds in the order of object and argument. I think that you think that the object side is the lvalue value and the argument side is the right side value.

To get the index of a specific character string from the character string, use indexOf.
```
    > "ABC".indexOf(/B/)
    1
```
/B/ is written in regular expressions and also in regular expression class. You only have to remember that you can specify the character you want to find here.
If not found, it returns -1.
```
    > "ABC".indexOf(/D/)
    -1
```
To get the length of the string, use length.
```
    > "ABC".length ()
    3
```
To output a character string, use print, println, printf.
```
    > "ABC".println ();
    ABC
    > "ABC".print ();
    ABC
    > "ABC".printf("<%s>");
    <ABC>
```
println is output with line feeds. print does not feed a line. printf is the output of a string using the format string, and% s is the string of the object. In this case you can only use strings as arguments, so we only use% s, but you can use it as follows.
```
    > printf ("name% s age% d \ n", array {"Minato Daisuke", 39});
    name Minato Daisuke age 39
```
The first element of array of the second argument is written to% s and the second element is written to% d and output.
% s and% d are used properly according to the type of element as follows.
```
    % c Character type to output as 1 character
    % lc Print as 1 character. UTF 32 compatible (Japanese etc.)
    % d Integer type to output in decimal
    Output in% x hexadecimal number
    % o Output in octal number
    Output in the format of% f [-] dddd.dddddd
    Floating point type% e Output in exponential format
    % s String to output as a string. UTF 32 compatible. We will also output the Buffer class.
    % ls Not used. The String class is output in% s.
```
For details, please try to search printf format etc in the search engine. It is almost the same as C language.


Because strings are not primitive types, we only accept methods. It can not be an object of the operator.
