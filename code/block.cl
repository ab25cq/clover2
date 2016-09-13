
a:block(int,int):int = block(a:int, b:int): int {
System.println("a -->".append(a.toString));
System.println("b -->".append(b.toString));
    return a + b;
}

Clover.test("block test", a(123,234) == 357);

