# Syntax

## Free format

Clover2 is a free format. There is no point in particular for line breaks and blanks. Please put your line breaks and spaces freely.

## About variables and functions

A variable is a data container. The machine language level that can be understood directly by the computer called assembler represents memory.
A computer was originally designed to mimic the human intelligence (thought by the British Babbages who did not have children)
There is a place to memorize also in the computer so that there is memory also in humans. At machine language level memory represents it.
A memory is a place to store memory where 1 or 0 is stored in an address called an address (such as an address).
If it can store 1 or 0, it can be called memory. Although I store electronically 1 or 0 now, it seems that it was represented with a gear at the beginning.
The variable is a place to store data like this memory, for example
```
    a: int = 256;
```
And clover2, but in this case the variable named a stores the number 256.
At the machine language level a is an alias for a certain address (for an 8-bit computer, it starts with 0x0000 and ends with 0xFFFF in hexadecimal notation)
A numerical value of 256 is stored there. In human beings it is like memorizing the number 256 in the name a.
Memory can only store 1 or 0, but 256 can be expressed as 0xFF in hexadecimal and 11111111 in 1 binary number as 1 or 0 in binary number.
An int is simply a type of data, which is simply a type of data. For example, in the case of a character string
```
    b: String = "ABC"
```
, Etc. Stored data "ABC" is stored (remembered) in the variable b.
What I am happy to remember when processing data can be handled uniformly when processing data.
I will also explain the function before giving out an example. A function is a unit of procedure. I will name a certain formal process and use it many times.
For example
```
    def show(name: String, age: int) {
        println(name);
        println(age.toString());
    }
```
And defining a function
```
    show("Daisuke Minato", 39);
    show("Yuka Minato", 38)
```
If you call it, etc., you can output different data many times just by making a show once.
Functions can take arguments, and arguments are stored in variables.
In the example above, name is the first argument of type string, age is second argument of numeric type.
println is a function that displays a character string and first displays data named name.
Next, age, age is displayed. .toString() performs type conversion and converts a numeric type to a string type.
Please do not think deeply here.
The execution result of this program is
```
    Daisuke Minato
    39
    Yuka Minato
    38
```
is. The program is made up of variables and functions in this way. Such a programming method is called structured programming.
Before that, there was no function, and a method of directly writing the machine language and processing it from the top to the bottom was taken. I also started from such a language at first
I learned the program. In recent languages ​​structured programming is the minimum condition and a new paradigm comes out.
It is object oriented and clover 2 is an object oriented language.
Object-oriented is made with the idea of ​​handling functions and data as a class together.
There is always a function that has a close relationship with certain data. So, I got it together in class
It is to make the program easier to write and readable.

## Conditional branch and operator

We explained that values ​​can be stored in variables, but use conditional branching if you want to do special processing on certain values.
```
    age: int = 39;
    if(age> = 40) {
        println("40 age over");
    }
    elif(age> = 30) {
        println("30 age over");
    }
    else {
        println("You are young");
    }
    println("END");
```
We use an if statement as above. I put a numerical type of 39 into a variable representing age age.
If this age value is over 40 years old it will be output as 40 age over.
30 age over if over 30 years old. Otherwise it will be displayed as You are young. In this case age has 39, so 30 age over and
It should be displayed.

\>= after age returns true if the comparison is left and right with the comparison operator and the left is greater. If inside of () of if statement is true (true), the contents of {} after that are
It will be executed. After executing {}, elif and else parts are skipped and the last part of println("END"); is executed.
If the value of age is 41, 40 age over is executed and the last println("END"); is executed. else is an if statement or elif statement is true
It will be executed if not (if all is false).
The comparison operators are as follows.
```
    --- comparison operator ---
    operator
    a < b a is less than b
    a <= b a is less than or equal to b
    a> b a is greater than b
    a> = b a is not less than b
    a == b a and b are equal
    a! = b a and b are different
```
Next comes the explanation of arithmetic operators. What is an arithmetic operator It is possible to perform calculations on numeric variables and values ​​by adding and subtracting.
```
    age: int = 39 + 10;
    if(age> = 40) {
        println("40 age over");
    }
    elif(age> = 30) {
        println("30 age over");
    }
    else {
        println("You are young");
    }
    println("END");
```
I put out the above example again and I am doing it + 39 to age 39. Then age will have 49, and this time you should see 40 age over.
```
    --- Arithmetic operator ---
    a + b Addition of a and b
    a - b Returns the result of subtracting b from a
    a * b Returns the result of multiplication of a and b
    a / b Division of a and b
    a% b divide b by b and add too much value
```
By the way, at the end of the line ; is okay with or without clover2. In case of C language or other languages, there are times when it is necessary
It is safe to keep a habit of attaching; in customary manner.

The if statement has a return value. It is as follows.
```
    > a: int = if (true) {123};
    123
    > a
    123
```
Returns the last executed value.
```
    > b: = 123;
    > a: = if(b == 123) { 123 } else { "ABC" }
    > Clover.test("if result test", a.cast("int") == 123);
```
In this case a is anonymous type. Please cast if you use.

## logical operator

If you want to add two conditions to an if statement, use logical operators.
```
    age: int = 39 + 10;
    if(age> = 40 && age <= 49) {
        println("forty (years of age)");
    }
    elif(age> = 30 && age <= 39) {
        println("thirty (years of age)");
    }
    else {
        println("You are young or old");
    }
    println("END");

    a && b "true" when both a and b are true
    a || b "true" if a or b is true
    ! a True if a is false, false if a is true
```
In the above example, if age> = 30 && age <= 39 and age> = 30 is true and age <= 39 is true, the whole expression is true.

## bit operator

