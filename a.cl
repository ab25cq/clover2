
a:ClassA = new ClassA(111, 222);

Clover.test("test", a.method3() == 333);
#Clover.test("test", a.method() == 333 && a.method2() == 333 && a.method3() == 333 && a.method4() == 333 && a.toString().equals("ABC") && a.toString2().equals("DEF"));

