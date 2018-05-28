# Anonymouse class

Anonymous type is a type that can be assigned to any class variable. Conversely, variables of any class can be assigned to variables of Anonymous class. However, the execution result is left to the user. If you use an Integer object but use it as a String object, the system will be dropped. Since the class name of the object at the time of execution can be confirmed by the className () special method, please use it according to the class.

Method calls for Anonymous classes are handled dynamically as well as interfaces. However, unlike the interface, type checking is not done at compile time, and any method can be called. If the method can not be found at run time, a Method not found exception occurs at run time. The return value of the method call to the Anonymous class is always Anonymous. Anonymous is handled at compile time as a return value even if the returned value of the called method is bool. If you want to convert to another type please call cast special method.

```
    a: Anonymous = new Integer (3);
    a.getValue (). cast ("int") == 3;
```


I will do like this. The Integer class has a method named getValue () that accepts the stored numeric value of type int, but since all method calls to Anonymous type are returned by Anonymous type, it is necessary to cast each time. Cast special methods can only be called on Anonymous type.

All user classes except primitive types have special methods to convert to Anonymous type called toAnonymous (). Even when Generics is used, even if there is no problem at runtime, processing that can not be implemented due to compile time type checking problem can be realized using toAnonymous.
