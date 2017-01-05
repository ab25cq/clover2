a:EqualableList<String> = new EqualableList<String>();

a.add("AAA");
a.add("BBB");
a.add("CCC");

count :int = 0;
a.each(closure(item:String) { 
    count ++;
})

Clover.test("list test", a.items(1).equals("BBB") && count == 3);

b:EqualableList<String> = equalable_list {"A", "B", "C"};

count = 0;
b.each(closure(item:String){
    count ++;
})

Clover.test("list test2", b.items(1).equals("B") && count == 3);

c:EqualableList<Integer> = equalable_list {1,2,3 };

count = 0;
c.each(closure(item:Integer) {
    count ++;
})

Clover.test("list test3", c.items(1) == 2 && count == 3);

d:EqualableList<Integer> = equalable_list { 1,2,3 };

d.delete(3);

Clover.test("list test4", d.equals(equalable_list { 1,2 }));
Clover.test("list test5", equalable_list { 1 }.delete(1).length() == 0);
Clover.test("list test6", equalable_list { 1,2 }.delete(1).equals(equalable_list {2}));
Clover.test("list test7", equalable_list { 1,2 }.delete(2).equals(equalable_list {1}));
Clover.test("list test8", equalable_list { 1,2,3 }.delete(1).equals(equalable_list {2,3}));
Clover.test("list test9", equalable_list { 1,2,3 }.delete(2).equals(equalable_list {1,3}));
Clover.test("list test10", equalable_list { 1,2,3 }.delete(3).equals(equalable_list {1,2}));
Clover.test("list test11", equalable_list { 1,2,3 }.insert(1, 7).equals(equalable_list { 1,7,2,3}));
Clover.test("list test12", equalable_list { 1,2,3 }.insert(0, 7).equals(equalable_list { 7,1,2,3}));
Clover.test("list test13", equalable_list { 1,2,3 }.insert(3, 7).equals(equalable_list { 1,2,3,7}));
Clover.test("list test14", equalable_list { 1,2,3 }.insert(-1, 7).equals(equalable_list { 1,2,3,7}));
Clover.test("list test15", equalable_list { 1,2,3 }.insert(-2, 7).equals(equalable_list { 1,2,7,3}));
Clover.test("list test16", equalable_list { 1,2,3 }.insert(-10, 7).equals(equalable_list { 7,1,2,3}));
Clover.test("list test17", equalable_list { 1,2,3 }.replace(-1, 10).equals(equalable_list { 1,2,10 }));
Clover.test("list test18", equalable_list { 1,2,3 }.replace(-2, 10).equals(equalable_list { 1,10,3 }));
Clover.test("list test19", equalable_list { 1,2,3 }.replace(10, 10).equals(equalable_list { 1,2,10 }));
Clover.test("list test20", equalable_list { 1,2,3 }.replace(-10, 10).equals(equalable_list { 10,2,3 }));

