
a: BlockTestClass = new BlockTestClass();

#Clover.test("Block test", a.method(2, 3) == 6 || a.method(2, 3) != 6);  # invalid block var access 
