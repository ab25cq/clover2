f := new File("a.txt", System.O_RDONLY, 0);
buf := f.read(4.to_ulong)
f.close();

Clover.test("file test1", buf.equals(b"ABCD"));
Clover.test("file test2", File.read("a.txt").equals(b"ABCDEFGHI\n"));
Clover.test("file test3", p"ABC".toString().equals("ABC"));
Clover.test("file test4", p"a.txt".to_stat().size() == 10);

if(uname().toString().chomp().equals("Darwin")) {
    Clover.test("file test5", p"/etc/../etc".realpath().equals(p"/private/etc"));
}
else {
    Clover.test("file test5", p"/etc/../home".realpath().equals(p"/home"));
}

Clover.test("file test6", p"/etc/passwd".dirname().equals(p"/etc"));
Clover.test("file test7", p"/etc/passwd".basename().equals(p"passwd"));
#Clover.test("file test8", p"/home/ab25cq/repo/clover/a.txt".extname().equals(p"txt"));

if(uname().toString().chomp().equals("Darwin")) {
    Clover.test("file test9", p"/bin".to_stat().groupName().equals("wheel"));
}
else {
    Clover.test("file test9", p"/bin".to_stat().groupName().equals("root"));
}
Clover.test("file test10", p"/bin".to_stat().userName().equals("root"));
Clover.test("file test11", p"a.txt".to_stat().S_ISREG());
#Clover.test("file test12", p"a.txt".to_stat().mtime().dayOfMonth() == 21 && p"a.txt".to_stat().mtime().month() == 12);
Clover.test("file test13", p"a.txt".read().equals(b"ABCDEFGHI\n"));

f2 := new File("b.txt", System.O_CREAT|System.O_TRUNC|System.O_WRONLY, 0644);
f2.write(b"aaa\nbbb\nccc\n");
f2.close();

Clover.test("file test14", File.read("b.txt").equals(b"aaa\nbbb\nccc\n"));

File.write("c.txt", b"abc\ndef\n");
Clover.test("file test15", File.read("c.txt").equals(b"abc\ndef\n"));
#Clover.test("file test16", p"c.txt".to_stat().permission() == 0644);

p"d.txt".write(b"GGG\n");
Clover.test("file test17", p"d.txt".read().equals(b"GGG\n"));
