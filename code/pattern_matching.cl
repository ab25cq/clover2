
a:Anonymous = "ABC";

c:String = when(a) {
    is String {
        a;
    }
    else {
        "else";
    }
}

Clover.test("Pattern matching test", c.equals("ABC"));

b:Anonymous = new PatternMatchingTest(111, "ABC");

d:String = when(b) {
    !is String {
        "111";
    }
    else {
        "else"
    }
}

Clover.test("Pattern maching test2", d.equals("111"));
