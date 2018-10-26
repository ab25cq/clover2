# regex class

Primitive type of regular expression. Regular expressions are only used as String types, so they are explained together with the String type. Regular expressions are used for character string processing and are as follows.

Metacharacters
```
    \A Start of character string
    \Z End of string
    \b Word boundary
    \B Other than word boundary
    \w Alphanumeric characters and '_' (underscore)
    \W other than alphanumeric characters and '_' (underscore)
    \s Space characters ('' (space), '\ t', '\ n', '\ r')
    \S Other than space character
    \d Numeric (0 ... 9)
    \D Other than numbers
    \t tab character
    \n Newline character (\ 0x0 d)
    \r carriage return character (\ 0x0a)
    \xHH Character code specified with 2 hexadecimal digits (HH)
```
For example `\d` represents all of `1` through `9`. For example `9999` matches `\d\d\d\d`.
```
    ^ Beginning of line
    $ End of line
    \b Word break
    \B Other than word breaks
```
For example `^\d` matches only the number at the beginning of a line.
```
    {n, m} Repeat n times or more, m times or less
    {n,} n or more iterations
    {n} n iterations
    \* Repeat 0 times or more (same as {0,})
    \+ Repeat more than once (same as {1,})
    \? 0 or 1 iteration (same as {0, 1})
```
For example `ba+` matches `baa`,` baa`, `baaaaa`. `ba{1,2}` is only `ba` and `baa`.
```
    [a-z] Match any lower case letter from 'a' to 'z'
    [A-Z] Match any lower case letter from 'A' to 'Z'
    [a-zA-Z] Match any lowercase letter or capital letter
    [0-9] Match any digit from '0' to '9'
    [a-zA-Z0-9] Match any of numbers or letters
    [\]\-] Or match with -
```
For example `[a-zA-Z]+` will match English words.
```
    (strings) strings is a group
    (str1|str2) Match str1 or str2
```
The Clover 2 regular expression is compatible with perl5 because it uses pcre. I will leave it here. For details, I will transfer explanations to other pages.

Next, I will explain methods using String and regular expressions.

String.match returns a bool value as a return value as to whether the string matches the regular expression. When it is true, it means that it matched, false means that it did not match.
```
    > "ABC".match(/\d/)
    false
    > "ABC".match(/^A/)
    true
```
Regular expressions are expressed as /.../. `"ABC"` does not match `\d` because it is not a number. Therefore, false is returned. ABC matches ^A because A is at the beginning of the line. Therefore, true is returned. To get a grouping character string, do as follows. A grouping character string is a regular expression matched and it is a part of character string enclosed in ().
```
    > group_strings: = new EqualableList <String>();
    list {}
    > "ABCABCABC".match(/^A(..)/, group_strings);
    true
    > group_strings
    list {BC}
```
Any two letters that come after A in /^A(..)/ are BC, so BC is in group_strings.

String.sub is a method for converting a character string and uses it as follows.
```
    > "ABCABCABC".sub(/^A/, "B")
    BBCABCABC
```
/^A/ represents A at the beginning of a line. It converts it to "B". To obtain a grouped character string, please do as follows.
```
    > group_strings = new EqualableList <String>();
    list {}
    > "ABCABCABC".sub(/A(..)/g, "B", group_strings);
    BBB
    > group_strings
    list {BC, BC, BC}
```
/A(..)/ means A with any one letter. There is g after /A(..)/, but if g is attached it does not end processing once it matches, it repeats it many times until the match is over.
(..) () is a grouping, in this case specify the character string you want to put in group_strings. Because ABC matches at /A(..)/, 3 BCs are in group_strings.

Regular expression options such as g have the following.
```
    m Multi-line mode - ^ and $ match internal lines
    i Ignore differences between lowercase letters
    s dotall
    A anchored
    D dollar_endonly
    U ungreedy
    x Readability enhancement - you can put whitespace and comments freely
    g Global - all that matches
```
Please see pcre manual for details. Author does not understand except g, i and m ,,,,,.

sub can also take a lambda expression.
```
    > "ABCABCABC".sub(/A(.)(.)/g, lambda (match_string: String, group_strings: EqualableList<String>): String {
        return "A".append(group_strings.join("+"));
    })
    AB+CAB+CAB+C
```
/A(.)(.)/g, so each time you match this regular expression the lambda expression is executed. The return value of the lambda expression is the conversion result. In this case match_string contains the entire matched string as ABC, group_strings contains {B, C}. Since B + C is returned with group_strings.join ("+"), AB + C is the return value of lambda expression in "A" .append (group_strings.join ("+")). The character string matching A (.) (.) Is converted as this conversion result as this conversion result.

Next, I will explain String.scan. String.scan is a method to retrieve an arbitrary character string from a string. It is quicker to see an example.
```
    > "ABC".scan(/./)
    list {A,B,C}
```
Characters are taken one character at a time by scan (/./) and it becomes a list. /./ is to represent an arbitrary character. scan will repeat the regular expression match without g. Let's see another example.
```
    > "ABC123ABC345" .scan (/\d\d\d/)
    list {123, 345}
```
You can retrieve the three-digit number by `scan (/\d\d\d/)`. You can also take a lambda expression.
```
    > "ABC123ABC345".scan(/\d\d\d/, lambda (match_string: String, group_strings: EqualableList<String>): String {
        return match_string.scan(/./).join("+");
    });
    list {1 + 2 + 3, 3 + 4 + 5}
```
The return value of the lambda expression becomes each element of List of return value of scan. If `group_strings: EqualableList <String>` has a regular expression enclosed in parentheses (), the matched character string will be inserted in parentheses. (Called grouping)

Next I will move on to the explanation of String.split. String.split can also be thought of as just the reverse of scan in a method that can separate strings with delimiter strings. Let's see an example.
```
    > "ABC\nDEF\nGHI\n".split(/\n/);
    list {ABC, DEF, GHI}
```
In this case you can take each line of text because it is split with newline characters. Let's see an example a little more.

    > "ABC,DEF,GHI\nJKL,MNO,PQR\nSTU" .split(/,|\n/));
    list {ABC, DEF, GHI, JKL, MNO, PQR}

There are English words on each line separated by commas, but only English words are taken out. `/, | \ n /` because the newline character is a delimiter.

split can also take a lambda expression.
```
    > "ABC,DEF,GHI".split(/,/, lambda(match_string: String): String {
        return match_string.chars(0).toString();
    });
    list {A,D,G}
```
Since the character string matching the match_string is included, the first character of it is rephrased with chars (0). The return value of the lambda expression is one of the elements of the return value of split itself.

Next, I would like to go to the explanation of indexOf. indexOf returns the offset (the index from the beginning) of the matching character string. If not found, it returns -1.
```
    > "ABC123".indexOf(/\d\d\d/)
    3
    > "ABC".indexOf(/\d\d\d/)
    -1
```
If it is judged whether the return value of indexOf () is -1 or not, it can judge whether a partial character string is included in the character string or not.

that's all.

Additional notes. Regular expressions can be written as regex "regular expressions" as expressions other than / regular expressions /. Regular expressions including # are treated as comments, but regex "regular expression" is fine. Honestly I wish I had done this from the beginning on this expression ,,,,