Bitwise operators are operators that manipulate data bit by bit. The operable type is an integer.
```
    a & b bitwise AND of a and b
    a | b bitwise OR of a and b
    a ^ b Bitwise exclusive OR of a and b
    << Shift left
    a << b Shift to the left by b bits
    a >> b Shift right by b bits
    ~ a invert each bit of a
```
Bitwise operators are used to handle low-level integers. I will not use it too much at first.
It is used for binary file processing and flag processing.
AND is often used for whether or not a bit contains a numeric value.
OR is often used to include bits in numbers.
You can eliminate some bits by taking & 0xFF etc for bit inversion.

## loop

Loops are for controlling the flow of programs. It is used when you want to iterate.
clover2 has a while statement and a for statement. Anyway, I'll give you an example.
```
    i: int = 1;
    while(i <3) {
        println("HELLO LOOP");
        i++;
    }
    println("END");
```
First of all, the variable i contains 1. Then i <3 of the while statement is executed before entering the while statement. If this is true
I will enter the loop. It is inside {}. Then, HELLO LOOP is executed with println("HELLO LOOP"); Then on i ++
i enters 2. ++ is an increment operator and plus 1 the value of the variable. After that we will return to the beginning of the loop again.
If i <3 is true, execute the loop again. In this case i will be 2 so it will be executed again.
If you run inside the loop again, i should be 3 next time. Since this time i <3 is false, it is not executed in the loop.
The last println("END"); will be executed. In the end, HELLO WORLD is displayed three times, and finally END is displayed. <br>
We move on for statement.
```
    for(i: int = 0; i <3; i ++) {
        println("HELLO LOOP");
    }
    println("END");
```
The results of this program are exactly the same. HELLO LOOP is displayed three times and END is displayed at the end. In detail, first, i: int = 0; in for is executed. And if i <3 is true the inside of the loop will be executed. After executing the loop, i ++ is executed. And if i <3 is true execute the loop again. When i <3 becomes false, we exit the loop.
<br>
If you want to escape a loop in a loop, use a break statement. I often use infinite loops and break statements. It is said that it is not so good not to state the condition in the conditional expression of a while statement, but I think that there are times when there are programs that are easier to read than infinite loops and break statements.
```
    i: int = 0;
    while(true) {
        if(i == 3) {
            break;
        }
        else {
            println("HELLO LOOP");
            i++;
        }
    }
    println("END");
```
This program also displays the HELLO LOOP three times and displays END at the end and finishes with the exact same execution result as the previous loop example. I will explain this program. First, 0 is entered in i. After that, it becomes the conditional expression true of the while statement. If this is true execute the loop. Of course it is true, so it is true no matter how many times it is judged. The conditional expression i == 3 of the if statement is executed. Since i is 0, it is false so the part of else is executed. println("HELLO LOOP"); i ++; i has changed to 1. After that we will be in the conditional expression of the while statement. Since it is true, the loop is executed again. Since i is 1 again, the else statement is executed. HELLO LOOP is displayed and i becomes 2. And we will come to the conditional expression of the while statement. Since it is true, the loop is executed again. Since i is 2, the else statement is executed. HELLO LOOP is displayed and i becomes 3. Since the while statement is true again, the loop is executed again. Since i == 3 of the if statement is true, the if statement block is executed. break; Then we escape from the while statement and the last println("END"); will be executed. In this way break will escape from the loop when executed. Incidentally, there is also a continue statement in C language, but not in clover 2. I use C language for a long time, but I have not used the continue statement only once, so I could not put it in. In most cases, I think that program flow can be controlled with while, for, if, and break. There used to be line numbers and labels, and the program was executed from the top to the bottom, there were no loops, and the flow was controlled using an instruction to move to a specific line number called GOTO statement. Currently we can control the program flow with while, for, if, break instead of the GOTO statement, the GOTO statement and line number are obsolete. There are labels and goto in the C language, but not in clover 2. There is nothing you do not want to use goto sentences. You can make the loop doubly or triple, and you want to escape from that innermost loop. There is no goto statement in clover 2, so in this case you may be in trouble. There is a method of escaping multiple loops using flags as follows, please do so.
```
    flg_loop_out: bool = false;
    value1: int = 128;
    for(i:int = 0; i<3; i++) {
        for(j:int = 0; j<3; j++) {
            for(k:int = 0; k < 3; k++) {
                if(value == 128) {
                    flg_loop_out = true;
                    break;
                }
            }
            if(flg_loop_out) {
                break;
            }
        }
        if(flg_loop_out) {
            break;
        }
    }
```
Although it is a little confusing, when flg_loop_out becomes true, you can escape from all for statements.

## block

A block is useful when you want to execute several expressions with one expression. Use it as follows.
```
    > { println("HELLO"); println("HELLO"); println("HELLO"); }
    HELLO
    HELLO
    HELLO
```
The last executed value is the return value of the block.
```
    > a:int = { 123 };
    123
    > a
    123
```
## comment

The part surrounded by /* and */ (multiple lines possible) becomes a comment.
The one line comment starts from # and ends at the end of line (\n).
```
    /*
       Output Hello World Program
    */
    
    println("HELLO WORLD"); # output HELLO WORLD
```
Comments are not executed. It is deleted at compile time.

## Annotation

Annotation can be added by attaching @ after the type name and the method argument.
Annotation is a type of comment. You can add comments to the arguments of the method so that they are easy to understand.
Annotations can use alphanumeric characters and _.
```
    def fun(str: String, number: int) {
        return str.append(number.toString());
    }
    fun("ABC"@str, 123@number);
    def fun2(str:String@Nullable, p:pointer@int[]) {
        /* Process */
    }
    a := new int[123];
    fun2(null, &a);
```
I will use it like this.

# Nullable

null is an empty value, an instance of the Null class. null can be assigned to variables of all classes except primitive types. However, due to restrictions, null can only be assigned to variables that have? After the class name. Please note that if there is a? After the class name, be careful that null may be included.
```
    a: String = null; # Compile error

    b: String? = null; # null can be substituted. b is empty and null is assigned.
                       # However, you have to code with b carefully to see if it contains null
```

You can use the == and! = Operators to judge whether null is included although it is added later.

