
a:Tuple2<Integer, Bool> = new Tuple2<Integer, Bool>(1.toInteger, true.toBool);

Clover.test("tuple test", a.value1 == 1 && a.value2 == true);

b:Tuple3<Integer, Bool,Integer> = tuple {3, false, 4};

Clover.test("tuple test2", b.value1 == 3 && b.value2 == false && b.value3 == 4);

