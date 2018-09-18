
version 6.0.0

    It corresponds to JIT. The raspberry pi 3 editor (vicl) made with Clover 2 moves at a practical speed. It was able to speed up Clover 2 itself considerably. However, in JIT, GC will not do it automatically. Users need to call Clover.gc (). Please put it in the main loop.

version 5.9.9

    Modification of GC algorithm. It got fairly fast. Added Clover.compaction (). For a program running all the time, such as editor please put Clover.compaction () in the main loop. It can reduce memory consumption. JIT does not correspond to the new GC algorithm. JIT is implemented at 6.0.0. For the time being released. The specification of the class file has changed. Please recompile the existing source

version 5.0.9

    Fixed a bug in JIT. I think that this time it was stable.

version 5.0.8

    Multiple assignment of fields and class fields can now be performed.

    Fixed a bug in JIT. I think that this time it was stable.

    Chaged class file definition. Please re-compile the source files.

    The clone, initialize, and nothing methods are no longer automatically defined. Please change the source.

    Fixed comment bug.

version 5.0.7

    Fixed JIT bug and && or || bug.

version 5.0.6

    Tuning using memory. Fixed memory leaks.

version 5.0.5

    Added List.insert(index:int, list_:List<T>)

version 5.0.4

    There was a bug in priorities of && and ||. Fix.

version 5.0.3

    Fixed Memory bug

version 5.0.2

    Fixed Interpreter bug

version 5.0.1

    Chaged GC algorithm. Maybe Clover2 has been more faster.

version 5.0.0

    Chaged GC algorithm. Maybe Clover2 has been more faster.

version 4.9.8

    Added Command.getErrorOutput():Command and Command.getOutputWithError():Command.

version 4.9.7

    Added nothing():SELF method to all classes

version 4.9.6

    Added Hash.map, Hash.selectValues, Hash.keyValues.

version 4.9.5

    Fixed bug with printw, wprintw.

version 4.9.4

    Fixed bug with comment. See code/CommentTest.clcl

version 4.9.3

    Fixed bug with used '#'

version 4.9.2

    Bug fixed of occuring a exception in closure.

version 4.9.1 

    Refactoring method blocks. Return value of block object by lambda can not be omitted>. (For organizing the source)

version 4.9.0

    Fixed method result bug.

    Fixed Generics bug.

    Fixed block object bug

    Added ? and : operator for null checking and exception checking.

version 4.8.9

    Fixed JIT bug

version 4.8.8

    1_000 == 1000

    var a = 1 <==> var a:int = 1 <==> a := 1

version 4.8.7
    
    Fixed Buffer class bug.

version 4.8.6
    
    Fixed Buffer.clone bug.

version 4.8.5

    Appended compare method to SortableList and SortableArray.

version 4.8.4

    Appended appendable flag to Buffer.initialize. You can make Buffer class without copying memory.

version 4.8.3

    Added add, next, prev methods to various basic classes. Added add method to ISortable interface. Added IIteratorable interface. The Generics argument interface of the Range class is now IIteratorable. The Range class must satisfy the IIterato rable interface. Source change is required. Instead, "A" .. "D" etc works. Added sum method to SortableList class. Added toList (), toEqualableList (), toSortableList () method to Range class. The return value and argument of the main method of String.clcl has changed from EqualableList to SortableList. If you used String to specify the argument return type as EqualableList <String> in the code, you will need to change the source. Excuse me.

version 4.8.2

    ___ BEGIN___, ___END___ enclosed sources are now executed before compiling, when compiling classes.


version 4.8.1

    Fixed a bug that caused a bug in the creation of clone method by reflection and the test did not work with JIT.

version 4.8.0

    Added List.multiplyWithSelf(n:Int):SELF<T>;
    Added List.selectWithSelf(block_:lambda(T):bool):SELF<T>;
    Added List.subListWithSelf(start:int, end:int):SELF<T>;
    Added List.fillWithSelf(start:int, end:int, item:T):SELF<T>;
    Added List.fillWithSelf(item:T):SELF<T>;
    Added List.reverseWithSelf():SELF<T>;
    Added List.shuffleWithSelf():SELF<T>;

version 4.7.9

    List.deleteWithRange, EqualableList.deleteWithRange, SortableList.deleteWithRange have changed inner stat.

version 4.7.8

    Fixed bug of REPL.

version 4.7.7

    Fixed a bug in relation between module SELF and Generics.