```
    str:String? = null; assert(str == null);
```


## primitive class
```
    byte: 8 bit signed numeric type
    ubyte: 8 bit unsigned numeric type
    short: 16 bit signed numeric type
    ushort: 16 bit unsigned number type
    int: 32 bit signed numeric type
    uint: 32 bit unsigned numeric type
    long: 64 bit signed numeric type
    ulong: 64 bit unsigned number type
```
Numeric types have many kinds. It can be determined mainly by the size of the data. The byte type can handle the numerical type of the size of data that can be handled with 8 bits. Since byte is signed, it can handle numbers from -128 to 127. Since ubyte is an unsigned 8 bit, it can handle numbers from 0 to 256. It says something about 8 bit means that memory can handle only 1 or 0, but 8 bits means that you use eight of this memory to express numerical values. In binary numbers it means that you can handle 8 digits such as 11111111 and 01010101. If it is ubyte, the minimum value is 00000000 and the maximum value is 11111111, so if you represent it in hexadecimal as 0x00 to 0xFF, you can handle 0 to 256 numbers. Negative expressions may vary from computer to computer, but in most cases it is normal to treat them as negative numbers if the most significant bit is 1. If it is byte, the minimum value is 10000000 and it becomes -128, and the maximum value becomes 0117111111 as 127. So byte is able to handle numbers from -128 to 127.
```
    float: 32 bit signed floating point
    double: 64-bit signed decimal point
```
float is a floating point type. Decimals can be used. Double can use a smaller decimal smaller than 64 bits. Values ​​are represented as float as 0.1 f, double as 0.11, and so on. In the case of float, f must be attached to decimal.
```
    pointer: type that stores address
```
For details, we will explain later, but it is a primitive class that can handle addresses. clover 2 has a pointer. Pointer manipulation is not protected memory, so incorrect address manipulation causes the script itself to cause a segmentation fault. (Debugging is difficult, so it is hard to fix)
It is safe not to use it except for binary operation. However, if you want to change the value of the caller of the function with an argument (if you want more than one return value for the function) etc., you can use it conveniently. For example
```
    def fun(a: pointer@int): int {
        a->int = 345;
        return 123;
    }
    
    value1: int = 0;
    value2: int = 0;
    value1 = fun(&value2)
    value1.toString().println();
    value2.toString().println();
```
The @ after the type is just an annotation and just a comment. In this case, since the pointer class does not perform type checking, annotation is added in the sense that it wishes to pass an int type address. The output of this program is 123 and 345. I got the address of value 2 with & value 2. It passes that address to the function and assigns 345 as an int type value with a-> int. Then, 345 is assigned to the value 2 passed to fun. Since value 1 is simply assigning the return value of the function, 123 is substituted. The way to pass this argument is called call by refference. The way to pass ordinary arguments is called call by value.
```
    char: type that stores a string type
```
A value representing a character is a type. The expression of the value is 'A' or 'a'. Since clover 2 represents characters and character strings with UTF 32, it is possible to treat Japanese characters as char type.
```
    a: char = 'A';
    b: char = 'あ';

    bool: a type that stores a boolean value
```
It is a type representing a boolean value. It contains true or false.

You can not send a method call to a primitive type. Only operators are eligible.
If you send a method call to a primitive type, the function called boxing works as below, and wrapper class (wrapper class)
The method call is sent to.
Conversely, if you use an operator for a non-primitive type, it is unboxed and computed as a primitive type.

### Representation of Numbers
```
    (Numbers) 123, 256, etc. Represent a number in decimal.
    0x(Numeric value) OxFF, 0x11, etc. Represent a number in hexadecimal.
    0(Numeric values) ​​017, 011, etc. Express the number in octal.
    (Numerical value)f 1.1f, 2.2 , etc. Represents a float type decimal.
    (Numerical value) 1.1, 2.2, etc. Represents a decimal number of type double.
    (Number)y 123y etc. Represents a numeric value of type byte.
    (Numerical)uy 256uy etc. Represents a numeric value of ubyte type.
    (Numerical)s 123s. Represents a short numeric value.
    (Numerical)us 123us etc. It represents ushort type numeric value.
    (Numerical)u 123u. Represents a numeric value of uint type.
    (Number)l 123456l etc. Represents a long type number.
    (Numerical)ul 123456ul and so on. Represents a numeric value of ulong type.
```

    You can add underscores to numbers for easy viewing

```
    1_000_000
```

## array

An array is a collection of values ​​of objects and primitive types accessible by subscripts. You can handle numerical values ​​etc. at once.

You can use it as follows.
```
    > a: int[] = new int[3]();
    3 length array of Integer
    > a[0] = 100;
    100
    > a[1] = 200;
    200
    > a[2] = 300;
    300
    > a[1]
    200
```
There is another way to create an array. I make it as follows.
```
    > a:int[] = [100, 200, 300];
    3 length array of Integer
    > a[1]
    200;
```
In the display, 3 length array of Integer is displayed, but internally an int type array is created. Because the interpreter internally calls toString (), wrapper class (wrapper class) of Array &lt; Integer &gt; array of int [] is created and toString () is called. Primitive types are automatically boxed into wrapper classes when method calls are made.

Why arrays are, but it is useful if you want to process values ​​collectively.
```
    > a:int[] = [100, 200, 300];
    3 length array of Integer
    > for(i:int = 0; i < 3; i++) {
        a[i] = a[i] + 100;
    }
    > a[0];
    200
    > a[1];
    300
    > a[2];
    400
```
In the example above, we are collectively adding + 100 to each array element.

## class

A class is a collection of methods and fields. A method is a procedure belonging to a class by a procedure. A field is a variable belonging to a class.

