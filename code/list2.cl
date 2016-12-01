
Clover.test("List2 test1", list {1,2,3}.indexOf(2) == 1);
Clover.test("List2 test2", list {1,2,3}.sample().include(list {1,2,3}));
Clover.test("List2 test3", list {1,2,3}.equals(list { 1,2,3 }));
Clover.test("List2 test4", list {1,2,3}.clear().equals(new List<Integer>()));
Clover.test("List2 test5", list {1,2,3}.map(lambda(n:Integer):Anonymous { return n.toString(); }).equals(list { "1", "2", "3"}));
Clover.test("List2 test6", list {1,2,3}.map(lambda(n:Integer):Anonymous { return n * 2; }).equals(list { 2,4,6 }));
Clover.test("List2 test7", list {1,2,3}.append(list {4,5,6}).equals(list {1,2,3,4,5,6}));
Clover.test("List2 test8", list {1,2}.multiply(3).equals(list {1,2,1,2,1,2}));
Clover.test("List2 test9", list {1,2,3,4,5,1,2,3,4,5}.count(1) == 2);
Clover.test("List2 test10", list {1,2,3,4,5}.deleteAt(1).equals(list {1,3,4,5}));
Clover.test("List2 test11", list {1,2,3,1,2,3}.select(lambda(n:Integer):bool { return n != 1 }).equals(list {2,3,2,3}));
Clover.test("List2 test12", list {1,2,3,1,2,3}.deleteWithRange(2,4).equals(list {1,2,2,3}));
Clover.test("List2 test13", list {1,2,3,4,5,6}.fill(2,4, 100).equals(list {1,2,100,100,5,6}));
Clover.test("List2 test14", list {1,2,3,4,5,6}.fill(2,4, 100).equals(list {1,2,100,100,5,6}));
Clover.test("List2 test15", list {1,2,3,4,5,6}.subList(2,4).equals(list { 3,4 }));
Clover.test("List2 test16", list {1,2,3,4,5,6}.subList(-2,-1).equals(list { 5,6 }));
Clover.test("List2 test17", list {1,2,3,4,5,6}.subList(-1,-1).equals(list { 6 }));
Clover.test("List2 test18", list {1,2,3,4,5,6}.subList(2,-1).equals(list { 3,4,5,6 }));
Clover.test("List2 test19", list {1,2,3,4,5,6}.subList(2,-2).equals(list { 3,4,5 }));
Clover.test("List2 test20", list {1,2,3,4,5,6}.fill(100).equals(list {100,100,100,100,100,100}));
Clover.test("List2 test21", list {1,2,3,4,5,6}.indexOf(3) == 2);
Clover.test("List2 test22", list {"AAA", "BBB", "CCC"}.join("+").equals("AAA+BBB+CCC"));
Clover.test("List2 test23", list {111, 222, 333}.join("+").equals("111+222+333"));

a:List<Integer> = list { 1,2,3 };
Clover.test("List2 test24", a.pop() == 3 && a.pop() == 2 && a.pop() == 1 && a.pop().identifyWith(null));

b:= list { 1,2,3 };

Clover.test("List2 test25", b.shift() == 1 && b.shift() == 2 && b.shift() == 3 && b.shift().identifyWith(null));

println("List test26");
c := list { 1,2,3 };

c.shuffle().toString().printf("%s\n");
c.shuffle().toString().printf("%s\n");
c.shuffle().toString().printf("%s\n");
c.shuffle().toString().printf("%s\n");
c.shuffle().toString().printf("%s\n");
