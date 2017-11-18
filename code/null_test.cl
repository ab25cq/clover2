fields:EqualableList<String> = "#####aaaaaa".chomp().split(/:/);

if(fields.items(2).to_int() == 100) {
    result := fields.items(0);
}
