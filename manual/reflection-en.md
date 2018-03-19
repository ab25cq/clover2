# Reflection


In reflection, we first create a Class class. The argument of the constructor is the class name.

```
    klass:Class = new Class("ClassA");
```

The flags field contains a class type flag. genericsParamTypes is a string type array containing the name of the interface of generics arguments. genericsParamNames is a string type array containing the names of arguments of generics.

To add a field do the following.
```
    klass.appendField("field1", "int");
```

To add a method, do as follows.

```
    klass.appendMethod("def method1() { 123 }");
```

To add a class field do the following.

```
    klass.appendClassField("classField1", "String");
```

To obtain field information, do as follows.

    klass.getField(0);

0 is the index. Specify numerical values in order of definition. 

To obtain information on a method, do as follows.

    klass.getMethod(0);

0 is the index. Specify numerical values ​​in order of definition. It is important to note that when you define a field, methods of setter and getter are automatically defined, so you may not get the method you want. Since the setter and getter methods are automatically defined when the field is defined, do not forget to specify the index.

Field classes are as follows.

```
    class Field
    {
        flags:long;
        name:String;
        resultType:String;
        #value:Anonymous;

        def private():bool {
            return (self.flags & Clover.FIELD_FLAGS_PRIVATE).to_bool;
        }

        def protected():bool {
            return (self.flags & Clover.FIELD_FLAGS_PROTECTED).to_bool;
        }
    }
```

flags represents the type of field. name is the field name and resultType is the type of the field. 

The data class of the method is as follows.
```
    class Method
    {
        flags:long;
        name:String;
        path:String;
        methodNameAndParams:String;
        index:int;

        params:MethodParam[];

        resultType:String;

        varNum:int;

        genericsParamTypes:String[];
    }
```

flags contains the type of method. name is the method name. path is the method name including the class name. methodNameAndParams contains a string containing method name and type of argument. index contains an index defined sequentially from the top of the method in the class. params is an array of argument information.
```
    class MethodParam
    {
        name:String;
        type:String;
    }
```

name is the variable name of the argument. type is the name of the type of the argument. varNum contains the number of local variables. genericsParamTypes is an array containing the interface names of method generics. that's all. Please try variously and understand.

Please note that appendField and others work only at compile time. Clover 2 is meaningless in compiled languages even if fields and methods are added at run time. Please use it at compile time scripting. Since compile-time scripting can use all the functions of Clover 2, if you create classes for compile-time scripting, Automation can be done a lot. Is it like a macro or preprocessor? Well, please enjoy a lot

