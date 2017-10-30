a := new MethodGenerics();
b: MethodGenericsInteger = a.method(new MethodGenericsInteger(123), new MethodGenericsInteger(123))

Clover.test("method generics test", b.field == 246);

c: MethodGenericsInteger2 = a.method2(new MethodGenericsInteger(1), new MethodGenericsInteger2(2));

Clover.test("method generics test2", c.field == 3);

d:List<MethodGenericsInteger> = a.method3() {|it:Object|
    return new MethodGenericsInteger(it.toAnonymous().cast("Integer").value);
}

sum := 0;
d.each() {|it:MethodGenericsInteger|
    sum += it.field;
}

Clover.test("method generics block test", sum == 6);

