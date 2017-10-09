
z:int = if(true) { 1 } else { 2 };

a:=999;
b:=1000;

c := if(true) { if(true) { 3 } else { 4} } else { 5 }

d:KotlinTest = new KotlinTest();

Clover.test("if test", d.method2());

e := 888;

Clover.test("if test2", a == 999 && b == 1000 && c == 3 && e == 888);

Clover.test("if test3", KotlinTest.method3(1, "DEF").equals("DEF"));
