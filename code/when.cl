a := 125;

print("when test...");
when(a) {
    1 {
        println("FALSE");
    }
    123,125 {
        println("TRUE");
    }
    else {
        println("FALSE");
    }
}

b := "ABC";

print("when test2...");
when(b) {
    "A" {
        println("FALSE");
    }
    "ABC" {
        println("TRUE");
    }
    else {
        println("FALSE");
    }
}

c := when(123) {
    123 {
        "ABC";
    }

    234 {
        "DEF";
    }

    else {
        "GHI";
    }
}

Clover.test("when test3", c.equals("ABC"));

d := when(234) {
    123 {
        "ABC";
    }

    234 {
        123;
    }

    else {
        "GHI";
    }
}

Clover.test("when test4", d.cast("int").equals(123));
