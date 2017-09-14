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
System.sleep(1);

Clover.test("jit test9", a.run9().value == 123);

print("jit test10...");
try {
    a.run10();
}
catch(e:Exception) {
    println("OK");
}

a.run11();

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
Clover.test("jit teyst35", a.run35() == 3l);
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
println("FALSE");
}
catch(e:Exception) {
    println("OK");
}
#a.run54();

Clover.test("jit test55", a.run55(1, 2, lambda(x:int, y:int):int { return x + y }) == 3);

a.run56();

Clover.test("jit test57", a.run57() == 777);

JITTest.classField1 = 888;
Clover.test("jit test58", a.run58() == 888);

Clover.test("jit test59", a.run59() == 777);

Clover.test("jit test60", a.run60() == 245);
Clover.test("jit test61", a.run61() == 245l);
a.run62().toString().println();
Clover.test("jit test62", a.run62() == 245.1);
Clover.test("jit test63", a.run63() == 5);
Clover.test("jit test64", a.run64() == 111);
Clover.test("jit test65", a.run65() == 'A');
Clover.test("jit test66", a.run66() == 'a');
Clover.test("jit test67", a.run67() == true);
Clover.test("jit test68", a.run68() == false);
Clover.test("jit test69", a.run69() == true);
Clover.test("jit test70", a.run70() == false);
Clover.test("jit test70.5", a.run70_5()[0] == 1);
Clover.test("jit test70.7", a.run70_7().items(1) == 2);

d:int[] = a.run70_5();

Clover.test("jit test70.5", d[0] == 1 && d[1] == 2 && d[2] == 3);

e:Array<Integer> = a.run70_7();

Clover.test("jit test70.7", e.items(0) == 1 && e.items(1) == 2 && e.items(2) == 3);

Clover.test("jit test71", a.run71().equals( equalable_array { 1, 2, 3 }));

f:List<Integer> = a.run71_1();

Clover.test("jit test71.1", f.items(0) == 1 && f.items(1) == 2 && f.items(2) == 3);

Clover.test("jit test71.2", a.run71_2().equals(equalable_list { 1, 2, 3}));

g:Tuple2<Integer, String> = a.run71_3();

Clover.test("jit test71.3", g.value1 == 1 && g.value2.equals("ABC"));

i:Hash<String, Integer> = a.run71_4();

Clover.test("jit test71.4", i.equals(hash { "ABC":1, "DEF":2 }));

z:lambda(int,int):int = a.run72();
Clover.test("jit test72", z(1,2) == 3);

Clover.test("jit test72.5", a.run72_5() == 234);

Clover.test("jit test72.6", a.run72_6() == 123);
Clover.test("jit test72.7", a.run72_7() == 123.1);
Clover.test("jit test72.8", a.run72_8() == 123.1f);
Clover.test("jit test72.9", a.run72_9() == 123l);
Clover.test("jit test72.a", a.run72_a() == 123y);

Clover.test("jit test73", a.run73() == 12);
Clover.test("jit test74", a.run74() == 123);
Clover.test("jit test75", a.run75() == 123);
Clover.test("jit test76", a.run76() == 123);
Clover.test("jit test77", a.run77() == 65);
Clover.test("jit test78", a.run78() == 1);
Clover.test("jit test78.1", a.run78_1() == 123u);
Clover.test("jit test78.2", a.run78_2() == 123u);
Clover.test("jit test78.3", a.run78_3() == -123);
Clover.test("jit test79", a.run79() == 123y);
Clover.test("jit test80", a.run80() == 123y);
Clover.test("jit test80.1", a.run80_1() == -123y);
Clover.test("jit test81", a.run81() == 123uy);
Clover.test("jit test82", a.run82() == 123uy);
Clover.test("jit test82.1", a.run82_1() == 123s);
Clover.test("jit test82.2", a.run82_2() == 123s);
Clover.test("jit test82.3", a.run82_3() == 123us);
Clover.test("jit test82.4", a.run82_4() == 123us);
Clover.test("jit test82.5", a.run82_5() == -123s);
Clover.test("jit test83", a.run83() == 123ul);
Clover.test("jit test84", a.run84() == 123456l);
Clover.test("jit test85", a.run85() == 123.0f);
Clover.test("jit test86", a.run86() == 123.1f);
Clover.test("jit test87", a.run87() == 123.1f);
Clover.test("jit test87.1", a.run87_1() == 123.0f);
Clover.test("jit test87.2", a.run87_2() == -123.0f);
Clover.test("jit test88", a.run88() == 123.0);
#Clover.test("jit test89", a.run89() == 123.1);
Clover.test("jit test90", a.run90() == 123.1);
Clover.test("jit test90.1", a.run90_1() == 123.0);
Clover.test("jit test90.2", a.run90_2() == -123.0);

