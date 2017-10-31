list { 1, 2, 3 }
    .map(lambda(n:Integer):Anonymous { return n * 2; })
    .each(lambda(m:Anonymous) { m.toString().println();})

list { 1, 2, 3 }.toString().println();

a:List<String> = list { 1, 2, 3 }.map() { |n:Integer| return n.toString() };

Clover.test("map test", a.items(0).equals("1") && a.items(1).equals("2") && a.items(2).equals("3"));

