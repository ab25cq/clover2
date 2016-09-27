a:Hash<String, Integer> = new Hash<String, Integer>();

a.put("ABC", 1.toInteger);
a.put("DEF", 2.toInteger);

Clover.test("hash test1", a.get("ABC").getValue() == 1);
Clover.test("hash test2", a.get("DEF").getValue() == 2);

a.put("ABC", 3.toInteger);

Clover.test("hash test3", a.get("ABC").getValue() == 3);

b:Hash<String, Integer> = [ "ABC":123.toInteger, "DEF":234.toInteger ];

Clover.test("hash test4", b.get("ABC").getValue() == 123);
Clover.test("hash test5", b.get("DEF").getValue() == 234);

