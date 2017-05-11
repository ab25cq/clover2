a:JITTest  = new JITTest();

b:int = a.run();
Clover.test("jit test", b == 4);

c:String = a.run2();
Clover.test("jit test2", c.equals("ABC"));

Clover.test("jit test3", a.run() == 4);

a.run4();

Clover.test("jit test4", a.run5() == 123.1);

Clover.test("jit test5", a.run6() == 124);

Clover.test("jit test6", a.run7().equals("ABCDEF"));

print("jit test7...");
try {
    a.run8();
}
catch(e:Exception) {
    println("OK");
}

Clover.test("jit test8", a.run9() == true);

Clover.test("jit test9", a.run10() == 2);

Clover.test("jit test9", a.run11() == 1);

Clover.test("jit test10", a.run12() == 2);

Clover.test("jit test11", a.run13() == 3);

Clover.test("jit test12", a.run14() == 1);

Clover.test("jit test13", a.run15() == 123);

a.run17();

Clover.test("jit test15", a.run18() == /./);
Clover.test("jit test16", a.run19());
Clover.test("jit test17", a.run20());
Clover.test("jit test18", a.run21() == 3y);
Clover.test("jit test18", a.run22() == 1y);
Clover.test("jit test19", a.run23() == 1y);
Clover.test("jit test20", a.run24() == 123);
Clover.test("jit test21", a.run25() == 246);
Clover.test("jit test22", a.run26() == 100);
Clover.test("jit test22", a.run27() == 2y);
Clover.test("jit test23", a.run28() == 3y);
Clover.test("jit test24", a.run29() == 2y);
Clover.test("jit test25", a.run30() == 2y);
Clover.test("jit test26", a.run31() == 1y);
Clover.test("jit test27", a.run32() == 1y);
Clover.test("jit test28", a.run33() == 3y);
Clover.test("jit test29", a.run34() == 6y);
Clover.test("jit test30", a.run35() == 3l);
