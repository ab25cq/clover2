
Clover.test("string test", StringTest3.run().equals("abc123def"));
Clover.test("buffer test", StringTest3.run2().equals(B"abc123def"));
Clover.test("path test", StringTest3.run3().equals(p"abc123def"));
Clover.test("regex test", StringTest3.run4() == /abc123def/);
Clover.test("string test2", StringTest3.run5().equals("abc123def"));
Clover.test("buffer test2", StringTest3.run6().equals(B"abc123def"));
Clover.test("path test2", StringTest3.run7().equals(p"abc123def"));
Clover.test("regex test2", StringTest3.run8() == /abc123def/);
Clover.test("string test3", StringTest3.run9().equals("abc123def"));

