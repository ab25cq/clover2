a := new List<Object>();

a.add(1);
a.add("ABC");
a.add("DEF");

string_num := 0;
int_num := 0;

a.each {
    if(it.is("String")) {
        it.printf("[%s]\n");
        string_num++;
    }
    elif(it.is("Integer")) {
        it.printf("[%d]\n");
        int_num++;
    }
}

Clover.test("Object test", string_num == 2 && int_num == 1);
