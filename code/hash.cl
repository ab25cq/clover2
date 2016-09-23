a:Hash<String, Integer> = new Hash<String, Integer>();

a.add("ABC", 1.toInteger);
a.add("DEF", 2.toInteger);

Clover.test("hash test1", a.get("ABC").getValue() == 1);
Clover.test("hash test2", a.get("DEF").getValue() == 2);


#Hash<String, Integer> b = { "ABC":1.toInteger, "DEF":2.toInteger };


