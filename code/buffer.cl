a:Buffer = new Buffer();

a.append(b"ABC");
a.append(b"DEF");

Clover.test("buffer test1", a.equals(b"ABCDEF"));
Clover.test("buffer test2", b"ABC".toString().equals("ABC"));

b:Buffer = new Buffer();

b.append(b"ABC");
b.append(b"\0");
b.append(b"ABC");

Clover.test("buffer test3", b.equals(b"ABC\0ABC"));