version 4.7.6

    Added System.mvprintw(y:int, x:int, str:String);
    Added map method to Numeric classes

version 4.7.5
    
    Added Class.getMethods();
    Added String.rindexOf();
    Added Clover.primitiveClassToBoxingClass(name:String);
    Added Clover.boxingClassToPrimitiveClass(name:String);
    Added Bool.if(lambda):Anoymous?
    Added Bool.ifWithException(lambda):Anoymous?
    Added ? post operator. --> str:String? = null; str?.match(/./). It doesn't throw Exception. str := "ABC"; str?.match(/./). It's works.
    Added == and != operator for User Object. str:String? = null; assert(str == null). It works.

version 4.7.4

    Removed List.detete(int,int).

version 4.7.3

    Added List.detete(int,int).

version 4.7.2

    Fixed make test bug

version 4.7.1

    Fixed a bug that could not define a field with generic class nested within class.

version 4.7.0

    Append memory safe pointer(Buffer class) to Clover2. See manual

version 4.6.9

    Fixed bug of thread

verson 4.6.8

    --with-jit and --with-thread is stable on amd64

version 4.6.7

    Now Clvoer2 can have runned on sparc64, maybe other Bigendian Platform.

version 4.6.6

    Fixed memory bug. Test on i686. I have not testted on ppc64 yet.

version 4.6.5

    Added --with-thread option to configuren. --with-optimize can not be attached at the same time. If you add -with-thread we recommend --with-jit as well.

    Fixed bug of jit with thread

version 4.6.4

    Added --with-tread option to configure. If compile without --with-thread, optimizatioin is enabled.
version 4.usec4

    --with-threadオプションをconfigurenに追加。もし--with-threadをつけないと最適化が有効になります。threadは使えませんが、、、。

version 4.6.3

    Fix bug of structure variable initialization.

version 4.6.2

    Fixed bug of method arguments.

version 4.6.1
    
    Fixed a bug in break at method block.

version 4.6.0
    
    Fixed a bug that can not be caught when an exception occurs in block in JIT. You can now break with List.each and so on.

version 4.5.9

    Chaged String.delete definition.

version 4.5.8

    ls, make etc. have been removed from Clover.controllingTerminalPrograms. If you want to control ls, write ls in shell mode and ls () if you do not want terminal control.

version 4.5.7

    Fix important memory bugs.

version 4.5.6

    append String.delete method to Clover2 Library.

    Fixed Range class bug.

    Fixed shell mode bug.

version 4.5.5

    Fixed bug.Maybe stable version.

version 4.5.4
    
    Added "var", "val" keyword for local variable assignment. You can declare readonly varialbe with "val" keyword.

version 4.5.3

    Fixed bug.Maybe stable version.

version 4.5.2

    Fixed bug.

version 4.5.1

    I make c-ffi optional. If you want to use it, please add --with-c-ffi to configure option.

version 4.5.0

    I put a bridge for C. Functions and constants can be imported.

    Buffer class is unboxing to pointer class

version 4.2.7

    Fixed bug of String.insert.

version 4.2.6

    The simplified representation of the value of the Hash class has changed. a:Hash<String, Integer> = ["AAA"=>2, "BBB"=>3].

    Reduce the memory clover2 compiler used

    test in the ppc64, i386

version 4.2.5
    
    Fixed bug of Command Class.

    Fixed bug of JIT

    Fixed bug of Shell mode.

version 4.2.4

    changed when expression

version 4.2.3

    Fixed some bugs.

version 4.2.2

    Added JIT runtime to dynamic library (libclover2.so)

    Turn on running JIT method on Compile Time Scripting.

version 4.2.1

    Fixed JIT bugs.

version 4.2.0

    Modification of GC algorithm. Segmentation violated when finalizers in GC needed more memory, but it was fixed. LLVM was not able to respond properly, but it was fixed. Corresponds to LLVM 3.8 and LLVM 4.0 later.

version 4.1.8

    I created a search path routine for include files of class source files. Files in $ PREFIX / share / clover 2 and ~ /. Clover 2 are searched in addition to the current directory. If you include "MyOwnLibrary.clcl" etc in cclover2 - core a.clcl etc, you can modify the basic library. Fixed a bug in file search routines for class files, modules, and include files. The class file of the current directory takes precedence. Also, the directory where the script file is located is also added to the search routine. I changed the specification of the exception. You can catch not only when calling a method but also when an exception occurs at the top of the script. We have made Clover.onException output the exception message. Please change the output destination when CGI or terminal control. You can do so by overriding Clover.onException (String, bool): static. Fixed a bug that parsing does not pass like -x Fixed a bug that seems to be a command without a character string including a fix thought to be an operator.The class compilation is abolished.

