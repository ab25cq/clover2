
a:block(int,int):int = block(a:int, b:int): int {
    return a + b;
}

#Clover.test("block test", a(123,123) == 246);

