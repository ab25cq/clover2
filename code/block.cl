
a:lambda(int,int):int = lambda(value1:int, value2:int): int {
System.println(value1.toString);
System.println(value2.toString);
    return value1 + value2;
}

Clover.test("lambda test1", a(123,234) == 357);

/*
c:int = 1;

b:lambda(int,int):int = closure(value1:int, value2:int):int {
    return value1 + value2 + c;
}

Clover.test("lambda test2", b(2,3) == 6);

d:lambda(int,int):int = closure(value1:int, value2:int):int {
    c = 777;
    return 777;
}

Clover.test("lambda test3", d(111, 222) == 777 && c == 777);

e:lambda(int,int):int = lambda(value1:int, value2:int):int {
    return value1 + value2;
}

Clover.test("lambda test4", e(1, 2) == 3);
*/
