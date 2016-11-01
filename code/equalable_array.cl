
a := new EqualableClassA();

b := array { a, a, a };

print("toEqualableArray test...");
try {
    b.toEqualableArray();
}
catch(e:Exception) {
    if(e.message.equals("An elements doesn't implement IEqualable")) {
        println("OK");
    }
    else {
        println("FALSE");
        System.exit(2);
    }
}

