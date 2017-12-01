a := 123;

print("when test...");
when(a) {
    0 {
        println("FALSE");
        System.exit(2);
    }

    123 {
        println("OK");
    }

    else {
        println("FALSE");
        System.exit(2);
    }
}
