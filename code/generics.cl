
a:GenericsTestClass = new GenericsTestClass();
b:GenericsTestClass2 = new GenericsTestClass2();

c:GenericsTest1<GenericsTestClass, GenericsTestClass2> = new GenericsTest1<GenericsTestClass, GenericsTestClass2>(a, b);

Clover.test("generics test1", c.method(123) == 123);
Clover.test("generics test2", c.method2(a) == 123);
Clover.test("generics test3", c.getField().method(123) == 123);
Clover.test("generics test3", !c.getField2().isNull);


