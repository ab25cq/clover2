a:Anonymous = "AAA";

if(a.is("Integer")) {
    Clover.test("is test", a.className().equals("Integer"));
}
elif(a.is("String")) {
    Clover.test("is test", a.equals("AAA"));
}
else {
}

b:Long = a;

Clover.test("is test2", true);
