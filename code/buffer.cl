a:Buffer = new Buffer();

a.append(b"ABC");
a.append(b"DEF");

Clover.test("buffer test1", a.equals(b"ABCDEF"));
Clover.test("buffer test2", b"ABC".toString().equals("ABC"));