y:pointer = &z;
Clover.test("jit test91", a.run91(y).equals(&z));
Clover.test("jit test92", a.run92() == true);
Clover.test("jit test92.1", a.run92_1() == 'A');
#Clover.test("jit test92.2", a.run92_2() == 'A');
#Clover.test("jit test93", a.run93().equals("1.1"));
Clover.test("jit test93.1", a.run93_1().equals("123"));
Clover.test("jit test93.2", a.run93_2().equals("123"));
Clover.test("jit test93.3", a.run93_3().equals("123"));
Clover.test("jit test93.4", a.run93_4().equals("123"));
Clover.test("jit test93.5", a.run93_5().equals("123"));
Clover.test("jit test93.6", a.run93_6().equals("-123"));
#Clover.test("jit test93.7", a.run93_7().equals("123.1"));
#Clover.test("jit test93.8", a.run93_8().equals("123.1"));
Clover.test("jit test94", a.run94().equals("123"));
Clover.test("jit test95", a.run95().equals("a"));
Clover.test("jit test95_1", a.run95_1().equals("a"));
Clover.test("jit test95_2", a.run95_2().equals("true"));
Clover.test("jit test95_3", a.run95_3().equals("false"));

#a.run95_4(y).println();
#System.sleep(3);
Clover.test("jit test95_5", a.run95_5() == 123);
Clover.test("jit test95_6", a.run95_6() == 123);
Clover.test("jit test95_7", a.run95_7() == 123);
Clover.test("jit test95_8", a.run95_8() == 123y);
Clover.test("jit test95_9", a.run95_9() == 123s);
Clover.test("jit test95_10", a.run95_10() == 123l);
Clover.test("jit test95_11", a.run95_11() == 123y);
Clover.test("jit test95_12", a.run95_12() == 123y);
Clover.test("jit test95_13", a.run95_13() == 123y);
Clover.test("jit test95_14", a.run95_14() == 123.0);
Clover.test("jit test95_15", a.run95_15() == 123.0f);
Clover.test("jit test95_16", a.run95_16() == 123.1f);
Clover.test("jit test95_17", a.run95_17() == 123.0f);
Clover.test("jit test95_18", a.run95_18() == 123.0);
#a.run95_19().toString().println();
#System.sleep(10);
#Clover.test("jit test95_19", a.run95_19() == 123.1);
Clover.test("jit test95_20", a.run95_20() == 123.0);
Clover.test("jit test96", a.run96() == 123);
Clover.test("jit test96_1", a.run96_1() == 123);
Clover.test("jit test96_2", a.run96_2() == 123.0f);
Clover.test("jit test96_3", a.run96_3() == 123.0);
Clover.test("jit test96_4", a.run96_4() == -123y);
Clover.test("jit test96_5", a.run96_5() == -123.0);
Clover.test("jit test96_6", a.run96_6() == 123.0);
Clover.test("jit test96_7", a.run96_7() == 123);
Clover.test("jit test97", a.run97() == 123l);
Clover.test("jit test98", a.run98() == 123.0f);
Clover.test("jit test98_1", a.run98_1() == 123);
Clover.test("jit test98_2", a.run98_2() == 123);
Clover.test("jit test98_3", a.run98_3() == 123.0f);
Clover.test("jit test98_4", a.run98_4() == 123l);
Clover.test("jit test98_5", a.run98_5() == 123l);
Clover.test("jit test98_6", a.run98_6() == -1);
#Clover.test("jit test98_6", a.run98_6() == 255);
Clover.test("jit test98_7", a.run98_7() == 123.0);
Clover.test("jit test98_8", a.run98_8() == 123.0);
Clover.test("jit test98_9", a.run98_9() == 123y);
Clover.test("jit test98_10", a.run98_10() == 123);
Clover.test("jit test98_11", a.run98_11() == -1s);
Clover.test("jit test98_12", a.run98_12() == -1y);

printf("a.run98_13() %ld\n", array { a.run98_13() });

Clover.test("jit test98_13", a.run98_13() == 123l);
Clover.test("jit test98_14", a.run98_14() == 123y);
Clover.test("jit test98_15", a.run98_15() == 123.0);
Clover.test("jit test98_16", a.run98_16() == -123.0);
Clover.test("jit test98_17", a.run98_17() == -123);
Clover.test("jit test98_18", a.run98_18() == 65);
Clover.test("jit test98_19", a.run98_19() == 65);
Clover.test("jit test99", a.run99() == 2);

Clover.test("jit test99_1", a.run99_1() == 2l);
#a.run99_2().toString().println();
#System.sleep(3);
#Clover.test("jit test99_2", a.run99_2() == 2.1);
Clover.test("jit test99_3", a.run99_3() == 2);
Clover.test("jit test99_4", a.run99_4() == 2.1);
Clover.test("jit test99_5", a.run99_5() == 2);
Clover.test("jit test100", a.run100() == 2.0f);
Clover.test("jit test101", a.run101() == 2y);
Clover.test("jit test102", a.run102() == 2l);
Clover.test("jit test103", a.run103());

print("jit test 104...");
a.run104(lambda(n:int) { n.toString.println() });
println("OK");

print("jit test 105...");
a.run105();
println("OK");
Clover.test("jit test 106", a.run106() == 123);

#JITTest.callingMethod("AAA", array { 1, 2, 3 } , 1, 1);
#ls("-al")

