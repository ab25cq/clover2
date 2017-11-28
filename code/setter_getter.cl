a := new SetterGetter();

a.value(123);
a.value2("ABC");

Clover.test("setter getter", a.value() == 123 && a.value2().equals("ABC"));
