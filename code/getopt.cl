
optind:int = -1;

while(true) {
    result := getopt("abc:e");

    if(result.value1 == -1) {
        optind = result.value3;
        break;
    }

    when(result.value1.getValue().to_char) {
        case ('a') {
            println("option a");
        }
        case ('b') {
            println("option b");
        }
        case ('c') {
            println("option c \{result.value2}");
        }
    }
}

for(i:= optind; i<Clover.ARGC; i++) {
    println("other option \{Clover.ARGV[i]}");
}