It is defined as follows.
```
    class Student
    {
        name: String
        age: int
    
        def initialize(name:String, age:int) {
            self.name = name;
            self.age = age;
        }
    
        def getName(): String {
            return self.name;
        }
    
        def getAge(): int {
            return self.age;
        }

        def show() {
            printf("name:%s\nage%s\n", array {self.name, self.age});
        }
    }
```
Class comes after class. A class is a set of functions and is also a variable type. It can also be thought of as parts of the program.
A class is a collection of fields and methods. In the example above, name and age are fields. I think that it is easy to understand when considering it as a container of data.
In this class we show student data. Name can be a string type name by name age by numeric type.
The method writes the method name after def, and writes the argument in (). The method is a program and I will write the instructions sequentially.
The initialize method is called when initializing a class instance (real state) with a special method.
Conversely, defining the finalzie method is called when the instance is destroyed.
An instance of the Stundent class is created as follows.
```
    student_a:Student = new Student("Daisuke Minato", 39);
    student_b:Student = new Student("Yuka Minato", 38);
```
Student_a represents data of a student named Daisuke Minato, and student_b represents student data called Yuka Minato.
At this time, the initialization method defined by def initialize is called. The contents are "Daisuke Minato" and arguments such as 39
It is stored in the field of the instance. self represents that instance.
In this case, we assign the contents of the argument to name and age of the field of the instance.
The value type returned by the method is written after:. If there is no return value: you do not need:
To call a method on a created instance
```
    student_a.show();
    student_b.show();
```
And so on. In this case, since the data is displayed by printf in the show, the contents of the student's data are displayed.
<br>
Unlike other languages ​​self can not be omitted in fields and methods. The type also comes after the variable name.
If you want to define class fields and class methods, put static before the return type.
Please note that you can not put static after the return value. By the way there is no private designation.
I am using array at printf because there is no variable length argument in Clover 2
This is because Array <Object> is taken as the second argument of printf. Anyway, please think that's something like that.
As described above, please save the Student class definition with Student.clc and other file names. The script body that uses that Student class
Student.cl and so on please. Compiling
```
    > cclover2 Student.clcl
```
will do. After compilation, a student.oclcl class file for student data is created.

Execution is
```
    > clover2 Student.cl
```
is.

## Class fields and class methods

Class fields and class methods are class-specific fields and methods.
Creating an instance does not create a new class method or class field. Use it as follows.
```
clcl file

    class Class A {
        classField: static int;
        def classMethod(a:int): static {
            printf("ClassA.classMethod%d\n", array {a});
        }
    }

cl file

    ClassA.classField = 1;
    printf("ClassA.classField%d\n", array {ClassA.classField});
    ClassA.classMethod(2);
```
The execution result is
```
    ClassA.classField1
    ClassA.classMethod2
```
.

If you specify static before the type of the field or before the return type of the method, class fields and class methods are created.
To initialize the class field on the class side, please add static to the initialize method.
Called when the class is loaded. Conversely, when deleting a class, the finalize method is called.
```
clcl file

    class Class B
    {
        classField: static int;
    
        def initialize(): static {
            ClassB.classField = 123;
        }
        def finalize(): static {
            println("ClassB is deleted");
        }
    }

cl file

    printf("ClassB.classField%d\n", array {ClassB.classField});
```
Output is
```
    ClassB.classField123
    ClassB is deleted
```
.

Student: = new Student ("Yuka Minato", 38); You can omit student: = Student ("Yuka Minato", 38) and new though it is a later addition.

## dynamic_class

For objects of dynamic_class, you can call any method name or argument method. A method called callingMethod is called at the time of execution of the invoked method, and you can do concrete processing in it. For example
```
    dynamic_class MyDynamicClass
    {
        def initialize() {
        }
        def callingMethod(method_name:String, params:Array <Object>, num_method_chains:int, max_method_chains:int) {
            if(method_name.equals("hoge") {
                println("hoge");
            }
            elif(method_name.equals("hogehoge") {
                println("hogehoge");
            }
        }
        def callingMethod(method_name:String, params: Array<Object>, num_method_chains:int, max_method_chains:int): static {
            if(method_name.equals("hoge") {
                println("class method hoge");
            }
            elif(method_name.equals("hogehoge") {
                println("class method hogehoge");
            }
        }
    }
```
It is defined as follows. The caller
```
    > a:MyDynamicClass = new MyDynamicClass();
    > a.hoge ();
    hoge
    > a.hogehoge();
    hogehoge
    > MyDnamicClass.hoge()
    class method hoge
```
And so on. params contains an array of argument objects as an array. Since it is an Object type, if you want to process according to the object class of the argument, please use the className () method for processing. num_method_chains contains information on the number of method chains and max_method_chains contains information on how many method chains have continued. But normally you will not use it.

## boxing and unboxing

When a user class becomes an object of an operator, it is unboxed and becomes a primitive type. Conversely, if a primitive type is assigned to an argument of Generics or a method call is made, it is boxed and becomes a corresponding user class. The corresponding user class and primitive class are as follows.
```
    int → Integer
    uint → UInteger
    byte → Byte
    ubyte → UByte
    short → Short
    ushort → UShort
    long → Long
    ulong → ULong
    float → Float
    double → Double
    pointer → Pointer
    char → Char
    bool → Bool
```
.

Buffer class is unboxng'ed to pointer class. So you can run below.

```
    str := strdup(b"ABC");
    strcmp(str, b"ABC") == 0;
    free(str);
```

## Representation of Numbers in Wrapper Class
```
    a: Integer = 5I;
    b: UInteger = 5UI;
    c: Byte = 5Y
    d: UByte = 5UY;
    e: Short = 5S;
    f: UShort = 5US;
    g: Long = 5L;
    h: ULong = 5UL;
    i: Float = 5.5F;
    j: Double = 5.5D;
```

## Primitive type and special field

There is no method call in the primitive type, but there is a special field. Since it is a field, it does not () like a method call. For example
```
    1.to_long
    1.1.to_int
    true.to_int
```
And write it.

