a:JITTest  = new JITTest();

b:int = a.run();
Clover.test("jit test", b == 4);

c:String = a.run2();
Clover.test("jit test2", c.equals("ABC"));

Clover.test("jit test3", a.run() == 4);

#a.run4();
