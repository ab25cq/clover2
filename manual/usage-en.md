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
    > cclover2 HelloWorld.clcl
    > vim HelloWorld.cl
    HelloWorld.fun();
    > clover2 HelloWorld.cl
```
is. 

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

If you want to add methods and fields to built-in classes such as String and Hash, they are included in the Clover2 source file. Include MyOwnLibrary.clcl. In MyOwnLibrary.clcl, these layers are necessary because layers are stacked in the order of Fundamental.clcl → Reflection.clcl → Thread.clcl → String.clcl → Container.clcl → Range.clcl → File.clcl → Command.clcl → SystemCalls.clcl → CLibrary.clcl → CGI.clcl → MyOwnLibrary.clcl.
One point of caution is that in this case you will need the option -core at compile time.
For example, if the name of the source file that extended String and Hash is MyOwnLibrary2.clcl

```
> cclover2 -core MyOwnLibrary2.clcl
```

Compile with. Please copy the original String.oclcl and Array.oclcl created to $HOME/.clover2. Regardless of the current directory, you can use that String or Array.

The open class of Clover2 is realized simply by compiling the class included in the incued file. So, adding methods and fields does not have any impact, such as being particularly slow. Also inherit is the same execution cost as just a method call, since the method that the method calls at compile time is fixed. Please relax and enjoy the coding of mixin-layers style. The secret that can add a method with the same argument with the same argument simply allows it and since it searches from the end of the method array at compile time method search it can only overwrite it. It does not cost anything. It is realized with a very simple mechanism.
1

## Split compilation and mixin-lyers 

Beginning with version 7.5.0 the following is possible. 

```
    > vim a.clcl
    class ClassA {
        field1:int;

        def initialize(value:int) {
            field1 = value;
        }

        def method(a:int, b:int) {
            return a + b + field1;
        }
    }
    > cclover2 a.clcl
    > vim b.clcl
    inherit ClassA {
        field2:int;

        def initialize(value:int, value2:int) {
            field1 = value;
            field2 = value2;
        }

        def method(a:int, b:int) {
            return a + b + field1 + field2;
        }
    }
```

You can add methods and fields with compiled class file inherit class name.  This makes mixin-layers more rigorous, so if you make refactoring and make changes, you only need to be careful about the layer behind.  You can also add fields and methods to the String class by adding inherit String to add functionality to the base class.  If you can load even the String class it is possible.  However, please be careful in order of compilation. 

Mixin compilation In mixin-layers, you may want to call methods dynamically.  In that case, specify dynamic when defining method.  It is useful because methods are determined at run time. 

```
    > vim a.clcl
    class ClassA {
        table:SortableList<String>();
        def initialize() {
            callTableInitialize();
        }

        def callTableInitialize(): dynamic {
            table = { "AAA", "BBB", "CCC" };
        }
    }

    > cclover2 a.clcl

    > vim b.clcl
    inherit ClassA {
        def callTableInitialize(): dynaimc {
            table = { "DDD", "EEE", "FFF" }
        }
    }
    > cclover2 b.clcl
```

In this case the Class A table will be"DDD","EEE","FFF".  If there is no dynamic specification, it should be"AAA","BBB","CCC". 


## Registering class files

The search path of the class file is the current directory and $HOME/.clover2. If you want to reference classes from any directory, please copy the oclcl file to $HOME/.clover2. If you have JIT enabled, you will also need to copy a dynamic library. Copy lib[class name].so, lib[class name].so.1.0.0 to $HOME/.clover2. Although it moves even if it does not exist, JIT does not become effective and it moves. Please register a $LIBRARY_PATH like to .bashrc: export LD_LIBRARY_PATH=~/.clover2:$LD_LIBRARY_PATH for searching of dynamic libraries later.

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

# Memory management

About GC, GC of Clover 2 uses both reference count and mark and sweep. With various improvements, It is considerably faster than version 5.9.9. However, since compaction is not performed, it is necessary for the user to call it yourself. It is not necessary for ordinary scripts, but for applications that are always running, such as editors, you have to call Clover.compaction () on the main loop only once in several times. If you do not do this, memory consumption will increase steadily. Also, when compaction is performed, the address of the object changes, so the address obtained by headOfMememory () becomes invalid. Please be aware of that. Conversely, if you do not call Clover.compaction, the start address of the object. It does not change. 

----

[<< Previous Home](Home-en) [>> next main function](feature-en)
