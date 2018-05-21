# Type inference

There are two types of Clover type inference: type variable inference of local variable, type inference to block object. First is type inference of local variables.
```
    a: int = 2;
```
Is
```
    a: = 2;
```
You can write. The type of the variable is declared according to the type of the rvalue value.

Type inference to another block object is as follows.
```
    a: lambda (int, int): int = lambda (a: int, b: int) {return a + b}
```
Depending on the return type, the return type of the block object is determined. (Return value: int can be omitted)

# Type block inference method

Arguments and return values ​​can be omitted in the method block. The arguments are declared as it, it2, it3, ....
```
    slist {1,2,3}. each { it.toString().println() }
    1
    2
    3

    a:SortableList<String> = slist {1,2,3}.map{ it.toString() }
```
.

----

[<< Pre-main function](feature-en) [>> next library reference](libraries-en)
