# Range class

The Range class is a class indicating range. It is made with Generics and Generics needs to implement the ISortable interface.
It is made by Generics so that it can be implemented even in Char class, etc., but normally you will only use Integer class.
The representation of the value is
```
    1..2
    3..4
    1..5
```
Etc.
The implemented method is isMember (value: T): bool. It judges whether the value of value is within the range.
It is important to note that to send a message to a Range object it is necessary to enclose the Range object in parentheses. This is based on the fact that there is nothing on the parser.
```
    (1..5).isMember (3) # -> true
```
Etc.
Because the range value can also include message passing, it can not be distinguished by the parser. The following cases can not be distinguished.

```
    1.object.hoge().IsMember ()
```
1. It is impossible to judge whether the object is in range or 1. object.hoge () is in range. To message passing to the Range object, enclose parentheses.

As it is, it is a very useless object, but you can use Range object in a method that accepts range as argument of method.
```
    "ABCDEGHI" .subString (1..3) # -> "BC"
    {1, 2, 3, 4, 5}. subList (2..4) # -> {3, 4}
```
Etc.
In the standard library, Range does not include the last value in range at first. It is because it is like Python.
It was because it was easier to use in personal feeling of writing the code.
Including the last value in the range is often a lot troublesome. I learned from Python.
For details of the Range class, see Range.clcl included in clover 2. Methods of String, List, and Buffer class using Range class are summarized there. Please check out Range.clcl if you like.
I make the Range class simple. If you feel like it, please add some method by the user.
