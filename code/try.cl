
a:int = 333;

System.print("Try test1...");
try {
    TryTest.method1();
}
catch(e:Exception) {
    System.println("OK");
    b:=234;
    Clover.test("Try test1-1", b == 234);
    Clover.test("Try test1-2", e.message.equals("ERROR"));
}

System.println("Try test2... OK");

try {
    a:=123;
    Clover.test("Try test3", a == 123);

    System.print("Try test4...");
    TryTest.method1();
}
catch(e:Exception) {
    System.println("OK");
    b:= 123;
    Clover.test("Try test5", b == 123);

    try {
        d:=456;
        System.print("Try test6...");
        TryTest.method1();
    }
    catch(e:Exception) {
        System.println("OK");
        g:= "AAA";
        Clover.test("Try test7", e.message.equals("ERROR") && g.equals("AAA"));
    }

    Clover.test("Try test8", e.message.equals("ERROR"));
}
