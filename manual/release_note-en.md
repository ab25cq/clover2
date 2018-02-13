
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