The primitive types are as follows
```
    toString → cast to String class
    toByte → cast to Byte class
    toUByte →　cast to UByte class
    toShort → cast to Short class
    toUShort → cast to UShort class
    toInteger → cast to Integer class
    toUInteger → cast to UInteger class
    toLong → cast to Long class
    toULong → cast to ULong class
    toFloat → cast to Float class
    toDouble → cast to Double class
    toPointer → cast to Pointer class
    toChar → cast to Char class
    toBool → cast to Bool class
    to_byte → cast to byte type
    to_ubyte → cast to ubyte type
    to_short → cast to short type
    to_ushort → cast to ushort type
    to_int → cast to int type
    to_uint → cast to uint type
    to_long → cast to long type
    to_ulong → cast to ulong type
    to_float → cast to float type
    to_double → cast to double type
    to_char → cast to char type
    to_pointer → cast to pointer type
    to_bool → cast to bool type
```

The char classes are as follows
```
    to_upper Convert alphabet to lowercase
    to_lower Convert alphabet to uppercase
```
The following array is available.
```
    length Gets the size of the array.
    toArray Casted to an Array class.
```
Regular expression classes are as follows.
```
    global Returns whether there is a global flag or bool
    ignoreCase Returns boolean flag to ignore case when searching
    multiline Returns the multiline flag when searching as bool
    extended whether extended regular expression is used or returned as bool
    dotAll Return dotAll flag as bool
    Return anchored anchord flag as bool
    dollarEndOnly Return the dollarEndOnly flag as bool
    ungreedy Returns the ungreedy flag as bool.
```
## Special method

User classes always have methods that they have.
```
    identifyWith(object: Object): bool
```
Determines whether the object held by the variable is the same.
```
    > a:Integer = new Integer (5);
    5
    > b: Integer = a;
    5
    > b.identifyWith(a)
    true
    > c: = new Integer(6);
    6
    > b.identifyWith(c)
    false
```

It can also be used to judge whether it holds null.
```
    > a:Integer = null;
    Null pointer eception (3)
    compile or runtime error
    > a.identifyWith(null)
    true
```
In the interpreter, an error appears because toString (). Chomp (). Println () has been done. Do not worry too much.

Next is className which gets the class name of the object.
```
    className(): String

    > a: = new Integer (5);
    5
    > a.className ();
    Integer
```
There is toAnonymous() to convert to Anonymous type.
```
    toAnonymous(): Anonymous

    > a: = new Integer (5);
    5
    > b: String = a.toAnonymous ()
    field index is invalid
    compile or runtime error
    > c: Integer = a.toAnonymous ()
    5
```
When converted to Anonymous type, it can be assigned to any type of variable. Type checking can be completely ignored.
In the example above, a is an Integer type and it is assigned to b of the String type, but compilation goes without compile error.
It happens that an error can be detected at runtime and it is an error, but it is a coincidence.
toAnonymous() is a user's responsibility to check for errors.
```
    toNull(): Null
```
Convert it to null. Please use it when you want to suppress return value display by interpreter.
```
    ID(): int
```
Returns the unique ID of the object. It will be used for debugging, especially for users.

```
    allocatedSize():size_t
```

Returns the size of the retrieved memory of the object. It will be used for debugging, especially for users. Mainly expanded. It is used for debugging with Zhang library.

```
    headOfMemory():pointer
```

Returns the starting address of the memory from which the object was retrieved. It is mainly used in extension libraries.

```
    is(class_name: String): bool
```
Check the type of the object and return true if it is an object of the class with the argument class name. After that, if is is done to the variable, make that variable the type of class_name.
```
    a:Anonymous = "ABC";
    if(a.is("String") {
        # a is of type String
    }
    elif(a.is("Integer") {
        # a is Integer
    }

    # a is Integer
```
## interface

An interface defines a method that must be implemented and treats multiple classes with that method in a unified way.
In particular
```
    interface IMyIntereface
    {
        def getValue(): int
        def show()
    }
```
It is defined as follows. Interface names are conventionally preceded by I first. This IMyInterface interface defines that you need to define a method called getValue () which gets an int type value and a method to display the value of show ().
For example
```
    class MyClassA
    {
        def initialize() {
        }
        def getValue(): int {
            return 123;
        }
        def show() {
            println("123");
        }
    }

    class MyClassB
    {
        def initialize() {
        }
        def getValue(): int {
            return 345;
        }
        def show() {
            println("345");
        }
    }
```
Defining a class called
```
    a: IMyInterface = new MyClassA();
```
Ya
```
    b: IMyInterface = new MyClassB();
```
You can substitute MyClassA or MyClassB because getValue () and show () are defined in the IMyInterface variable.
You can call the defined method on the assigned interface, and you can call the method of MyClassA or MyClassB that contains it.
```
    > a.show ();
    123
    > b.show ();
    345
```
When it is convenient, for example, if you use the interface as a method argument. For example
```
    class MyClassC
    {
        def initialize() {
        }
        def show(my_interface: IMyInterface) {
            my_interface.show();
        }
    }
```
Etc. You can pass both Class A and Class B objects as arguments to MyClassC 's show method.
```
    > a: MyClassA = new MyClassA();
    > b: MyClassB = new MyClassB();
    > c: MyClassC = new MyClassC();
    > c.show(a);
    123
    > c.show(b);
    345
```
Polymorphism means that the method called by an object assigned to a variable changes like this. As long as you implement the IMyInterface method, any class can be passed to MyClassC's show, which is convenient.

When implementing the interface, there are times when you want to represent the class itself you are implementing. In that case please use the class name Self.
```
    interface MyInterface2
    {
        def equals(right: Self): bool;
    }
```
We will implement this interface as follows.
```
    class MyClassA
    {
        value: int;
        def initialize(value: int) {
            self.value = value;
        }
        def equals(right: MyClassA): bool {
            return self.value == right.value;
        }
    }
```
For Self part, if you use the class name of the class you are defining, you have implemented MyInterface 2.

## transfer