version 4.1.7

    I made a Clover.onException hook. It is executed when an exception occurs.

version 4.1.6
    
    Fixed lambda array object bug.

version 4.1.5

    I have made it possible to execute lambda on lambda's array, so I can do it. Fixed a bug in the clone method.

version 4.1.4

    Now Path class delegates String class

    Added curses library

version 4.1.3

    Fiexed clone method bugs.

version 4.1.2

    Fixed clone method bugs

    Fixed because class fields and field ++, - and so did not move.

version 4.1.1

    Fixed clone method bugs

    Fixed a bug in string expression that removes spaces after that place.

    Fixed because there was a bug in free_object.

version 4.1.0

    The clone method has been added to IEqualable, ISortable and IHashKey. clone is now automatically implemented by reflection at compile time. See Reflection.clcl for details.

version 4.0.9

    I changed the memory management format of the extension library object.

version 4.0.8

    Added several methods to System.

    A library of libbsd-dev or libbsd-devel is required. (Optional, if System.getbsize is enabled)

    With completion of REPL, completion of class field of System class is also effective.

    I made a library of Socket. See Socket.clcl for details.

    port of the system call.

    Porting the ioctl system call.

    Porting of select system call

    Mutex bug may be fixed.

version 4.0.7

    I found Security holl of String.removeTag. Fix.

version 4.0.6

    There was a bug that will handle if it is the end of a regular expression if you use a character that uses / in regular expressions. I tried to avoid it with \/.
 
    Addition of String.removeTag ()

version 4.0.5

    The class field of the System class can now omit the notation System. In other words, access(fname, R_OK) == 0 etc is compiled.

    I put String.decodeFromForm (). It is useful in CGI

    Refactoring processing of identifiers. I think there was a bug. Fix.

    Class names can now be omitted when calling class methods and class fields of the same class.

version 4.0.4

    Multi line string bug was fiexed.

version 4.0.3

    Fixed regex bug.

    Inside String Expression (\{}) it became a block instead of an expression

version 4.0.2

    CSV File was supported. flock was supported.

    Fixed compiler bug.

    Fixed JIT bug.

version 4.0.1

    Started to make CGI library. System.setlocale was appended.

    Fixed compiler bug.

version 4.0.0

    Threads were added. For details, please read the explanation of Thread class.

    def allocSize (): size_t allows you to specify the size of the memory to get from the heap. We mainly use it in extension library.

    The allocSize () special method was added. Returns the size of the memory retrieved from the heap of the object.
        It mainly uses extended libraries, so users will not use them in particular.

    The headOfmemory () special method was added. Returns the starting size of the memory obtained from the heap of the object. It is mainly used for extended libraries, so users will not use them in particular.

    The specification of the class file has been changed. Compiled class files need to be recompiled again. Please recompile.

    Fixed boxing bug of UShort

version 3.7.6

    Added Multi line stirng.

    I added getMethod (name: String), getClassField (name: String), getField (name: String) to lover class. Also add numFields, numMethods, numClassFields fields to the Class class

    I added Clover.isLoaded(name:String), Clover.isDefined(name:String).

    I added Clover.appendClass(code:String).

    new can now be omitted when creating objects.

version 3.7.5
    
    Added Compile time scripting and Reflection.

version 3.7.4

    Added getppid, setsid, getsid, setpgrp, setpigd to System Class
    
    There was a bug in completing method calls for arrays in REPL. Fix.

version 3.7.3

    A simplified expression was added to the expression of the value of hash. a: Hash <String, Integer> = ["AAA": 2, "BBB": 3] is compiled

version 3.7.2

    When assigning a numeric value to a variable, it does not automatically convert to double or float such as int -> float. (int -> long) etc. are implicitly cast

version 3.7.1

    Added Multiple Assignements for local variables

    > (a, b) := (1,2)
    > (a, b) = (b, a)

    An easy thing was added by the notation of a tuple

    > (1,"AAA", 1.1)  # == Tuple<Integer, String, Double>

