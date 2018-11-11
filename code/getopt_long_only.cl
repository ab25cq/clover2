
optind := -1;

while(true) {
    longopts:getopt_long_option[] = new getopt_long_option[4];

    longopts[0] = new getopt_long_option("add", System.no_argument, null, 'a');
    longopts[1] = new getopt_long_option("break", System.no_argument, null, 'b');
    longopts[2] = new getopt_long_option("clear", System.required_argument, null, 'c');
    longopts[3] = new getopt_long_option("delete", System.optional_argument, null, 'd');

    result := getopt_long_only("abc:d::", longopts);

    if(result.value1 == -1) {
        optind = result.value3;
        break;
    }

    when(result.value1.getValue().to_char) {
        case ('a') {
            println("option a --add");
        }
        case ('b') {
            println("option b --break");
        }
        case ('c') {
            println("option c --clear \{result.value2}");
        }
        case ('d') {
            println("option d --delete \{result.value2}");
        }
    }
}

for(i := optind; i<Clover.ARGC; i++) {
    println("other option \{Clover.ARGV[i]}");
}
