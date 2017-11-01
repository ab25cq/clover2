
a := new ClassMethodTest();

Clover.test("Class method test", a.get() == 123);

b:lambda():int = lambda():int {
    123;
}

Clover.test("lambda test", b() == 123);