version 3.7.0

    Fixed command line argument bug.

    System.getopt, System.getopt_long, System.getopt_long_only added.

    -clean, --version, -version option is deprecated (-> command line argument of the same name can not be taken)

version 3.6.9

    Pattern matching has been entered into when. I use it as follows.

    e := new Array<String>();

    f := when(e.className()) {
        match /.+<String>/: {
            123;
        }
        else {
            456;
        }
    }

    Clover.test("when test5", f == 123);

version 3.6.8

    Fixed some bugs and memory leak.

version 3.6.7

    The command suspend was a bug in version 3.6.3. Fix.

version 3.6.6

    The environment variable PWD is now set when the cd command is executed.

    System.setenv's return value changed from Buffer to String

version 3.6.5

    Fixed REPL complementary bug.

version 3.6.4

    Fixed a bug in method calls for arrays that are not primitive types.

    Fixed REPL complementary bug.

    Added Clover.ARGV and ARGC, VERSION.

version 3.6.3

    System.mbstowcs, System.wcstombs API changes. See String.clcl for details.
    System.tcgetatter, System.cfmakeraw API change. See Command.clcl for details.

    Fixed REPL complementary bug.

version 3.6.2

    The class name of System class can be omitted.

    Addition of various system calls

version 3.6.1

    The right side value of the operator of the pointer is okay if it is not ulong. a: = 1; b: = & a; b + = 4 works.

version 3.6.0

    I put new File ("fname.txt", "w"); etc in the file class. Internally it is fopen, fwrite, fread and buffered.

version 3.5.9
    Numeric type conversion is now implicit in method arguments. int -> ulong and so on.

versioin 3.5.8

    I configured configure and handle other CPUs and organize files in the directory.

Version 3.5.7

    We added an instruction called unset variable name. Cancel the variable declaration.

    It corresponds to PowerPC.

Version 3.5.6

We prepared a script to make Debian package. A package is made with make_deb.sh. Installed by install_deb.sh.
There was a bug in loading the basic library. Fix.

version 3.5.6

In order to package the OS, I moved the installation location of the basic library to ${PREFIX}/share/clover2 or ${DESTDIR}/share/clover2.

It made the automatic compiling function simple. When changing the source file, it will not compile automatically.

make DESTDIR=$HOME install, etc now move the software file to $HOME/bin, $HOME/share/clover2.

version 3.5.4

Added document to repository.

version 3.5.3

Added document to repository.

versioin 3.5.2

There was a bug in method block related. Fix.

versioin 3.5.1

There was still a bug in the native code compiler. Bugs frequently occurred related to method blocks. It seems that it was quite unstable. Fixed. Excuse me.

version 3.5.0

Bugs in the native code compiler are gone. It is finished. Please try using ./configure --with-jit without any rest.

version 3.3.1

Boxing and unboxing now occur in method arguments.
I am making a Range class. Added methods of arguments indicating ranges with String class, Buffer class, List class, etc.
Fixed a problem that a field in the same class does not take precedence over a command name.

version 3.3.0

A bug was found in JIT. Fix. JIT moved all test code natively. I think JIT is stable.

version 3.2.9

The source code and line number of the method where the exception occurred becomes easy to understand.

version 3.2.9

There was a bug in the search routines for class fields and class methods. It was quite a fatal bug. Please download.

version 3.2.9

There was a bug in the class file search routine. It was quite a fatal bug. Please download.

version 3.2.9

Type information has been entered into the object. new Array <String> (). className (). equals ("Array <String>") is true.

version 3.2.8

I put an object representation of a numeric wrapper class.

    a: Integer = 5 I;
    b: UInteger = 5 UI;
    c: Byte = 5 Y
    d: UByte = 5 UY;
    e: Short = 5 S;
    f: UShort = 5 US;
    g: Long = 5 L;
    h: ULong = 5 UL;
    i: Float = 5.5 F;
    j: Double = 5.5 D;

version 3.2.7

