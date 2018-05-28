a := 123;

thread := Thread() {
    b := "ABC";

    Clover.test("thread test1", a == 123 && b.equals("ABC"));
}

thread.join();

a = 234;

thread2 := Thread() {
    b := "DEF";
    c := 345;

    Clover.test("thread test2", a == 234 && b.equals("DEF"));

    a = 345;

    thread3 := Thread() {
        Clover.test("thread test3", a == 345 && b.equals("DEF") && c == 345);
    }

    thread3.join();
}

thread2.join();


for(i:=0; i<100; i++) {
    thread3 := Thread() {
        a := 111;
        thread4 := Thread() {
            strs: String[] = String[100]();

            for(i:=0; i<100; i++) {
                strs[i] = "ABC";
            }

            for(i=0; i<100; i++) {
                slist{1,2,3}.map { it.toString() }.map { it.toCommand() }
            }
            pwd().write("abc");

            sum := 0;
            array {1,2,3}.each { sum += it }

            thread4a := Thread() {
                strs: String[] = String[100]();

                for(i:=0; i<100; i++) {
                    strs[i] = "ABC";
                }

                for(i=0; i<100; i++) {
                    slist{1,2,3}.map { it.toString() }.map { it.toCommand() }
                }

                sum := 0;
                array {1,2,3}.each { sum += it }

                thread4b := Thread() {
                    strs: String[] = String[100]();

                    for(i:=0; i<100; i++) {
                        strs[i] = "ABC";
                    }

                    for(i=0; i<100; i++) {
                        slist{1,2,3}.map { it.toString() }.map { it.toCommand() }
                    }

                    #ls("-al").toString().scan(/./)
                }

                strs = String[100]();

                for(i=0; i<100; i++) {
                    strs[i] = "ABC";
                }

                for(i=0; i<100; i++) {
                    slist{1,2,3}.map { it.toString() }.map { it.toCommand() }
                }

                #"ABC".scan(/./).map { it.multiply(5) }.join("+")

                #ls("-al").toString().scan(/./)

                thread4b.join();
            }

            sum = 0;
            array {1,2,3}.each { sum += it }

            strs = String[100]();

            for(i=0; i<100; i++) {
                strs[i] = "ABC";
            }

            for(i=0; i<100; i++) {
                slist{1,2,3}.map { it.toString() }.map { it.toCommand() }
            }

            thread4a.join();


            Clover.test("thread test4", true);
        }

        thread5 := Thread() {
            strs: String[] = String[100]();

            for(i:=0; i<100; i++) {
                strs[i] = "ABC";
            }

            for(i=0; i<100; i++) {
                slist{1,2,3}.map { it.toString() }.map { it.toCommand() }
            }

            #"ABC".scan(/./).map { it.multiply(5) }.join("+")

            Clover.test("thread test5", true);
        }

        for(i:=0; i<100; i++) {
            slist{1,2,3}.map { it.toString() }.map { it.toCommand() }
        }

        strs: String[] = String[100]();

        for(i=0; i<100; i++) {
            strs[i] = "ABC";
        }

        "ABC".scan(/./);

        thread4.join();
        thread5.join();
    }

    #"ABC".scan(/./).map { it.multiply(5) }.join("+")

    strs: String[] = String[100]();

    for(i:=0; i<100; i++) {
        strs[i] = "ABC";
    }

    thread3.join();
}

