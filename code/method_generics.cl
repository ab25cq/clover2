a := new MethodGenerics();
b: MethodGenericsInteger = a.method(new MethodGenericsInteger(123), new MethodGenericsInteger(123))

Clover.test("method generics test", b.field == 246);

