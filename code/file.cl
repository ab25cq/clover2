f := new File("a.txt", System.O_RDONLY, 0);
buf := f.read(4)
f.close();

Clover.test("Clover test1", buf.equals(b"ABCD"));

f2 := new File("a.txt");
