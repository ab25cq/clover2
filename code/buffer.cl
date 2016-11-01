a:Buffer = new Buffer();

a.append(b"ABC");
a.append(b"DEF");

Clover.test("string buffer test1", a.equals(b"ABCDEF"));
