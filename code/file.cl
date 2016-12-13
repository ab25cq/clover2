f := new File("a.txt", System.O_RDONLY, 0);
buf := f.read(4)
f.close();

Clover.test("file test1", buf.equals(b"ABCD"));
Clover.test("file test2", File.read("a.txt").equals(b"ABCDEFGHI\n"));
Clover.test("file test3", p"ABC".toString().equals("ABC"));
Clover.test("file test4", p"a.txt".to_stat().size() == 10);

