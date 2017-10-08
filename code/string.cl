Clover.test("String test1", "ABC".length() == 3);

a:String = "ABC";
Clover.test("String test2", a.equals("ABC"));
Clover.test("String test3", !a.equals("DEF"));

b:String = "DEF";
Clover.test("String test4", b.equals("DEF"));
Clover.test("String test5", !b.equals("ABC"));

c:String = new String("GHI");

Clover.test("String test6", c.equals("GHI"));

c.append("111");

Clover.test("String test7", c.equals("GHI111"));

Clover.test("String test8", "ABC".append("123").equals("ABC123"));
Clover.test("String test9", !"AAAA".equals("BBBBBBBBBBBBBBBBB"));

"ABC".subString(1,3).println();
Clover.test("String test10", "ABC".subString(1,3).equals("BC"));
Clover.test("String test11", "ABC".insert(1, "111").equals("A111BC"));
Clover.test("String test12", "ABC".insert(-1, "111").equals("ABC111"));
Clover.test("String test13", "ABC".insert(-2, "111").equals("AB111C"));
Clover.test("String test14", "ABC".insert(5, "111").equals("ABC111"));
Clover.test("String test15", "ABC".insert(-5, "111").equals("111ABC"));

