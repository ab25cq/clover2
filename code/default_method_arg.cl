a := new DefaultMethodArg();

Clover.test("method default value", a.method(2) == 3);
Clover.test("method defautl value2", a.method2(2, 2) == 6);
Clover.test("method default value3", DefaultMethodArg.method3(1) == 4);
Clover.test("method default value4", a.method4(1).equals("ABC1"));
Clover.test("method default value5", a.method5() == 3);

