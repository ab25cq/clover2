a:Anonymous = 3;

n:int = 0;
a.times(closure() {
    n++;
});

Clover.test("Anonymous test1", n == 3);

