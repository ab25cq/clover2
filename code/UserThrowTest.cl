a := UserThrowTest();
try {
    a.method2();
}
catch(e:Exception) {
    println("OK");
}
