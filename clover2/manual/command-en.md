# Command class

The Command class allows you to execute external commands.
```
    > Command.pwd()
    /home/ab25cq
```
The Command class can omit the Command when calling a class method.
```
    > pwd()
    /home/ab25cq
```
Since the return value of the command of the Command class is Command, it can connect external commands like a pipe in a method chain.
```
    >ls("src/").grep("main")
    main.c
```
In addition to the string, Array, EqualableArray, SortableArray, List, EqualableList, SortableList can be passed as arguments to the method of the Command class. In that case it will be expanded and executed if the element is a string.
```
    > egrep("main", p"src/".glob("*.c"))
    src/compiler.c: int main(int argc, char ** argv)
    src/interpreter.c: int main(int argc, char ** argv)
    src/main.c: int main (int argc, char ** argv)
```
The return value of `p"src/".glob("*.c")` is `SortableList <String>`, but each element String is passed as an argument to egrep.

Because the text output by the toString () method can be converted to a string, you can also use the method of String as the execution result of Command.
```
    > ls("src/").grep("main").toString().scan(/./).join("+")
    m+a+i+n+.+c
```
You can know by bool value whether the execution result of the external command is correctly completed with the toBool () method.
```
    > pwd().toBool()
    true
```
The execution result can be obtained while displaying the output on the screen with the toBoolAndOutput () method. (Although terminal control is not done ,,,,,)
```
    > pwd().toBoolAndOutput ()
    /home/ab25cq
    true
```
You can save the output to a file with `write (path: String, permission: mode_t): Command` and` write (path: String): Command` method.
```
    > pwd().write("output_of_pwd")
    /home/ab25cq
    > cat("output_of_pwd")
    /home/ab25cq
```
The String class has a toCommand () method and can convert it to a Command class, so you can lessen String objects, for example.
```
    > "ABC".scan(/./).join("+").toCommand().less()
    A+B+C
```
The Command class is not a built-in class, but a user class. See Command.clc for definitions. It is realized using the dynamic_class mechanism. Since Clover 2 is open class, it is also possible to add methods later.

If there is only one method of the Command class, it can be described like a shell.
```
    > ls -al src/main.c
    -rw-rw-r--. 1 ab25cq ab25cq 1098 September 18 08: 01 src / main.c
    > vim src/main.c
```
There is no pipe connection. If you want to do something like a pipe please describe it like ordinary Clover 2 syntax such as `ls ("-al","src/main.c ").less()`.

However, pipes, && and || are also added, although they are added later. Please see the shell mode item for details.
