
a := new DelegateClass();

a.show();

println("a.get() is \{a.get()}");

Clover.test("delegate test", a.get() == 345);
Clover.test("delegate test2", a.plus(1, 2) == 3);