Transfer is a substitute for inheritance for Clover2 without inheritance. Use it as follows.
```
    class Class B
    {
        def initialize() {}
        def show() {
            println("HELLO delegate");
        }
        def get(): int {
            return 123;
        }
    }

    class ClassA
    {
        b: delegate Class B;
        def initialize () { self.b = new ClassB() }
    }

    a: = new ClassA();
    a.show();
    Clover.test("delegation test", a.get() == 123);
```
It is like this. Methods of the class of the delegate field are defined as methods of the class containing the field. Since def get and def show are defined in Class A, they can also be assigned to interfaces including def get and def show. You can have multiple fields with delegate specification. If methods collide, the method of delegate specified field takes precedence. If methods conflict, you can create your own method with the same name and call your favorite field. Since Clover 2 takes precedence over the method defined later. Even if you want to change the behavior of a delegated field method, if you define a method with the same name in the backward direction, that will take precedence. It's like overwrite in inheritance. <br>
<br>
In internally delegate specified place In the example above, the following methods are defined in Class A: <br>
```
    def get() {
        return self.b.get();
    }
    def show() {
        self.b.show();
    }
```
It is a simple mechanism. You can expect implementation similar to inheritance by including a class that allows implementations to be shared by delegate and that also satisfies interface requirements. I think transfer is a concept above inheritance. Please do not miss it.

## module

Since there is no inheritance in Clover 2, use the module if you want to share the implementation between classes. If a module is simply text and included in the definition of class, that text will be copied and the implemented methods and fields will be available.
```
    module MModuleA
    {
        field: int;
        def getFeild(): int
            return self.field;
        }
    }

    class ClassA
    {
        include MModuleA
        def initialize(num: int) {
            self.field = num;
        }
    }

    class ClassB
    {
        include MModuleA
        def initialize(num: int) {
            self.field = num * 2;
        }
    }
```
As we include MModule A, we can use field field and getField method in Class A and Class B.
Combining modules and interfaces allows you to treat two or more classes as if they were inherited. In this case, for example
```
    interface IInterfaceA
    {
        def getField(): int
    }
```
If you create a variable with type IInterfaceA if you implement the interface named ClassA or ClassB you can substitute it.
```
    a: IInterfaceA[] = new IInterfaceA[2];
    a[0] = new ClassA(123);
    a[1] = new ClassB(123);
    for (i := 0; i < 2; i ++) {
        a[i].getField().toString().println();
    }
```
Combining interfaces and modules like this will result in polymorphism as if they were inherited. Polymorphism is a mechanism in which a method corresponding to an assigned object is called when executing a method in a variable to which a different class which is an object-oriented term has been substituted.

If you want to use the class name of the class itself included in the module, use the class name SELF.
```
    module MEquals
    {
        def equals(right: SELF): bool {
            return self.value == right.value;
        }
    }

    class Class A
    {
        value: int;
        def initialize(value: int) {
            self.value = value;
        }
        include MEquals
    }

    class Class B
    {
        value: float;
        def initialize(value: float) {
            self.value = value;
        }
        include MEquals
    }
```
In Class A, def equals (right: Class A): bool is implemented and Class B implements def equals (right: Class B): bool. This is because the SELF part of the MEquals module changes to Class B when it is included in Class A and when it is included in Class A in Class A when it is included in Class A.
Type checking etc. are not done in the module. Just being compiled with just the text attached. There are times when it becomes an error at that time.

## Generics

Generics of Clover 2 is mainly prepared to realize the collection. Therefore, it is not as sophisticated as Generics in other languages. Definition is as follows.
```
    class MyArray <T:ISortable>
    {
        items: T[];
        def initialize() {
            self.items = null;
        }
        def add(item: T) {
            # ....
        }
    }
```
The class name is followed by &lt; T: ISortable &gt; but T is a class argument. ISortable is an interface that must be implemented. When to use
```
    a: MyArray<Integer> = new MyArray<Integer> ();
```
Pass Integer class argument to MyArray as. Since Integer implements ISortable, it will not cause a compile error. An error occurs if the class argument does not implement ISortable. Since T implements ISortable, T is handled as ISortable in the method definition, and methods implemented by ISortable can be called. <br>

New T() can not be the same as Java. T is an interface, so new can not be done. You can not even new T\[\]().

## Method Generics
```
    def <T:Object, R:AnInterface> method(a: T, b: R): List<T> {
    }
```
It is defined as follows. The type of the return value changes depending on the type of the argument.

## function
```
    def fun(a: int, b: int): int { 123 }
```
If you declare like this, the block object lambda (int, int): int will be assigned to the local variable fun. You can call it like fun(1,2). The scope is the same as the local variable. Since it is just a block object, it can be passed as an argument of a method or assigned to another variable.

## enum
```
    > vim EnumTest.clclc
    class EnumTest {
        enum {Value1, Value2, Value3}
        enum {BValue1, BValue2, BValue3}
    }
    > vim enum_test.cl
    Clover.test("enum test", EnumTest.Value1 == 0 && EnumTest.Value2 == 1 && EnumTest.Value3 == 2 && EnumTest.BValue1 == 0 && EnumTest.BValue2 == 1 && EnumTest.BValue3 == 2 );
    > clover2 enum_test.cl
    enum test ... OK
```
. An enum type element is just a static int to be initialized. It is like sugar-coating syntax.

## Definition of automatic setter and getter

It is now defined automatically when setter and getter define fields. (From version 3.1.9)
```
    > vim SetterAndGetter.clcl
    class SetterAndGetter {
        field1: int;
        field2: String;
        field3: private int;

        def initialize() {}
    }
    > vim setter_and_getter.cl
    a: = new SetterAndGetter ();
    a. field1(123);
    a. field2("ABC");
    Clover.test ("setter and getter", a.field1() == 123 && b.field2().Equals("ABC")));

    # a.field3() is defined, but a.field3(123) is not defined.
```
If you do not care about the default definitions, please define such methods later. Since Clover 2 takes precedence over methods defined later on method search.

