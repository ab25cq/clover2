
Clover.test("cast test1", 255.to_byte == -1)
Clover.test("cast test2", 255.to_byte == -1)
Clover.test("cast test3", 65.to_char == 'A');

Clover.test("cast test4", -1.to_ubyte == 255);
Clover.test("cast test5", -1.to_ubyte.to_byte == -1);

Clover.test("cast test6", -1.to_byte == 255.to_byte);
