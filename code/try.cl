print("try test...");
try {
    1/0;
}
catch(e:Exception) {
    println("OK");
}

print("try test2...");

try {
    1/0;
}

println("OK");
