a:JITTest = new JITTest();

b:int = a.run();
Clover.test("jit test", b == 4);


c:String = a.run2();
Clover.test("jit test2", c.equals("ABC"));

println("jit test3");
a.run3();

Clover.test("jit test4", a.run4() == 4);
Clover.test("jit test5", a.run5() == 3);

Clover.test("jit test6", a.run6() == 123.1);

Clover.test("jit test7", a.run7() == 124);

Clover.test("jit test8", a.run8().equals("ABCDEF"));

Clover.test("jit test9", a.run9().value == 123);

print("jit test10...");
try {
    a.run10();
}
catch(e:Exception) {
    println("OK");
}

print("jit test11...");
a.run11();
println("OK");

Clover.test("jit test12", a.run12());
Clover.test("jit test13", a.run13() == 2);
Clover.test("jit test14", a.run14() == 1);
Clover.test("jit test15", a.run15() == 3);
Clover.test("jit test16", a.run16() == 3);

Clover.test("jit test17", a.run17() == 2);
Clover.test("jit test18", a.run18() == 1);
Clover.test("jit test19", a.run19() == 123);

Clover.test("jit test20", a.run20() == /./);
Clover.test("jit test21", a.run21());
Clover.test("jit test22", a.run22());
Clover.test("jit test23", a.run23() == 3y);
Clover.test("jit test24", a.run24() == 1y);
Clover.test("jit test25", a.run25() == 246);
Clover.test("jit test26", a.run26() == 100);
Clover.test("jit test27", a.run27() == 2);
Clover.test("jit test28", a.run28() == 3);
Clover.test("jit test29", a.run29() == 2);
Clover.test("jit test30", a.run30() == 2y);
Clover.test("jit test31", a.run31() == 1y);
Clover.test("jit test32", a.run32() == 1y);
Clover.test("jit test32", a.run32() == 1y);
Clover.test("jit test33", a.run33() == 3y);
Clover.test("jit test34", a.run34() == 6y);
Clover.test("jit test35", a.run35() == 3l);

Clover.test("jit test36", a.run36() == 0xfe);
Clover.test("jit test37", a.run37() == 0xfffffffe);
Clover.test("jit test38", a.run38() == 2.2f);
Clover.test("jit test39", a.run39() == 2.2f);
Clover.test("jit test40", a.run40() == 4.0);
Clover.test("jit test41", a.run41() == true);
Clover.test("jit test42", a.run42() == true);
Clover.test("jit test43", a.run43() == true);
Clover.test("jit test44", a.run44() == true);
Clover.test("jit test45", a.run45() == true);
Clover.test("jit test46", a.run46() == true);
Clover.test("jit test47", a.run47() == true);
Clover.test("jit test48", a.run48() == true);
Clover.test("jit test49", a.run49() == false);
Clover.test("jit test49.5", a.run49_5(&b));
Clover.test("jit test50", a.run50().equals("String"));
Clover.test("jit test51", a.run51() == true);
Clover.test("jit test52", a.run52() == true);
Clover.test("jit test53", a.run53() == 246);

print("jit test53.5...");
try {
    a.run53_5();
}
catch(e:Exception) {
    println("OK");
}

a.run54();

Clover.test("jit test55", a.run55(1, 2, lambda(x:int, y:int):int { return x + y }) == 3);

a.run56();

Clover.test("jit test57", a.run57() == 777);

JITTest.classField1 = 888;
Clover.test("jit test58", a.run58() == 888);

