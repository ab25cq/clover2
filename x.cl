
a:List<String> = list { 1, 2, 3 }.map() { |n:Integer| return n.toString() };

Clover.test("map test", a.items(0).equals("1") && a.items(1).equals("2") && a.items(2).equals("3"));

