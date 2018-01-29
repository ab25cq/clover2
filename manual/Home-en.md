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

# Sample code

```
    "A,B,C".split(/,/) { it.append("X"); }
    {AX, BX, CX}

    slist {1,2,3}.map{ it * 2 }.each { it.printf("[%d]\n"); }
    [2]
    [4]
    [6]

    list {1,2,3}.map { it.toString().toCommand() }.each { it.less() }

    list {uname(), hostname(), pwd()}.each { it.less () }
```

# Operating environment

It works with 64 bit and 32 bit INTEL CPU. ARM does not know whether I will run because I do not have an environment.
Please use clang for the compiler. I have not checked the operation even with gcc. If you have some knowledge of C it will be compiled with gcc
I think that it is not difficult.
This means that it is desirable to work with Fedora, Ubuntu, or Debian running on a computer that contains clang today.
Once OSX also moves from version 3.1.2. Since readline is editline in OSX, I think that it is necessary to put readline in brew etc. in order to run the interpreter. (unconfirmed)

# License

It is GPL2. Since readline is GPL 2, clover 2 using it is also GPL 2.

# Install

## Dependent library

It is necessary to install the development version of the library dependent on compilation. We need five libraries: math, iconv, pcre, readline, libz.
With Fedora, the library name -devel becomes the development version. Debian type (ubuntu etc.) should be library name -dev.
Please search and search for details.
In addition, ctags is necessary for the control pile. Please also install ctags.
Incidentally, math is a function for mathematics, iconv is multilingualized, pcre is regular expression, readline is an interpreter interface, and libz is a library for decompressing compressed files.
LWVM is required to enable just-in-time compilation by --with-jit to configure option. It is 3.8 and 3.9 in my environment. I do not know whether it will work with 4.0 or 5.0. (I checked but it does not work)

In ubuntu
```
    sudo apt-get install clang
    sudo apt-get libpcre3-dev
    sudo apt-get intall libz-dev
    sudo apt-get instsall ctags
```
A neighborhood is necessary.

Compile

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
Please. cclover2 and clover2 are registered in /usr/local/bin.
If you need an interpreter
Add the `--with-interpreter` option to `./ configure`. An interpreter is entered with the executable file name iclover2. However, the execution code is delicately delayed. (Since the judgment of Signal Interprrupt is embedded in the code). I think that it is a range of honest error.
If you need to compile Method's native code, add the `--with-jit` option to`./configure`.
If segmentation violation occurs with `--with-optimize` depending on the environment, try `--with-optimize` and execute it. Although processing speed is considerably slow, segmentation violation may not be done. Also, if the operation is unstable with --with-jit, please remove --with-jit and execute it. --with-jit is stable in version 3.5. If you still have a bug, please remove --with-jit and try using it. In case

----

[>> How to use](usage-en)
