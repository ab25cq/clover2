
Clover.test("printf test1", System.sprintf("%d %d", array { 123, 245 }).equals("123 245"));
Clover.test("printf test2", System.sprintf("%s %d", array { "ABC", 123 }).equals("ABC 123"));