The specification of when has changed.
I put a wildcard in when.

     > vim PaternMatching.clcl

     class PatternMatchingTest
     {
         value1: int;
         value2: String;

         def initialize (value1: int, value2: String) {
             self.value1 = value1;
             self.value2 = value2;
        } $

        def equals (right: PatternMatchingTest): bool {
            return self.value1 == right.value1 && self.value2.equals (right.value2);
        }
     }

     class PatternMatchingTest2
     {
          value1: Integer;
          value2: String;

          def initialize (value1: Integer, value2: String) {
              self.value1 = value1;
              self.value2 = value2;
          } $

          def equals (right: PatternMatchingTest 2): bool {
              return self.value1.equals (right.value1) && self.value2.equals (right.value2);
          } $
     } $

     > vim a.cl
     a: Anonymous = "ABC";

     c: String = when (a) {
          is String {
               a;
          }
          else {
               "else";
          }
     }

     Clover.test ("Pattern matching test", c.equals ("ABC")));

     b: Anonymous = new Integer (123);

     d: String = when (b) {
         ! is String {
             "111";
         }
         else {
             "else" $
         }
     }

     Clover.test ("Pattern maching test 2", d.equals ("111")));

     e: Anonymous = new PatternMatchingTest (111, "ABC");

     f: String = when (e) {
         case new PatternMatchingTest (111, "ABC"): {
              "ABC";
         }
         else {
             "DEF";
         }
     }

     Clover.test ("Pattern matching test 3", f.equals ("ABC")));

     g: Anonymous = new PatternMatchingTest (222, "DEF");

     f = when (g) {
         case new PatternMatchingTest (111, "DEF"): {
             "ABC"
         }
         case new PatternMatchingTest (222, wildcard): {
             "DEF";
         }
         else {
             "GHI";
         }
      }

      Clover.test ("Pattern matching test 4", f.equals ("DEF")));

      i: Anonymous = new PatternMatchingTest 2 (123, "ABC");

      j: String = when (i) {
           case new PatternMatchingTest 2 (wildcard, wildcard): {
                "ABC";
           }
           else {
                "DEF";
           }
       }

       Clover.test ("Pattern matching test 5", j.equals ("ABC")));

However, wildcard can not be assigned to primitive types, so if you want to use wildcard, please use Integer class etc. instead of int class.

version 3.2.6a
I inserted is and! is in when when.

version 3.2.6

A bug in the if statement was fixed.

version 3.2.5

A stack trace of the source code name and source code number that occurred when an exception occurred now appears.

version 3.2.4

The place that happened when an exception occurred is now output.

version 3.2.3b
There is also a return value for when.

     > vim a.cl
     a: int = when ("ABC") {
        "ABC" {
            1;
        }
        "DEF", "GHI" {
            2;
        }
        else {
            3;
        }
    }
    Clover.test ("when test", a == 1);
    > clover 2 a.cl
    when test ... OK

version 3.2.3 release 2017/12/4

The when expression is entered.

    a: = 123;
    when (a) {
       1 {
           println ("1");
       }
       2, 3 {
           println ("2, 3");
       }
       one two three {
           prinntln ("123");
       }
       else {
           println ("else");
       }
    }

    a: = "ABC";
    when (a) {
       "ABC" {
           println ("ABC");
       }
       "DEF", "GHI" {
           println ("DEF or GHI");
       }
       else {
           println ("else");
       }
    }

For user classes IEqualable interface must be implemented. This is because we are comparing values ​​with equals.

version 3.2.2b Release 2017/12/1

Fixed a bug that can not be compiled correctly if '{' or '... {...' etc is present. Why was there such a bug left? Roz

version 3.2.2a Release 2017/12/1

There was a bug in omission of self in the field. Fix.

version 3.2.2 release 2017/12/1

Self abbreviation for fields of the same class

    > vim InternalFieldTest.clcl
    class InternalFieldTest {
        field: int;
        def initialize (value: int) {
            field = value;
        }
        def get (): {
            return field;
        }
    }
    > vim a.cl
    a: = new InternalFieldTest (123);
    Clover.test ("internal field test", a.get () == 123);
    > clover 2 a.cl
    internal field test ... OK

It is like the above. Although the namespace of the local variable and the field batters, since the local variable takes precedence in the search algorithm, please add self to the field when it is ambiguous. With this algorithm, it was judged that there is no particular problem even if self is omitted. It is compatible with past codes.

version 3.2.1 release 2017/12/1

Self abbreviation for methods of the same class

    > vim InternalMethodTest.clcl
    class InternalMethodTest {
        def initialize () {}
        def method (): int {
            return method 2 ();
            # return self.method2 () may be written
        }
        def method2 (): int {
            return 123
        }
    }
    > vim a.cl
    a: = new InternalMethod ();
    Clover.test ("internal method test", a.method () == 123);
    > clover 2 a.cl
    internal method test ... OK

