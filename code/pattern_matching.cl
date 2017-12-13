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

e:Anonymous = new PatternMatchingTest(111, "ABC");

f:String = when(e) {
    case new PatternMatchingTest(111, "ABC"): {
        "ABC";
    }
    else {
        "DEF";
    }
}

Clover.test("Pattern matching test3", f.equals("ABC"));

g:Anonymous = new PatternMatchingTest(222, "DEF");

f = when(g) {
    case new PatternMatchingTest(111, "DEF"): {
        "ABC"
    }
    case new PatternMatchingTest(222, wildcard): {
        "DEF";
    }
    else {
        "GHI";
    }
}

Clover.test("Pattern matching test4", f.equals("DEF"));

i:Anonymous = new PatternMatchingTest2(123, "ABC");

j:String = when(i) {
    case new PatternMatchingTest2(wildcard, wildcard): {
        "ABC";
    }
    else {
        "DEF";
    }
}

Clover.test("Pattern matching test5", j.equals("ABC"));
