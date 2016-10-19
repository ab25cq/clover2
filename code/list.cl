a:List<String> = new List<String>();

a.add("AAA");
a.add("BBB");
a.add("CCC");

count :int = 0;
a.each(closure(item:String) { 
    count ++;
})

Clover.test("list test", a.items(1).equals("BBB") && count == 3);

b:List<String> = list {"A", "B", "C"};

count = 0;
b.each(closure(item:String){
    count ++;
})

Clover.test("list test2", b.items(1).equals("B") && count == 3);

c:List<Integer> = list {1,2,3 };

count = 0;
c.each(closure(item:Integer) {
    count ++;
})

Clover.test("list test3", c.items(1) == 2 && count == 3);

d:List<Integer> = list { 1,2,3 };

d.delete(3);

Clover.test("list test4", d.equals(list { 1,2 }));
Clover.test("list test5", list { 1 }.delete(1).length() == 0);
Clover.test("list test6", list { 1,2 }.delete(1).equals(list {2}));
Clover.test("list test7", list { 1,2 }.delete(2).equals(list {1}));
Clover.test("list test8", list { 1,2,3 }.delete(1).equals(list {2,3}));
Clover.test("list test8", list { 1,2,3 }.delete(2).equals(list {1,3}));
Clover.test("list test8", list { 1,2,3 }.delete(3).equals(list {1,2}));

