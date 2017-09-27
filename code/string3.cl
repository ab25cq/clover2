
Clover.test("string test", StringTest3.run().equals("abc123def"));
Clover.test("buffer test", StringTest3.run2().equals(B"abc123def"));
Clover.test("path test", StringTest3.run3().equals(p"abc123def"));
Clover.test("regex test", StringTest3.run4() == /abc123def/);
