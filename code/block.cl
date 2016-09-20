
a:block(int,int):int = lambda(a:int, b:int): int {
System.println("a -->".append(a.toString));
System.println("b -->".append(b.toString));
    return a + b;
}

Clover.test("block test", a(123,234) == 357);

c:int = 1;

b:block(int,int):int = lambda(value1:int, value2:int):int {
    return value1 + value2 + c;
}

Clover.test("block test", b(2,3) == 6);

d:block(int,int):int = lambda(value1:int, value2:int):int {
    c = 777;
    return 777;
}

Clover.test("block test", d(111, 222) == 777 && c == 777);