/*
Clover.test("jit test59", a.run59() == 777);

Clover.test("jit test52", a.run60() == 245);
Clover.test("jit test53", a.run61() == 245l);
Clover.test("jit test54", a.run62() == 245.1);
Clover.test("jit test55", a.run63() == 5);
Clover.test("jit test56", a.run64() == 111);
Clover.test("jit test57", a.run65() == 'A');
Clover.test("jit test58", a.run66() == 'a');
Clover.test("jit test59", a.run67() == true);
Clover.test("jit test60", a.run68() == false);
Clover.test("jit test61", a.run69() == true);
Clover.test("jit test62", a.run70() == false);
Clover.test("jit test63", a.run71().equals( equalable_array { 1, 2, 3 }));

z:lambda(int,int):int = a.run72();
Clover.test("jit test64", z(1,2) == 3);
Clover.test("jit test65", a.run73() == 12);
Clover.test("jit test66", a.run74() == 123);
Clover.test("jit test67", a.run75() == 123);
Clover.test("jit test68", a.run76() == 123);
Clover.test("jit test69", a.run77() == 65);
Clover.test("jit test70", a.run78() == 1);
Clover.test("jit test71", a.run79() == 123y);
Clover.test("jit test72", a.run80() == 123y);
Clover.test("jit test73", a.run81() == 123uy);
Clover.test("jit test74", a.run82() == 123uy);
Clover.test("jit test75", a.run83() == 123ul);
Clover.test("jit test76", a.run84() == 123456l);
Clover.test("jit test77", a.run85() == 123.0f);
Clover.test("jit test78", a.run86() == 123.1f);
Clover.test("jit test79", a.run87() == 123.1f);
Clover.test("jit test80", a.run88() == 123.0);
#Clover.test("jit test81", a.run89() == 123.1);
Clover.test("jit test82", a.run90() == 123.1);

y:pointer = &z;
Clover.test("jit test83", a.run91(y).equals(&z));
Clover.test("jit test84", a.run92() == true);
#Clover.test("jit test85", a.run93().equals("1.1"));
Clover.test("jit test86", a.run94().equals("123"));
Clover.test("jit test87", a.run95().equals("a"));
Clover.test("jit test88", a.run96() == 123);
Clover.test("jit test89", a.run97() == 123l);
Clover.test("jit test90", a.run98() == 123.0f);
Clover.test("jit test91", a.run99() == 2);
Clover.test("jit test92", a.run100() == 2.0f);
Clover.test("jit test93", a.run101() == 2y);
Clover.test("jit test94", a.run102() == 2l);
Clover.test("jit test95", a.run103());

Clover.test("jit test97", "AAA".equals("AAA"));

Clover.test("jit test98", a.reverse().equals("CBA"));

Clover.test("jit test99", a.insert(-2, "111").equals("AB111C"));

Clover.test("jit test100", a.run104() == 'B');
Clover.test("jit test101", a.run105() == 'B');

Clover.test("jit test102", a.indexOf(/B/, 1) == 1);
Clover.test("jit test103", a.run106() == 101);
Clover.test("jit test104", a.add(4).equals(equalable_list { 1, 2, 3, 4 }));

Clover.test("jit test105", a.insert2(-1, 7).equals(equalable_list { 1, 2, 3, 7}));

a.buffer_initialize(100ul);

d:int = 123;
a.buffer_initialize2(&d, 4ul);

Clover.test("jit test106", a.subBuffer(1, -1).equals(B"BC"));
Clover.test("jit test107", a.sub(/./, "X", null).equals("XBC"));
Clover.test("jit test108", a.scan(/./).equals(equalable_list {"A", "B", "C"}));
Clover.test("string2 test1", "ABC".sub(/A/, "B").equals("BBC"));
Clover.test("string2 test2", "AAA".sub(/A/g, "B").equals("BBB"));
Clover.test("string2 test3", "AAA".sub(/^A/g, "B").equals("BAA"));

Clover.test("string2 test4", "ABC".subString(-2, -1).equals("BC"));
group_strings:EqualableList<String> = new EqualableList<String>();
str:String = "ABCD".sub(/(.)(.)$/, "XX", group_strings);

Clover.test("string2 test5", str.equals("ABXX") && group_strings.length() == 2 && group_strings.items(0).equals("C") && group_strings.items(1).equals("D"));

str2:String = "ABCD".sub(/(.)(.)$/
            , lambda(match_string:String, group_strings:EqualableList<String>):String { 
                return System.sprintf("%s%s", array { group_strings.items(0), group_strings.items(0) }); 
            });

Clover.test("string2 test6", str2.equals("ABCC"));

Clover.test("string2 tset7", "ABC".match(/^A/) && "ABC".match(/C$/) && "ABC".match(/B/));

group_strings3:EqualableList<String> = new EqualableList<String>();
Clover.test("string2 test8", "ABC".match(/^A(.)C/, group_strings3) && group_strings3.length() == 1 && group_strings3.items(0).equals("B"));
Clover.test("string2 test9", "ABC".scan(/./).equals(equalable_list {"A", "B", "C"}));
Clover.test("List2 test12", equalable_list {1,2,3,1,2,3}.deleteWithRange(2,4).equals(equalable_list {1,2,2,3}));


Clover.test("file test9", p"/bin".to_stat().groupName().equals("root"));
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
*/