Clover.test("jit test107", "AAA".equals("AAA"));
Clover.test("jit test108", a.run108());
Clover.test("jit test108.1", a.run108_1().equals("CBA"));
Clover.test("jit test109", a.run109(2, "111").equals("AB111C"));
Clover.test("jit test110", a.run110() == 'B');
Clover.test("jit test111", a.run111() == 'B');
Clover.test("jit test112", a.run112() == 101);
Clover.test("jit test113", a.run113());
Clover.test("jit test114", a.run114());
Clover.test("jit test115", a.run115());
Clover.test("jit test116", a.run116());
Clover.test("jit test116_5", a.run116_5());
Clover.test("jit test116_6", a.run116_6());
Clover.test("jit test116_9", !a.run116_9());

Clover.test("jit test117", a.run117());
Clover.test("jit test-reverse", a.reverse().equals("CBA"));
Clover.test("jit test-insert", a.insert(-2, "111").equals("AB111C"));
Clover.test("jit test-toBuffer", a.toBuffer().equals(B"ABC"));
Clover.test("jit test-indexOf", a.indexOf(/B/, 1) == 1);
Clover.test("jit test-insert2", a.insert2(-1, 7).equals(equalable_list { 1, 2, 3, 7}));
Clover.test("jit test-add", a.add(4).equals(equalable_list { 1, 2, 3, 4 }));
Clover.test("jit test-subBuffer", a.subBuffer(1, -1).equals(B"BC"));

Clover.test("jit test-scan", a.scan(/./).equals(equalable_list {"A", "B", "C"}));
Clover.test("jit test-sub", a.sub(/./, "X", null).equals("XBC"));

a.buffer_initialize(100ul);

k:int = 123;
a.buffer_initialize2(&k, 4ul);

Clover.test("jit test-sub2", "ABC".sub(/A/, "B").equals("BBC"));

Clover.test("jit test-sub2-5", a.sub(/A/g, "X", null).equals("XBC"));
Clover.test("jit test-sub3", "AAA".sub(/A/g, "B").equals("BBB"));
Clover.test("jit test-sub4", "AAA".sub(/^A/g, "B").equals("BAA"));
Clover.test("jit test-scan", "ABC".scan(/./).equals(equalable_list {"A", "B", "C"}));
Clover.test("jit test subString", "ABC".subString(-2, -1).equals("BC"));

group_strings:EqualableList<String> = new EqualableList<String>();
str:String = "ABCD".sub(/(.)(.)$/, "XX", group_strings);

Clover.test("jit test-sub5", str.equals("ABXX") && group_strings.length() == 2 && group_strings.items(0).equals("C") && group_strings.items(1).equals("D"));

str2:String = "ABCD".sub(/(.)(.)$/
            , lambda(match_string:String, group_strings:EqualableList<String>):String { 
                return System.sprintf("%s%s", array { group_strings.items(0), group_strings.items(0) }); 
            });

Clover.test("jit test-sub6", str2.equals("ABCC"));

Clover.test("jit test-match", "ABC".match(/^A/) && "ABC".match(/C$/) && "ABC".match(/B/));

group_strings3:EqualableList<String> = new EqualableList<String>();
Clover.test("jit test-match2", "ABC".match(/^A(.)C/, group_strings3) && group_strings3.length() == 1 && group_strings3.items(0).equals("B"));
Clover.test("jit test-list", equalable_list {1,2,3,1,2,3}.deleteWithRange(2,4).equals(equalable_list {1,2,2,3}));

Clover.test("jit test-split", a.split(/\n/).equals( equalable_list { "ABC" }) );

a.split2(p"/etc/group".read().toString(), /\n/);

zz:Array<Integer> = a.run70_7();

Clover.test("jit test-items", a.items(zz, 0) == 1 && a.items(zz, 1) == 2 && a.items(zz, 2) == 3);

Clover.test("jit test-closure1", a.closure_test1() == 100);
Clover.test("jit test-closure2", a.closure_test2() == 40);

Clover.test("jit test-closure3", a.closure_test3().equals("ABC"));

Clover.test("jit test-file", p"/bin".to_stat().groupName().equals("root"));
Clover.test("jit test-file2", p"/bin".to_stat().userName().equals("root"));
Clover.test("jit test-file3", p"a.txt".to_stat().S_ISREG());
#Clover.test("jit test-file4", p"a.txt".to_stat().mtime().dayOfMonth() == 21 && p"a.txt".to_stat().mtime().month() == 12);
Clover.test("jit test-file5", p"a.txt".read().equals(b"ABCDEFGHI\n"));

f2 := new File("b.txt", System.O_CREAT|System.O_TRUNC|System.O_WRONLY, 0644);
f2.write(b"aaa\nbbb\nccc\n");
f2.close();

Clover.test("jit test-file6", File.read("b.txt").equals(b"aaa\nbbb\nccc\n"));

File.write("c.txt", b"abc\ndef\n");
Clover.test("jit test-file7", File.read("c.txt").equals(b"abc\ndef\n"));
#Clover.test("file test16", p"c.txt".to_stat().permission() == 0644);

p"d.txt".write(b"GGG\n");
Clover.test("jit test-file8", p"d.txt".read().equals(b"GGG\n"));
