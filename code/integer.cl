
a:Integer = new Integer(123);

Clover.test("Integer test", a.getValue() == 123);

b:Integer = 345.toInteger;

Clover.test("Integer test", b.getValue() == 345);

c:UInteger = new UInteger(123);

Clover.test("UInteger test", c.getValue() == 123);

d:UInteger = b.toUInteger();

Clover.test("UInteger test2", d.getValue() == 345);

e:Byte = new Byte(123);

Clover.test("Byte test", e.getValue() == 123);

