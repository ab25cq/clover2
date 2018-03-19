
a := new ReflectionA();

a.b = 123;

Clover.test("reflection test", a.b == 123);

a.setB(234);

Clover.test("reflection test2", a.getB() == 234);

ReflectionA.ClassField2 = "ABC";

Clover.test("reflection test3", ReflectionA.ClassField2.equals("ABC"));

b:Class = new Class("ReflectionA");

field := b.getField(0);

Clover.test("reflection test4", field.name.equals("a") && field.resultType.equals("int"));

method := b.getMethod(4);

Clover.test("reflection test5", method.name.equals("method2") && method.index == 4 && method.params[0].name.equals("a") && method.params[0].type.equals("int") && method.params[1].name.equals("b") && method.params[1].type.equals("String") && method.resultType.equals("String"));

field2 := b.getClassField(0);

Clover.test("reflection test6", field2.name.equals("ClassField") && field2.resultType.equals("int"));

c:Class = new Class("ReflectionB");

Clover.test("reflection test7", c.genericsParamTypes[0].equals("Object") && c.genericsParamNames[0].equals("T") && c.genericsParamTypes[1].equals("IEqualable") && c.genericsParamNames[1].equals("T2"));

Clover.test("reflection test8", c.flags == Clover.CLASS_FLAGS_ALLOCATED);