## when statement
```
    a: = 123;
    when (a) {
       case 1: {
           println("1");
       }
       case 2, 3: {
           println("2, 3");
       }
       case 123: {
           println("123");
       }
       else {
           println("else");
       }
    }

    a: = "ABC";
    when (a) {
       case "ABC": {
           println("ABC");
       }
       case "DEF", "GHI": {
           println("DEF or GHI");
       }
       else {
           println("else");
       }
    }
```
For user classes IEqualable interface must be implemented. This is because we are comparing values ​​with equals.

There is also a return value for when.
```
    > vim a.cl
    a:int = when("ABC") {
       case ("ABC") {
           1;
       }
       case ("DEF", "GHI") {
           2;
       }
       else {
           3;
       }
    }
    Clover.test("when test", a == 1);
    > clover2 a.cl
    when test ... OK
```
If the return value of when is different, Anonymous type is returned. Please cast and use.
```
    > vim a.cl
    a: = when ("ABC") {
       case "ABC": {
           1;
       }
       case "DEF", "GHI": {
           "ABC
       }
       else {
           new Integer(123);
       }
    }
    Clover.test("when test", a.cast("int") == 1);
    > clover 2 a.cl
    when test ... OK
```
In the when statement you can also use is and! is.
```
    > vim a.cl
    a: = when("ABC") {
       is String {
           1;
       }
       else {
           new Integer (123);
       }
    }
    Clover.test ("when test 2", a.cast ("int") == 1);
    > clover 2 a.cl
    when test 2 ... OK

    > vim a.cl
    a: = when("ABC") {
       ! is Integer {
           1;
       }
       else {
           new Integer(123);
       }
    }
    Clover.test("when test 3", a.cast ("int") == 1);
    > clover 2 a.cl
    when test 3 ... OK
```
Use wildcard as follows. wildcard matches any value.
```
     > vim PaternMatching.clcl

     class PatternMatchingTest
     {
         value1: int;
         value2: String;

         def initialize(value1: int, value2: String) {
             self.value1 = value1;
             self.value2 = value2;
        } $

        def equals(right: PatternMatchingTest): bool {
            return self.value1 == right.value1 && self.value2.equals(right.value2);
        }
     }

     class PatternMatchingTest2
     {
          value1: Integer;
          value2: String;

          def initialize(value1: Integer, value2: String) {
              self.value1 = value1;
              self.value2 = value2;
          }

          def equals (right: PatternMatchingTest 2): bool {
              return self.value1.equals(right.value1) && self.value2.equals(right.value2);
          }
     } $

     > vim a.cl
     a: Anonymous = "ABC";

     c: String = when(a) {
          is String {
               a;
          }
          else {
               "else";
          }
     }

     Clover.test("Pattern matching test", c.equals("ABC")));

     b: Anonymous = new Integer(123);

     d: String = when(b) {
         ! is String {
             "111";
         }
         else {
             "else"
         }
     }

     Clover.test("Pattern maching test 2", d.equals("111")));

     e: Anonymous = new PatternMatchingTest(111, "ABC");

     f: String = when (e) {
         case new PatternMatchingTest(111, "ABC"): {
              "ABC";
         }
         else {
             "DEF";
         }
     }

     Clover.test("Pattern matching test 3", f.equals("ABC")));

     g: Anonymous = new PatternMatchingTest(222, "DEF");

     f = when (g) {
         case new PatternMatchingTest(111, "DEF"): {
             "ABC"
         }
         case new PatternMatchingTest(222, wildcard): {
             "DEF";
         }
         else {
             "GHI";
         }
      }

      Clover.test("Pattern matching test 4", f.equals("DEF")));

      i: Anonymous = new PatternMatchingTest2(123, "ABC");

      j: String = when (i) {
           case new PatternMatchingTest2(wildcard, wildcard): {
                "ABC";
           }
           else {
                "DEF";
           }
       }

       Clover.test("Pattern matching test 5", j.equals("ABC")));
```
However, wildcard can not be assigned to primitive types, so if you want to use wildcard, please use Integer class etc. instead of int class.
If you want to compare values ​​with case statements, you need to implement equals. Well, this is natural.

There is also pattern matching. Use it as follows.

```
    e := new Array<String>();

    f := when(e.className()) {
        match (/.+<String>/) {
            123;
        }
        else {
            456;
        }
    }

    Clover.test("when test5", f == 123);
```

The value of when must be a String. The value of match must be a regular expression.

## Cancel variable declaration

```
    a: = 123;
```
If you declared

```
    unset a
```

Declaration can be canceled. I think that it can be used conveniently in REPL.

## multiple assignment

Tuples can be assigned to multiple local variables.

```
    > (a, b): = (1, 2)
```

The right side value is a tuple. Please see the collection section for details.
a is 1 and b is 2.
It is also possible to exchange the values ​​of variables.

```
    > a: = 1; b: = 2;
    > (a, b) = (b, a)
```

a is 2 and b is 1.
For now, we can only do this multiple assignment with local variables.
Assign to class fields and fields normally.
Also, if you feel like it, you may implement it.

## AUTOMATIC CAST IN ASSEMBLY

In the case of int, short, long, including wrapper classes, mutual automatic casting is done and assignment and arguments of method become different arguments regardless of type. float, double, Float, Double are not automatically cast.

## Exception

I forgot to write, but of course there is also exception handling.

try {
    throws new Exception("TEST");
}
catch(e:Exception) {
    println("catch EXCEPTION");
}

Exceptions are not typed. Determine the exception that occurred in the message in e.message Please.

## Multi line string

I use it as follows

```
    print(
        """
        HELLO WORLD
        HELLO WORLD
        HELLO WORLD
        """);
```

Expansion of variables is used as follows.

```
    name := "Tom";

    print(
        """
        HELLO \{name}
        HELLO \{name}
        HELLO \{name}
        """);
```

Tabs can not be used for indentation. It is only space. If you do not need indentation please use normal string. An ordinary character string can also contain line breaks.