It is like the above. Self can not be omitted for the field. Because it is convenient for replacing the field name in the editor. After that I think that it is not good to battle local variables and field names.

version 3.2.0 release 2017/11/29

It corresponds to recursive expression of function. When defining a function with def in script, recursion could not be done, but it corresponds.
(You can naturally recurse expressions of class methods)

version 3.1.9 Release 2017/11/28

It is now defined automatically when setter and getter define fields.

    > vim SetterAndGetter.clcl
    class SetterAndGetter {
        field 1: int;
        field 2: String;
        field 3: private int;

        def initialize () {}
    }
    > vim setter_and_getter.cl
    a: = new SetterAndGetter ();
    a. field 1 (123);
    a. field 2 ("ABC");
    Clover.test ("setter and getter", a.field1 () == 123 && b.field2 (). Equals ("ABC")));
    
    # a.field 3 () is defined, but a.field 3 (123) is not defined.

If you do not care about the default definitions, please define such methods later. Since Clover 2 takes precedence over methods defined later on method search.

version 3.1.8b Release 2017/11/26

Make uninstall && ./configure && make && make test & & make It corresponds to compile order of make install.

version 3.1.8 Release 2017/11/24

Enumeration type

    > vim EnumTest.clclc
    class EnumTest {
        enum {Value 1, Value 2, Value 3}
        enum {BValue 1, BValue 2, BValue 3}
    }
    > vim enum_test.cl
    Clover.test ("enum test", EnumTest.Value 1 == 0 && EnumTest.Value 2 == 1 && EnumTest.Value 3 == 2 && EnumTest.BValue 1 == 0 && EnumTest.BValue 2 == 1 && EnumTest.BValue 3 == 2 );
    > clover2 enum_test.cl
    enum test ... OK
. An enum type element is just a static int to be initialized. It is like sugar-coating syntax.

version 3.1.7 Release 2017/11/24

We've included default arguments for the method. I use it as follows.

     > vim ClassA.clcl
     class Class A {
         def initialize () {}
         def method (a: int, b: int = 2, c: int = 3) {
             return a + b + c;
         }
     }
     > vim a.cl
     a: = new Class A ();
     Clover.test ("Method arg default value", a.method (1) == 6);
     > clover 2 a.cl
     Method arg default value ... OK

version 3.1.6 Release 2017/11/21

The is method can now also be called other than the Anonymous method. I think that it is convenient with List & lt; Object & gt;

    > a: = new List <Object> ();
    > a.add (1);
    > a.add ("ABC");
    > a.each {
    > if (it.is ("String"))) {
    > it.printf ("[% s]"); # it is of type String
    >}
    > elif (it.is ("Integer")) {
    > it.printf ("[% d]"); # it is Integer
    >}
    >}

It is like feeling. At that time, I noticed a segmentation violation as I can assign it to an Object type without boxing when I add 1 to List <Object>. I checked the interface properly so that primitive types can not be substituted. We also made boxing of primitive type assignments to the interface. The above code works properly in version 3.1.6.

version 3.1.5b Release 2017/11/21

Specification of is method of Anonymous class has been changed. After the if statement, I returned to the Anonymous class, but now I am leaving the class which is done at the end. I thought about just a little if statement only special.

    a: Anonymous = "ABC";

    if (a.is ("Integer")) {
        #a is Integer
    }
    elif (a.is ("String")) {
        #a is String
    }

    #a is String

version 3.1.5a Release 2017/11/20

Improved algorithm for source file searching during automatic compilation. (Especially not normally affected change)

version 3.1.5 Release 2017/11/20

We solved the problem of circular reference of class.

    > vim ClassA.clcl
    class Class A {
        field1: static int;

        def hello (): static {
            ClassB.hello ();
        }
    }
    > vim ClassB.clcl
    class Class B {
        def hello (): static {
            println ("ClassA.field1 \ {ClassA.field1} \ n");
        }
    }

In the case of such a code, compilation of both Class A.clcl and Class B.clcl does not pass, but it should be as follows.

    > vim ClassA.clcl
    include "ClassB.clcl"

    class Class A {
        field1: static int;

        def hello (): static {
            ClassB.hello ();
        }
    }
    > vim ClassB.clcl
    include "ClassA.clcl"

    class Class B {
        def hello (): static {
            println ("ClassA.field1 \ {ClassA.field1} \ n");
        }
    }

