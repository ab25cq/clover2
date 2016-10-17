
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

f:UByte = new UByte(255);

Clover.test("Byte test2", f.getValue() == 255);
Clover.test("Byte test3", f.toByte().getValue() == -1);

g:Float = new Float(100);

Clover.test("Float test1", g.getValue() == 100);

h:Bool = new Bool(true);

Clover.test("Bool test1", h.getValue() == true);

Clover.test("Integer test1", 123 + 123.toInteger == 246);

i:int = new Integer(123);

Clover.test("Integer test2", i == 123);
