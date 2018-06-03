#    1/0;

a := TestA();

#a.method();

try {
    1/0;
} catch(e:Exception) {
    println("AAA");
}


println("BBB");
