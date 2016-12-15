f := new File("a.txt", System.O_RDONLY, 0);
buf := f.read(4.to_ulong)
f.close();

Clover.test("file test1", buf.equals(b"ABCD"));
Clover.test("file test2", File.read("a.txt").equals(b"ABCDEFGHI\n"));
Clover.test("file test3", p"ABC".toString().equals("ABC"));
Clover.test("file test4", p"a.txt".to_stat().size() == 10);

/*
f2 := new File("b.txt", System.O_CREAT|System.O_TRUNC|System.O_WRONLY, 0644);
f2.write(b"aaa\nbbb\nccc\n");
f2.close();

Clover.test("file test5", File.read("b.txt").equals(b"aaa\nbbb\nccc\n"));
*/
