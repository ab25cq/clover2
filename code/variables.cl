
a:int = 123;

if(true) {
    b:int = 234;

    Clover.test("variable test1", a == 123 && b == 234);
}

c:int = 345;

if(true) {
    b:int = 456;

    Clover.test("variable test2", a == 123 && c == 345 && b == 456);
}

d:int = 567;

if(true) {
    b:int = 789;

    Clover.test("variable test3", a == 123 && b == 789 && c == 345 && d == 567);
}

Clover.test("variable test4", a == 123 && c == 345 && d == 567);

