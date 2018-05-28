# lambda class



lambda is a chunk of code that can be handled as an object. It is a familiar function in functional programming languages. There is also closure in lambda, lambda can not access parent variables, closure can also access parent variables. I think it is quick to see an example.
```
    > a: lambda(int) = lambda(num: int) {
        for (i := 0; i < num; i ++) {
            println ("HO!");
        }
    }
    > a(3)
    HO!
    HO!
    HO!

    > n:int = 3;
    > b:lambda () = closure () {
        for (i: = 0; i < n; i ++) {
            println ("HO!");
        }
        n = 999;
    }
    > b ()
    HO!
    HO!
    HO!
    > n
    999
```
Since closure is a type of lambda, the type name is supposed to be written with lambda. closure has access to the parent n variable. It is also possible to rewrite parent variables.
You can also create a return value. Please look at the following.
```
    > a: lambda (int): int = lambda (n: int): int {
        return n * 2;
    }
    > a (123)
    246
```
lambda (n: int): int with int and n as an argument and return value of int type lambda. In this case the contents are lambda which returns twice the argument, so a (123) returns 246.
