
a:lambda(int,int):int = lambda(a:int, b:int):int { return a + b };
b:lambda(int,int):int = lambda(a:int, b:int) { return a + b };
c:lambda(int,int):Anonymous = lambda(a:int, b:int) { return (a+b).toInteger };

Clover.test("type inference test1", a(1,2) == 3);
Clover.test("type inference test2", b(3,4) == 7);

x:Integer = new Integer(7);

Clover.test("Integer test1", x.equals(7));

y:Anonymous = new Integer(7);
Clover.test("Anonymous test1", y.toInteger == 7);
Clover.test("Anonymous test2", y.equals(7.toInteger).to_bool);
Clover.test("type inference test2", c(2,5).toInteger == 7);

d:=0;

Clover.test("type inference test4", d.className().equals("Integer"));

