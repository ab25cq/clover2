
a := new ResultTest();

a.method2();
a.method3();
a.method4();

Clover.test("result test", a.method().equals("ABC"));

#b:String? = null;

#println("result test2 \{b}");
#println("result test2 \{a.method5()}");