```
    print("HELLO WORLD
    HELLO WORLD
    HELLOWORLD
    ");
```

## Memory-safe pointer

The Buffer class is a class that stores binary data, but it can also be used as a memory-safe pointer

```
    a := b"ABC";
    a++;
    Clover.test("Memory safe pointer test", a->byte == 'B');

    try {
        a+=100;
    } catch(e:Exception) {
        println("Out of range on memory safe pointer");
    }
```

Tests are passed on. An exception occurs when the pointer points out of range as a + = 100, and so on.
Automatic casting to the pointer class is done when necessary as unboxing. When casting, it becomes the address of the pointer that is pointing instead of the starting address.

```
    a := b"ABCDEFGHI";

    a+=2;

    Clover.test("Memory safe pointer test2", memcmp(a, b"CD", 2) == 0);
```

```
    e := b"ABC";

    e++;
    e->byte = '1';
    e--;

    Clover.test("Memory safe pointer test3", memcmp(e, B"A1C", 3) == 0);
```

## Null pointer operator

It often happens that the null decision code is coded. Therefore, Clover 2 has the following simplifying operator.

```
    str:String? = null;

    str?.match(/./)
```

The above code calls match on a variable containing null, but no exception occurs even if it contains null. The match statement is not executed.

# Sugar coating syntax

### sugar-coating syntax of the lambda class

When creating a lambda object which is an argument of a method, the description may be complicated. For that reason sugar coating syntax is prepared. I write as follows.
```
    3.times() { println("HO!"); };
    
    sum: = 0; list {1, 2, 3}. each() { |n: Integer| sum + = n }
    
    str := ""; list { 1, 2, 3 }.map() {|n:Integer|:Anonymous return n.toString(); }.each() {|n:Anonymous| str.append(n.cast("String")); }
```
It is a writing style like Ruby style. A method that takes a block at the last argument can be written like this.

In this case () of the method can be omitted.
```
    list {1,2,3}. each {|n: Integer| println(n.toString())}
```
### Embedding an expression in a string
```
    a:int = 123;
    b:String = "abc \{a.toString()} def";
```
I will do as follows. Embedding expressions in Path, Regex, Buffer is similar.

`toString()` can be omitted:
```
    a:int = 123;
    b:String = "abc \{a} def";
```
Is equivalent to the above code.

### omitted return statement

The return statement of the method can be omitted. The last executed value is returned.
The reutrn statement of lambda can also be omitted if the type of return value is specified explicitly.
```
    def get(): int {123}
```
get returns 123.
```
    a: lambda(): int = lambda() {123}

a () returns 123.
```
### default argument of method
```
    > vim ClassA.clcl
    class Class A {
        def initialize () {}
        def method(a: int, b: int = 2, c: int = 3) {
            return a + b + c;
        }
    }
    > vim a.cl
    a: = new ClassA();
    Clover.test("Method arg default value", a.method (1) == 6);
    > clover 2 a.cl
    Method arg default value ... OK
```
You can set the default value of method arguments as above.

### self omission of methods and fields of the same class
```
    > vim InternalMethodTest.clcl
    class InternalMethodTest {
        def initialize() {}
        def method(): int {
            return method 2 ();
            # return self.method2 () may be written
        }
        def method2(): int {
            return 123
        }
    }
    > vim a.cl
    a: = new InternalMethod();
    Clover.test("internal method test", a.method() == 123);
    > clover 2 a.cl
    internal method test ... OK
```
It is like the above.

Self abbreviation for fields of the same class
```
    > vim InternalFieldTest.clcl
    class InternalFieldTest {
        field: int;
        def initialize(value: int) {
            field = value;
        }
        def get(): {
            return field;
        }
    }
    > vim a.cl
    a: = new InternalFieldTest(123);
    Clover.test("internal field test", a.get() == 123);
    > clover2 a.cl
    internal field test ... OK
```
It is like the above. Although the namespace of the local variable and the field batters, since the local variable takes precedence in the search algorithm, please add self to the field when it is ambiguous. With this algorithm, it was judged that there is no particular problem even if self is omitted. It is compatible with past codes.

## Bridge to C Language

If you want to this function, please compile with --with-c-ffi configure option.

    ```
    ExtensionTest.c

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int getValue(int x, int y) 
    {
        return x + y;
    }

    long getValue2(long x, long y)
    {
        return x + y;
    }

    char* getStr(char* x, char* y) 
    {
        size_t len = strlen(x) + strlen(y) + 1;

        char* result = calloc(1, len);

        strcpy(result, x);
        strcat(result, y);

        return result;
    }

    ExtensionTest.h

    #define ABC 123

    ExtensionClassTest.clcl

    class ExtensionClassTest
    {
        ABC: static int from ExtensionTest.h

        def getValue(x:int, y:int): int from libExtensionTest.so;
        def getValue2(x:long, y:long): long from libExtensionTest.so;
        def getStr(x:pointer, y:pointer): pointer@alloc from libExtensionTest.so;

        def main():static {
            Clover.test("Extension Test1", getValue(1, 2) == 3);
            Clover.test("Extension Test2", getValue2(1l, 2l) == 3l);

            str := getStr(b"ABC", b"DEF");

            Clover.test("Extension Test3", strcmp(str, b"ABCDEF") == 0);

            free(str);

            Clover.test("Extension Test4", ABC == 123);
        }
    }

    CLibrary.clcl

    include "SystemCalls.clcl"

    class System
    {
        def strcmp(x:pointer, y:pointer): int from libc.so.6
    }
    ```

Structures are not supported. Use C language functions that use structures from the native method.

## loval-variable

```
    var a := 123;
    a = 245;

    val b := 123;
    b = 234;   # error

    var c = 123;
    c = 245;

    val d = 123;
    d = 234;   # error
```

Although it is added later, the variable is var variable name = value. readonly is val variable name = value.

----

[<< previous usage](usage-en) [>> next type inference](typing-en)
