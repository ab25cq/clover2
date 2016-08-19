
a:int = 333;

System.print("Try test1...");
try {
    TryTest.method1();
}
catch(e:Exception) {
    System.println("OK");
    System.println("e.message --> ".append(e.message));
}

System.println("Try test2... OK");

