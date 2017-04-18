a:JITTest  = new JITTest();

b:int = a.run();
Clover.test("jit test", b == 4);

c:String = a.run2();
Clover.test("jit test2", c.equals("ABC"));

Clover.test("jit test3", a.run() == 4);

a.run4();

Clover.test("jit test4", a.run5() == 123.1);

Clover.test("jit test5", a.run6() == 124);

Clover.test("jit test6", a.run7().equals("ABC"));
