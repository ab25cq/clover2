
Clover.test("string2 test1", "ABC".sub(/A/, "B", null).equals("BBC"));
Clover.test("string2 test2", "AAA".sub(/A/g, "B", null).equals("BBB"));
Clover.test("string2 test3", "AAA".sub(/^A/g, "B", null).equals("BAA"));
Clover.test("string2 test4", "ABC".subString(-2, -1).equals("BC"));

group_strings:List<String> = new List<String>();
str:String = "ABCD".sub(/(.)(.)$/, "XX", group_strings);

Clover.test("string2 test5", str.equals("ABXX") && group_strings.length() == 2 && group_strings.items(0).equals("C") && group_strings.items(1).equals("D"));

group_strings2:List<String> = new List<String>();
str2:String = "ABCD".sub(/(.)(.)$/
            , lambda(match_string:String, group_strings:List<String>):String { 
                return System.sprintf("%s%s", array { group_strings.items(0), group_strings.items(0) }); 
            }
            , group_strings2);

Clover.test("string2 test6", str2.equals("ABCC") && group_strings2.length() == 2 && group_strings2.items(0).equals("C") && group_strings2.items(1).equals("D"));

