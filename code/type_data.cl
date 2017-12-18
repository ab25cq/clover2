a := new List<String>();

Clover.test("type test", a.className().equals("Array<String>"));

b:int[] = new int[123]();

Clover.test("type test2", b.classNmae().equals("int[]"));
