a:=1;

block {
    b:=2;

    Clover.test("test normal block", a == 1 && b == 2);

    a = 3;
}

Clover.test("test normal block2", a == 3);
