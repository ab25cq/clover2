fields:EqualableList<String> = "#####aaaaaa".chomp().split(/:/);

print("null pointer exception check...");
try {
if(fields.items(2).to_int() == 100) {
    result := fields.items(0);
}
}
catch(e:Exception) {
    println("OK");
}
