def fun(a:int, b:int):int {
    return a + b;
}

Clover.test("fun test", fun(111, 222) == 333);
