

Clover.test("% operator test", 1 % 5 == 1);
Clover.test("% operator test2", 6 % 5 == 1);

Clover.test("<< operator test", 1 << 1 == 2);
Clover.test("<< operator test", 1 << 2 == 4);
Clover.test(">> operator test", 4 >> 1 == 2);
Clover.test("& operator test", (1 & 0) == 0);
Clover.test("| operator test", (1 | 0) == 1);
Clover.test("^ operator test", (1 ^ 1) == 0);
Clover.test("| operator test", (1 | 1) == 1);
Clover.test("& operator test", (1 & 1) == 1);
Clover.test("~ operator test", ~(1.to_byte) == 254);
Clover.test("~ operator test2", ~(0.to_byte) == 255);

Clover.test("? operator test1", (true ? 1 : 2) == 1);
Clover.test("? operator test2", (false ? 1 : 2) == 2);
Clover.test("? operator test3", (false ? 1.toLong : 2.toLong).getValue() == 2);

a:=2;
a*=3;
Clover.test("*= operator test1", a == 6);

b:OpClass  = new OpClass(2);
b.value *= 3;
Clover.test("*= operator test2", b.value == 6);

OpClass.value2 = 2;
OpClass.value2 *= 3;
Clover.test("*= operator test3", OpClass.value2 == 6);


