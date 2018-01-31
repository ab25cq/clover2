# Extension library

Creating extension library for Clover 2 is quite complicated. I think that you can refer to src/class_system.c for how to write source in C language. The point of caution is that the object must exist on the stack of Clover 2. Otherwise it will be judged as a garbage object in GC and deleted. The timing at which GC is invoked is the general function that creates an object. If there is no space at this time GC will be called. I think that it is difficult, please refer to src/class_system.c with reference.

Creating extension library of Clover 2 is complicated, but it is assumed to be implemented mainly as a thin wrapper of C language functions. If you do that, you can create it without much complication. Once data of Clover 2 is prepared for C language data except structure. If the structure is also a pointer, treating it as a pointer type has no particular problem. The problem is when you are using the structure directly, which is troublesome in that case, please pass the each field of the structure as an argument and create a structure on the function side of C language. Then you can define it as a wrapper method of C language functions without any problems.
Define the constant in C language as a class field and initialize with the initialize class method. For initialization, src/class_system.c, File.clc, etc. will be helpful. There is no particular problem if macros in C language are defined as methods.

The following reference sources are ext.clc, ext.cl, ext/hello.c. As a test code, I think that it will be helpful as a way of writing simple extension libraries.

Another point to note is that the native method can only be made static. We can define it as a class method. This is because native method is supposed to be defined as a thin wrapper of C language functions. Once you have prepared a C language wrapper method, the other idea is to use Clover 2 class to write the process.

I will write in detail for a while. First of all, please write the function with reference to ext/hello.c in C language. Then create a dynamic library containing that function. As for how to make dynamic library, there should be a command which makes dynamic library in Makefile, please refer to it. Load it using System.dlopen in the class method initialize of the class whose native method you want to define. Then get a pointer to the function in System.dlsym. Pointer to the function obtained
```
    def put_fun_to_hash_for_native_method (
        path: String, fun_name: String, native_method: pointer): static native;
```

Register in Clover 2 with method.
```
    put_fun_to_hash_for_native_method(
        path: String, fun_name: String, native_method: pointer)
```
For example, the path of the argument of the argument is passed the string "Test.fun(int,int)" for the fun(a:int, b:int) method of the TestA class. There is no space in this "Test.fun(int,int)". If there is no argument, it will be "Test.fun()" etc. The fun_name of the second argument is "Teset_fun". And in C, defining a function called Test_fun is over. Refer to ext.clc for how to register C functions as methods of Clover2.

For details, please look at `ext.clc`,` ext.cl`, `ext/hello.c` and learn how to write C in `src/class_system.c`.

----

[<< Advanced Advanced Usage](usage2-en) [>> Next Postscript](conclusion-en)
