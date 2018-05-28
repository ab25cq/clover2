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
    klass.appendMethod("def method1() { 123 }");
```

To add a class field do the following.

```
    klass.appendClassField("classField1", "String");
```

To obtain field information, do as follows.
```
    klass.getField(0);
```
0 is the index. Specify numerical values in order of definition. 

```
    klass.getField("field1");
```

You can get fields by name.

To obtain information on a method, do as follows.
```
    klass.getMethod(0);
```
0 is the index. Specify numerical values ​​in order of definition. It is important to note that when you define a field, methods of setter and getter are automatically defined, so you may not get the method you want. Since the setter and getter methods are automatically defined when the field is defined, do not forget to specify the index.

```
    klass.getMethod("method1");
```

You can get methods by name.

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

The class class is defined as follows.

```
    class Class
    {
        className:String;
        flags:long;
        genericsParamTypes:String[];
        genericsParamNames:String[];
        numFields:int;
        numClassFields:int;
        numMethods:int;
    }
```

The number of fields in Class is numFields, the number of class fields is numClassFields, and the number of methods is numMethods. Class flags are obtained with flags, generics information is obtained with genericsParamTypes, genericsParamNames. genericsParamTypes contains the type of interface of the generics argument. genericsParamNames is the name of the argument of generics.

Clover.isLoadedClass(name: String) is known by the bool value whether the class is loaded. Clover.isDefinedClass(name: String) knows if a class is defined. (Whether there is a class file).

You can also define classes with Clover.append (code: String).
```
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

Please note that appendField and others work only at compile time. Clover 2 is meaningless in compiled languages even if fields and methods are added at run time. Please use it at compile time scripting. Since compile-time scripting can use all the functions of Clover 2, if you create classes for compile-time scripting, Automation can be done a lot. Is it like a macro or preprocessor? Well, please enjoy a lot

For compile - time reflection, the Clover.compileTimeScriptingOnDeclareTime () class method is called when declaring fields and methods> before the Clover.compileTimeScripting () class method is executed before the compile - time script is executed. If you add a method etc. to the class here, you can automatically add a method or add a field when defining the class. See Reflection.clcl for details.

