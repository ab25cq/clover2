
a := new ResultTypeTest();

Clover.test("result type test", a.get() == 123);

b:EqualableList<String> = equalable_list { 1, 2, 3 }.map { |n:Integer| n.toString(); }

Clover.test("result type test2", b.equals(equalable_list { "1", "2", "3" }));

c := equalable_list { 1, 2, 3 };

c.each { it.toString().println(); }
d:EqualableList<String> = equalable_list { 1, 2, 3 }.map { it.toString() }

Clover.test("result type test2", d.equals(equalable_list { "1", "2", "3" }));

a.method();

a.method2(new Integer(1), new Integer(2));
