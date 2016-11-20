Clover.test("string2 test1", "ABC".sub(/A/, "B").equals("BBC"));
Clover.test("string2 test2", "AAA".sub(/A/g, "B").equals("BBB"));
Clover.test("string2 test3", "AAA".sub(/^A/g, "B").equals("BAA"));
Clover.test("string2 test4", "ABC".subString(-2, -1).equals("BC"));

group_strings:List<String> = new List<String>();
str:String = "ABCD".sub(/(.)(.)$/, "XX", group_strings);

Clover.test("string2 test5", str.equals("ABXX") && group_strings.length() == 2 && group_strings.items(0).equals("C") && group_strings.items(1).equals("D"));

str2:String = "ABCD".sub(/(.)(.)$/
            , lambda(match_string:String, group_strings:List<String>):String { 
                return System.sprintf("%s%s", array { group_strings.items(0), group_strings.items(0) }); 
            });

Clover.test("string2 test6", str2.equals("ABCC"));

Clover.test("string2 tset7", "ABC".match(/^A/) && "ABC".match(/C$/) && "ABC".match(/B/));

group_strings3:List<String> = new List<String>();
Clover.test("string2 test8", "ABC".match(/^A(.)C/, group_strings3) && group_strings3.length() == 1 && group_strings3.items(0).equals("B"));

Clover.test("string2 test9", "ABC".scan(/./).equals(list {"A", "B", "C"}));
Clover.test("string2 test10", "ABCDEFGHI".scan(/^./).equals(list {"A"}));
Clover.test("string2 test11", "ABCDEFGHI".scan(/.$/).equals(list {"I"}));
Clover.test("string2 test12", "ABCDEFGHI".scan(/D.F/).equals(list {"DEF"}));

strings:List<String> = "ABC".scan(/./
            , lambda(match_string:String, group_strings:List<String>):String {
                return match_string.append("1");
            }
);

Clover.test("string2 test13", strings.equals(list { "A1", "B1", "C1" }));

Clover.test("string2 test14", "ABCABCABC".scan(/B/).length() == 3);

Clover.test("string2 test15", "ABC\nABC\nABC\n".split(/\n/).equals(list { "ABC", "ABC", "ABC" }));

Clover.test("string2 test16", "ABC\r\nABC\r\nABC\r\n".split(/\r\n/).equals(list { "ABC", "ABC", "ABC" }));

Clover.test("string2 test17", "ABC".reverse().equals("CBA"));


