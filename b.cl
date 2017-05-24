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
Clover.test("jit test31", a.run36() == 0xfe);
Clover.test("jit test32", a.run37() == 0xfffffffe);
Clover.test("jit test33", a.run38() == 2.2f);
Clover.test("jit test34", a.run39() == 2.2f);
Clover.test("jit test35", a.run40() == 4.0);
Clover.test("jit test36", a.run41() == true);
Clover.test("jit test37", a.run42() == true);
Clover.test("jit test38", a.run43() == true);
Clover.test("jit test39", a.run44() == true);
Clover.test("jit test40", a.run45() == true);
Clover.test("jit test41", a.run46() == true);
Clover.test("jit test42", a.run47() == true);
Clover.test("jit test43", a.run48() == true);
Clover.test("jit test44", a.run49() == false);
Clover.test("jit test45", a.run50().equals("String"));
Clover.test("jit test46", a.run51() == true);
Clover.test("jit test47", a.run52() == true);
Clover.test("jit test48", a.run53() == 123);

a.run54();

Clover.test("jit test49", a.run55(1, 2, lambda(x:int, y:int):int { return x + y }) == 3);

a.run56();

Clover.test("jit test50", a.run57() == 777);
a.run58();
Clover.test("jit test51", a.run59() == 777);
Clover.test("jit test52", a.run60() == 245);
Clover.test("jit test53", a.run61() == 245l);
Clover.test("jit test54", a.run62() == 245.1);
Clover.test("jit test55", a.run63() == 5);
Clover.test("jit test56", a.run64() == 111);
Clover.test("jit test57", a.run65() == 'A');
Clover.test("jit test58", a.run66() == 'a');
