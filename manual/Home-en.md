# Introduction

To you who wants to start using Clover2. This language consists of compilers and virtual machines like Java and C#.
In order to compile, type checking can be done at compile time.
In addition, it is designed to be able to use an easy-to-use library like Ruby.
Regular expressions, lambda, closure etc are first class objects. It can also be used as a literal, and it can also be passed as an argument to a method.
There are primitive arrays, but List and Hash can also be used in literals.
Well, in short, it looks like Java with usability like Ruby.
Although the library has not been maintained yet, I am glad if you can use it with ease in managing the server.

# Supported functions

There are two kinds of primitive classes and ordinary classes, primitive classes do not use heap. There is no method call, only operators are supported, and processing to the value of the primitive class is fast. But there are boxing and unboxing and when you make a method call to a primitive class, add a value to a container library etc, it is boxing to reduce usability of the primitive class. Conversely, if it becomes an object of an operator, it is unboxed.
2. Like functional languages, Lambda and closure are first class objects. Regular expressions are also first class objects.
3. There is a simple Generics. It seems to simplify Java's generics. Generics information is only available at compile time, it is efficient as it disappears at run time.
4. There is no inheritance for simplicity. There are only interfaces, classes and modules. Therefore, it is efficient to specify the method at compile time except for method calls to the interface. We support transfer as a function that can be used instead of inheritance in the language.
5. It is open class. You can add methods and fields later to all classes including built-in classes. You can define methods with the same name, you can do differential programming like mixin-layers style.
6. Clover2 also has an interpreter. External commands can also be easily executed and can be easily mixed with clover2's methods.


```
> ls().grep("main.c").toString().scan(/./).join("+").toCommand().less()
> m+a+i+n+.+c
```

And less displayed with an external command.
Method names, external command names, file names are also supplemented. Just like Java IDE and PowerShell, we will complement the context.

7. Attaching --with-jit specification to ./configure enables JIT by LLVM. Processing speed improves. It is about 3 times faster. Internally, it is good to say that it is a native code compiler rather than JIT because it is JIT compiled to compile the source library of Clover2 to make dynamic libraries.

8. You can write like a shell and REPL can be used instead of shell. Complementation also has the same function as shell. Since job control is also performed, fg and jobs etc. also move. However, the function is more limited than the shell.

```
> ls - al | less
> egrep str src/*.c
> make && make install && make test
> ./configure --prefix=$HOME --with-optimize --with-interpreter
```

9. You can type in method block types. The following code works.

```
> a: SortableList <String> = slist {1,2,3} .map { it.toString() }
```

10. The script can perform motion reflection at compile time. Since it is done at compile time, the overhead of reflection is 0 at run time.
```
    println("HELLO COMPILE SCRIPT");

    class ReflectionA {
        a:int;
        ClassField: static int;

        def initialize() {
            a = 123;
        }
        def method1() : int {
            123
        }

        def method2(a:int, b:String): String {
            return a.toString.append(b);
        }
    }

    class ReflectionB <T:Object, T2:IEqualable> {
    }

    c :Class = new Class("ReflectionA");
    c.appendField("b", "int");

    c.appendMethod("def setB(b:int) { self.b = b }");
    c.appendMethod("def getB():int { return self.b }");
    c.appendClassField("ClassField2", "String");

    class ReflectionTest
    {
        def main():static {
            a := new ReflectionA();
            Clover.test("refelection test", a.a == 123);
        }
    }

    Clover.appendClass(
        """
        class ReflectionC
        {
            field: String;

            def initialize() {
                field = "ABC";
            }
        }
        """
    );
```

11. Threads are supported.

12. FFI to C Language
```
    class System
    {
        R_OK: static int from unistd.h
        def strcmp(x:pointer, y:pointer): int from libc.so.6
    }
```

You can use C language libraries without creating extension libraries etc.

# Sample code

