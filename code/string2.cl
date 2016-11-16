
Clover.test("string2 test1", "ABC".sub(/A/, "B", null).equals("BBC"));
Clover.test("string2 test2", "AAA".sub(/A/g, "B", null).equals("BBB"));
Clover.test("string2 test3", "AAA".sub(/^A/g, "B", null).equals("BAA"));
Clover.test("string2 test4", "ABC".subString(-2, -1).equals("BC"));

array:string[128] = new String[128]();
group_strings:Array<String> = new Array<String>();
"ABCD".sub(/(.)(.)$/, group_strings);

Clover.test("string2 test5", group_strings.length() == 2 && group_strings[0].equals("C") && group_strings[1].equals("D"));

