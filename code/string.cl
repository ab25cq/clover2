
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


