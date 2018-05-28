# Object class

The Object class is an empty interface. Therefore, any object can be assigned. However, only the special method can be called. You can use className (), identfyWith () etc for special methods. Please do className () according to the object class at runtime. If you want to convert it to some class, please use toAnonymous () below. Or the is method may be more convenient.
```
    a: List <Object> = new List <Object> ();
    a.add (1);
    a.add ("ABC");
    a.each (lambda (item: Object) {
        if (item.className (). equals ("Integer") {
            item2: Integer = item.toAnonymous ();
            # Integer processing
        }
        elif (item.className (). equals ("String") {
            item2: String = item.toAnonymous ();
            # String handling
        }
    });
```
Example using is is special method
```
    a: List <Object> = new List <Object> ();
    a.add (1);
    a.add ("ABC");
    a.each {
        if (it.is ("Integer")) {
            # it is Integer
        }
        elif (it.is ("String")) {
            # it is of type String
        }
    });
```