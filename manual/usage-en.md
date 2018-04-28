# How to use

## HELLO WORLD

```
    > vim HelloWorld.cl
    println("HELLO WORLD");
    > clover2 HelloWorld.cl
    HELLO WORLD
```

In the class version
```
    > vim HelloWorld.clcl
    class HelloWorld
    {
        def fun(): static {
            println("HELLO WORLD");
        }
    }
    > vim HelloWorld.cl
    HelloWorld.fun();
    > clover2 HelloWorld.cl
```
is. HelloWorld.clcl is automatically compiled as class name and file name are the same without compiling.

## Source code

There are two kinds of clover2 source code. One is the source file that defines the class and the extension is clcl.
```
    > vim HelloWorld.clcl
    class HelloWorld {
        def printHelloWorld(): static {
            println("HELLO WORLD");
        }
    }
    > cclover2 HelloWorld.clcl

    > vim HelloWorld.cl
    HelloWorld.printHelloWorld();
    > clover2 HelloWorld.cl
    HELLO WORLD
```
It looks like. `cclover2 HelloWorld.clcl` creates a class file called HelloWorld.oclcl.
`clover2 HelloWorld.cl` creates an executable file called HelloWorld.ocl for the virtual machine and executes it as it is.
Since there are two types, it may seem awkward, but if you want to create a complicated application, edit the clcl file to create a class
If you want to create a simple script, we will assume that you only edit cl files.
So, in this example, I just want to HELLO WORLD
```
    > vim HelloWorld.cl
    println("HELLO WORLD");

    > clover2 HelloWorld.cl
    HELLO WORLD
```
That's OK.

## Open class and include and mixin-layers style coding

Since Clover2 is an open class, you can add fields and methods after class definition. The way to do it is simply to include the source file with the original class defined and define the class.
```
    > vim("a.clcl");
    class Class A
    {
        field1: int;
        def initialize(value1: int) {
            self.field1 = value1;
        }
        def setField1(value: int) {
            self.field1 = value;
        }
    }
    > vim ("b.clcl");
    include "a.clcl"
    class Class A
    {
        field2: String;
        def initialize(value1: int, value2: String) {
            self.field1 = value1;
            self.field2 = value2;
        }
        def setField2(value: String) {
            self.field2 = value;
        }
    }
```
Class A now has fields1 and 2 in fields and methods have setField1 and setField2. In this case, compiling is all right with b.clcl. If there is a method with the same name, the method defined at the back takes precedence. At that time, you can call the method of the previous definition with inherit(...). If you use it successfully you can write a program in a style to code like mixin-layers.
```
    > vim("c.clcl")
    class ClassB
    {
        field1: int;
        def initialize(value1: int) {
            self.field1 = value1;
        }
        def show() {
            self.field1.toString().println();
        }
    }
    > vim ("d.clcl")
    include "c.clcl"
    class ClassB
    {
        field 2: String;
        def initialize(value1: int, value2: String) {
            self.field1 = value1;
            self.field2 = value2;
        }
        def show() {
            inherit();
            self.field2.println();
        }
    }
```
A field has been added in d.clcl and the method has been overwritten. The overwritten show takes precedence for the method in d.clcl when searching for a method call. Because inherit(); is called in the show, the field c.clcl's show() is called and both fields are displayed. If there are arguments in the overridden method, give inherit an argument. <br>

If you want to add methods and fields to built-in classes such as String and Hash, they are included in the Clover2 source file. Include MyOwnLibrary.clcl. In MyOwnLibrary.clcl, these layers are necessary because layers are stacked in the order of Fundamental.clcl → Reflection.clcl → Thread.clcl → String.clcl → Container.clcl → Range.clcl → File.clcl → Command.clcl → SystemCalls.clcl → MyOwnLibrary.clcl.
One point of caution is that in this case you will need the option -core at compile time.
For example, if the name of the source file that extended String and Hash is MyOwnLibrary2.clcl

```
> cclover2 -core MyOwnLibrary2.clcl
```

Compile with. Please copy the original String.oclcl and Array.oclcl created to $HOME/.clover2. Regardless of the current directory, you can use that String or Array.

The open class of Clover2 is realized simply by compiling the class included in the incued file. So, adding methods and fields does not have any impact, such as being particularly slow. Also inherit is the same execution cost as just a method call, since the method that the method calls at compile time is fixed. Please relax and enjoy the coding of mixin-layers style. The secret that can add a method with the same argument with the same argument simply allows it and since it searches from the end of the method array at compile time method search it can only overwrite it. It does not cost anything. It is realized with a very simple mechanism.

## Registering class files

The search path of the class file is the current directory and $HOME/.clover2. If you want to reference classes from any directory, please copy the oclcl file to $HOME/.clover2. If you have JIT enabled, you will also need to copy a dynamic library. Copy lib[class name].so, lib[class name].so.1.0.0 to $HOME/.clover2. Although it moves even if it does not exist, JIT does not become effective and it moves. Please register a $LIBRARY_PATH like to .bashrc: export LD_LIBRARY_PATH=~/.clover2:$LD_LIBRARY_PATH for searching of dynamic libraries later.

## Automatic class compilation function
```
    > vim Hello.clcl
    class Hello {
        def hello () {
            println ("HELLO WORLD");
        }
    }
    > vim hello.cl
    Hello.hello ();
    > clover2 hello.cl
    HELLO WORLD
```
If you specify the source file name for the clover2 command, it will be automatically compiled before it is executed.
The dependent class also recursively performs dependency analysis, so it all compiles automatically.
In clover2, file names and class names will work differently, but it will be convenient to keep the same class name and file name.
However, even in version 3.5.3, it is still unstable, so just to be sure, it may be better to write cclover2 hello.clcl in Makefile etc. This is because it may not compile even if you modify the file with the editor. I'll fix it around here as well. Excuse me.

## Cyclic reference of class
```
    > vim ClassA.clcl
    class ClassA {
        field1: static int;

        def hello(): static {
            ClassB.hello ();
        }
    }
    > vim ClassB.clcl
    class ClassB {
        def hello(): static {
            println("ClassA.field1 \{ClassA.field1}\n");
        }
    }
```
In the case of such a code, compilation of both Class A.clcl and Class B.clcl does not pass, but it should be as follows.
```
    > vim ClassA.clcl
    include "ClassB.clcl"

    class ClassA {
        field1: static int;

        def hello(): static {
            ClassB.hello();
        }
    }
    > vim ClassB.clcl
    include "ClassA.clcl"

    class ClassB {
        def hello (): static {
            println("ClassA.field1 \ {ClassA.field1} \ n");
        }
    }
```
Include in both the circular reference source. Compiling either source goes through compilation.

----

[<< Previous Home](Home-en) [>> next main function](feature-en)