```
    "A,B,C".split(/,/) {it.append("X"); }
    { AX, BX, CX }

    slist{1,2,3}.map { it * 2 }.each { it.printf("[%d]\n"); }
    [2]
    [4]
    [6]

    > slist{1,2,3,4,5,6,7}.select { it > 3 }.reverse()
    {7,6,5,4}

    > 2.className().scan(/./).map { it.multiply(5) }.join("\n")
    IIIII
    nnnnn
    ttttt
    eeeee
    ggggg
    eeeee
    rrrrr

    > list{1,2,3}.map { it.toString().toCommand() }.each { it.less() }

    > list{uname(), hostname(), pwd()}.each { it.less() }
```

# Operating environment $
I am checking the operation on Linux on x86, PowerPC (32bit, 64bit). I think that it will work with other CPUs. (Because it runs with little endian, bigendian, 32 bit, 64 bit)
Once OSX also moves from version 3.1.2. Since readline is editline in OSX, in order to run REPL, I think that it is necessary to put readline in brew etc. (unconfirmed)
After that I use clang for the compiler.

# License

It is GPL2. Since readline is GPL 2, clover 2 using it is also GPL 2.

# Install

## Dependent library
It is necessary to install the development version of the library dependent on compilation. math, iconv, pcre3, readline, libz, libncursesw There are six libraries required. With Fedora, the library name -devel becomes the development version. Debian type (ubuntu etc.) should be library name -dev. Please search and search for details. In addition, ctags is necessary for the control pile. Please also install ctags. Incidentally, math is a function for mathematics, iconv is multilingualization, pcre is regular expression, readline is the interface of inpreter, and libz is a library for decompressing compressed files. If you want to enable native code compilation with --with-jit to configure option LLVM is required. It is 3.8 and 5.0 in my environment. Then you need GNU make to gcc, clang, make to the compiler.

If you want to use C-Language FFI, please add --with-c-ffi option to configure. In this case, you need libffcall1-dev library.

In ubuntu, Debian
```
    sudo apt-get install gcc
    sudo apt-get install ctags
    sudo apt-get install clang
    sudo apt-get install libreadline-dev
    sudo apt-get install libpcre3-dev
    sudo apt-get install libz-dev
    sudo apt-get install libncursesw5-dev
    sudo apt-get install ctags
    sudo apt-get install make
```
Is required. $

You need libffcall1-dev, if you append --with-c-ffi to configure option.

## Compile

Please get the source code first.
```
    git clone https://github.com/ab25cq/clover2.git
```
You can get it at.
```
    cd clover2
```
As
```
    ./configure --prefix=$HOME --with-optimize
    make
    make install
    make test
```
Please. cclover2 and clover2 are registered in ~/bin/.
If you have administrator privileges
```
    ./configure --with-optimize
    make
    sudo make install
    make test
```
Please. cclover2 and clover2 are registered in /usr/local/bin. If you need an interpreter add the `--with-interpreter` option to `./configure`. An interpreter is entered with the executable file name iclover2. However, the execution code is delicately delayed. (Since the judgment of Signal Interprrupt is embedded in the code). Range of honest error I guess. If you need to compile Method's native code, add the `--with-jit` option to `./configure`. If the behavior is unstable with --with-jit, please remove --with-jit and try it. --with-jit is stable in version 3.5. If you still have a bug, please remove --with-jit and try using it. If segmentation violation occurs with `--with-optimize` depending on the environment, try `--with-optimize` and execute it. Although processing speed will be considerably slow, segmentation violation may not be done.

If you want to install files in a specific directory

```
    ./configure --with-optimize
    make
    make DESTDIR=$HOME/tmp install
```

Please do as. clover2, cclover2 is installed in $HOME/tmp/bin, and the basic library is installed in $HOME/tmp/share/clover2.

Please do as. clover, cclover is installed in /tmp/bin.

## Packaging

In Debian you can install by package. You can create packages with make_deb.sh. The package is installed with install_deb.sh. Uninstallation is sudo apt-get remove clover2.
Packaging is done, so we are looking for a Debian developer who can register the package.
Someone please do m(_ _)m

## release_note

* [release_note](release_note-en)

----

[>> How to use](usage-en)
