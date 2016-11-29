
Clover.test("List2 test1", list {1,2,3}.indexOf(2) == 1);
Clover.test("List2 test2", list {1,2,3}.choice().include(list {1,2,3}));
Clover.test("List2 test3", list {1,2,3}.equals(list { 1,2,3 }));
Clover.test("List2 test4", list {1,2,3}.clear().equals(new List<Integer>()));
Clover.test("List2 test5", list {1,2,3}.map(lambda(n:Integer):Anonymous { return n.toString(); }).equals(list { "1", "2", "3"}));
