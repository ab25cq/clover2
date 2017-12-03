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
