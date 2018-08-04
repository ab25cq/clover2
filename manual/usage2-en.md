# Advanced usage

## Compile time scripting

You can move Clover 2 in the Clover 2 class source file.
```
    > vim ClassA.clcl
    println("HELLO WORLD");

    class ClassA {
        value1:int;
        value2:int;

        def initialize() {
            value1 = 123;
            value2 = 234;
        }
    }
    > cclover2 ClassA.clcl
    HELLO WORLD
```

This is for what reason it is in order to do reflection at compile time.
```
    > vim ClassA.clcl
    println("HELLO WORLD");

    class ClassA {
        value1:int;
        value2:int;

        def initialize() {
            value1 = 123;
            value2 = 234;
        }
    }

    klass:Class = new Class("ClassA");

    klass.appendField("value3", "int");
    klass.appendMethod("def method1() { value3 = value1 + value2; }");

    > cclover2 ClassA.clcl
    HELLO WORLD
```

In the above code, Class A has a field called value3, and method1 assigns the sum of value1 and value2 to value3.
Scripting of this compile time is executed at the timing after compilation is over. Please be aware of that. With this, if there is a certain field, you can write various processes such as implementing a specific method. Please see the explanation of reflection class for details.

___ BEGIN___, ___END___ enclosed sources are now executed before compiling, when compiling classes from verions 4.8.2.

## Just-in-time compilation

To enable JIT, please conifgure compile with --with-jit option. The byte code of the class file is compiled into native code when compiling the class file of Clover2, and a dynamic library is created. Clover2 is not compiled into native code at run time. For that reason Clover 2's JIT is fast. I think that a mere native code compiler rather than JIT is the correct way of calling. Speed ​​is about 3 times speed of bytecode. However, please be sure to include $ HOME/.clover2 in the environment variable LD_LIBRARY_PATH because it is being executed by the dynamic library. If it is not added to the search path of the dynamic library, the dynamic library is not searched, so it will be executed by bytecodes. When registering user-created class files in $HOME/.clover2, please also copy lib[class name].so, lib[class name].so.1.0.0 to $HOME/.clover2. User-created classes are also executed by native code.

In order to compile from a class file into a dynamic library it is necessary to compile with bclover 2. For example, for Hash.oclcl you need to be bclover2 Hash.oclcl.

## Interactive program execution

It is started by executing the command iclover2. The command can be executed interactively, the command is internally compiled, and the binary for that virtual machine is executed by the virtual machine contained in iclover2.
```
    > 1 + 1; 2 * 4
    2
    8

    > "ABC" .append ("DEF")
    ABCDEF

    > a: = 2
    2
    > a * 2
    4
```
External commands can also be called easily, commands to control terminals, less, vim, etc. can also be executed.
```
    > pwd ()
    /home/ab25cq
    > pwd().toString().subString(1,5).toCommand().less()
    home/
```
Job control is also possible. When CTRL-Z is pressed while vim or less etc is being executed, the program is suspended (paused) and control returns to iclover2.
If you want to return control to the suspended (paused) program
```
    > Clover.jobs.items(0).forground()
```
In other words, you can return control. 0 can suspend multiple programs with the job number, so specify a specific program by number.
If you want to see a list of jobs
```
    > Clover.jobs
```
If you run it, a list of paused programs will be returned in the list.
In other words, when you suspend, an instance of Job type is added to the list named Clover.jobs.
If you want to see detailed behavior and you can see UNIX C, you can see how it is done internally by looking at the source file called Command.clcl.

A list of programs to control terminals is contained in EqualableList&lt;String&gt; called Command.controllingTerminalPrograms. If you want to add it please add the program name to this list.
```
    > vim("MyOwnLibrary2.clcl")
    include "MyOwnLibrary.clcl"
    class Command
    {
    def initialize(): static {
         inherit ();

         Command.controllingTerminalPrograms.add("mfler4");
         Command.controllingTerminalPrograms.add("xyzsh");
         }
    }
```
You can add as. If you want to force terminal control, you can add it with an argument "--controlling-terminal". For example
```
    > make("-controlling-terminal").toBool () && make("-contorlling-terminal", "install").toBool()
```
If you run it and so on, make can get the return value with toBool () while controlling the terminal.

Conversely, if you do not want to control the terminal, you can do so by adding an argument "-no-contolling-terminal". 

Error output is not passed to the next method by default, but it is possible by attaching the argument "-getting-stderr". For example
```
    > make("-getting-stderr").head ()
```
If you do so, both standard output and error output of make will be processed with head ().

Use System.system () if you want to execute the program in the current directory. For example if ./configure --with-debug-prefix = $HOME
```
    System.system ("./configure --with-debug --prefix=$HOME")
```
And so on.

When you press the TAB key, you can supplement (supplement) input depending on the context, you can also use completion of command name, completion of method name, completion of file name.
```
    > 1.[TAB key]
    List of methods of type Integer
    > 123.toString().[TAB key]
    Method list of String type
    > ls[TAB key]
    List of commands named ls
    > ls("src/ma[TAB key]
    src/main.c"and file names are aided for input
```
I think that it can be used conveniently because it can be used interactively and external commands can be easily executed.

# Shell mode

Although it is a later addition, it can also be described like a shell for convenience when running an interactive program.
(Because it is inconvenient for commands such as vim to run many times as CIER 2 grammar necessarily increases the number of types)

ls -al src/main.c etc can also be executed.
```
    > ls -al main.c
    -rw-r-r- 1 ab25cq ab25cq 1098 Sep 23 10: 46 src/main.c
```
Shell commands such as cd, fg, jobs are also included. It is a method of the Command class

Gloves can also be used.
```
    > egrep main src/*.c
    src/compiler.c: int main (int argc, char ** argv)
    src/interpreter.c: int main (int argc, char ** argv)
    src/main.c: int main (int argc, char ** argv, char * const * envp)
```
Pipes can also be used.
```
    > ls -al | less
```
Internally it is all converted to the method of the Command class. It is just sugar coating syntax.
```
    > echo $HOME
    /home/ab25cq
```
We also expand environment variables.
```
    > egrep "str str" src/*.c
    > egrep str \ str src/*.c
    > egrep 'str str' src/*.c
```
There are also quotes.
```
    > make && make install && make test
```
There are also & amp; & amp; and ||.
```
    > ./configure --with-optimize
```
You can execute commands by path only in the current directory and parent directory. It can not run /usr/bin/ bash.
(Because regular expression and grammar overlap)
In that case run bash, zsh or yash and run it on the shell or System.system ("/usr/bin/bash") etc.

Shell mode is only a bonus. The shell should use a proper shell after all. It is a function I personally make for use instead of shell.

However, one important point is that when written in shell mode, the last program is terminal controlled. That is, `ls` is terminal-controlled, but `ls()` is not terminal-controlled. Take care of that point and write code.

[<< Previous library reference](libraries-en) [>> extension library](extension-en)
