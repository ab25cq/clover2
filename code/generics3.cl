
test:int = GenericsTest3<GenericsTest3ClassA, String>.method(new GenericsTest3ClassA(), "DEF");
test2:String = GenericsTest3<GenericsTest3ClassA, String>.method2(new GenericsTest3ClassA(), "DEF");

Clover.test("generics test", test == 123);
Clover.test("generics test2", test2.equals("DEF"));

