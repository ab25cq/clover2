
a := new PatternMatchingTest(111, "ABC");

b:String = match(a) {
    case PatternMatchingTest(value1, value2) {
        value2;
    }
    else {
        "else";
    }
}