Include in both the circular reference source. Compiling either source goes through compilation.

version 3.1.4 Release 2017/11/18

We have included automatic class compilation function. Classes with class names as file names are automatically compiled.
For example

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

It is like feeling. It is more convenient to keep the class name the same as the file name because it will be automatically compiled.
I began writing another kind of comment in Japanese. That way was better. I would like to make Clover 2 for Japanese people.

version 3.1.2a release 2017/11/18

I made it possible to use fg, jobs, cd in shell mode. I could not use it for a moment.

version 3.1.2 release 2017/11/18

I compiled and tested it with Darwin. It seems that it is working. I will not check it deeply. When calling class fields and class methods then classes starting with lowercase letters can not be called class fields or class methods. There were a couple of things. Since OSX is case-insensitive in file name, it came across with a bug that mistakenly states that list.head etc. is a field of the class called List. Well, I think that class names usually begin with capital letters, so we made these changes. Once classes starting with lowercase letters can be defined. You can not call class fields and class methods of classes with class names that start with lowercase letters.

In the native method of the System class, the check of Null pointer sweeps the segmentation violation, but now it checks everything. Even though it is said that only Null Pointer Exception came to occur. Even if you just know what happened to the user, it's still nice. Oh, that's right. I do not check Null pointer Exception of other native methods ,,, I will do it now.

version 3.1.1 release 2017/11/14

I put in null able.

    a: String = null; # Compile error

    b: String? = null; # null can be substituted. b is empty and null is assigned.
                        # However, you have to code with b carefully to see if it contains null

version 3.1.0 release 2017/11/14

I added the automatic compiling function of the script. The cl file can be executed directly with clover 2 without compiling.

    > vim HelloWorld.cl
    println ("HELLO WORLD");
    > clover2 HelloWorld.cl
    HELLO WORLD

Changing the extension.
<br>
    Ordinary source file cl -> cl <br>
    Class source file clc -> clcl <br>
    Result of compiling ordinary source file clo -> ocl <br>
    Class file clcl -> oclcl <br>
<br>
It is a big change. Excuse me. Sorry to trouble you but please also change the extension of the source file at hand. The extension was changed so that the output file can be deleted all together, such as rm \ *. O \ *. Because there was such a demand.

version 3.0.7 Release 2017/11/14

I created an is method in the Anonymous class. Use it as follows.

    a: Anonymous = "ABC";

    if (a.is ("Integer")) {
        #a is Integer
    }
    elif (a.is ("String")) {
        #a is String
    }

    #a is anonymous

Version 3.0.6a Release 2017/11/13

If you do not want terminal control of the command to control the terminal, attaching the argument --no-controlling-terminal will no longer control the terminal. For example, ls controls the terminal, but if you do the following, terminal control is not done.

list {ls ("- no - controlling - terminal"), hostname (), pwd ()}. each {it.less ()}

version 3.0.6 Release 2017/11/12

Fixed a bug in method block related memory. Because it is a fatal bug that rarely causes segmentation violation, please download it.
It is now possible to omit method return statement in JIT.
All the bugs I knew with this can be fixed. We will make 3.0.6 a stable version.

version 3.0.5d Release 2017/11/11

Fixed REPL complementary bug. It works as expected almost as far as it can be confirmed including method inference of method block.

version 3.0.5c Release 2017/11/10

If you omit the method block return value, using return means that the type check was not done correctly. Fix.
In particular

> a: SortableList <String> = slist {1,2,3} .map {return it.toString ();} <br>

I was getting wrong with the type check.

version 3.0.5b Release 2017/11/09

There was a bug in the if statement. I am correcting it. There was a bug in the return value when there is else. I do not know with a simple code, but it would have been a problem if there was an if statement in the for which loop count would be 3000 times or something. It is a fairly fatal bug, so please download it if possible.

version 3.0.5a release 2017/11/08

There was a deficiency in type inference of method block. slist {1,2,3} .map {it * 3} did not work. Fix.

version 3.0.5 Release 2017/11/07

Shell mode was bad and slist {1, 2, 3} .select {it> 1} etc did not work, but it was fixed.
I am trying to enter the shell mode after searching the command name from the PATH with the compiler.

version 3.0.4a release

1. slist {1, 2, 3}. Each {"ABC" [TAB] was supplemented to be Integer, but it has been fixed.
