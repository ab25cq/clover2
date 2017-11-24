/*
Clover.test("string2 test1", "ABC".sub(/A/, "B").equals("BBC"));
Clover.test("string2 test2", "AAA".sub(/A/g, "B").equals("BBB"));
Clover.test("string2 test3", "AAA".sub(/^A/g, "B").equals("BAA"));

Clover.test("string2 test4", "ABC".subString(-2, -1).equals("BC"));
group_strings:EqualableList<String> = new EqualableList<String>();
str:String = "ABCD".sub(/(.)(.)$/, "XX", group_strings);

Clover.test("string2 test5", str.equals("ABXX") && group_strings.length() == 2 && group_strings.items(0).equals("C") && group_strings.items(1).equals("D"));

*/
str2:String = "ABCD".sub(/(.)(.)$/
            , lambda(match_string:String, group_strings:EqualableList<String>):String { 
                return System.sprintf("%s%s", array { group_strings.items(0), group_strings.items(0) }); 
            });
/*
Clover.test("string2 test6", str2.equals("ABCC"));

Clover.test("string2 tset7", "ABC".match(/^A/) && "ABC".match(/C$/) && "ABC".match(/B/));

group_strings3:EqualableList<String> = new EqualableList<String>();
Clover.test("string2 test8", "ABC".match(/^A(.)C/, group_strings3) && group_strings3.length() == 1 && group_strings3.items(0).equals("B"));

Clover.test("string2 test9", "ABC".scan(/./).equals(equalable_list {"A", "B", "C"}));
Clover.test("string2 test10", "ABCDEFGHI".scan(/^./).equals(equalable_list {"A"}));
Clover.test("string2 test11", "ABCDEFGHI".scan(/.$/).equals(equalable_list {"I"}));
Clover.test("string2 test12", "ABCDEFGHI".scan(/D.F/).equals(equalable_list {"DEF"}));

strings:EqualableList<String> = "ABC".scan(/./
            , lambda(match_string:String, group_strings:EqualableList<String>):String {
                return match_string.append("1");
            }
);

Clover.test("string2 test13", strings.equals(equalable_list { "A1", "B1", "C1" }));

Clover.test("string2 test14", "ABCABCABC".scan(/B/).length() == 3);

Clover.test("string2 test15", "ABC\nABC\nABC\n".split(/\n/).equals(equalable_list { "ABC", "ABC", "ABC" }));

Clover.test("string2 test16", "ABC\r\nABC\r\nABC\r\n".split(/\r\n/).equals(equalable_list { "ABC", "ABC", "ABC" }));

Clover.test("string2 test17", "ABC".reverse().equals("CBA"));
Clover.test("string2 test18", "ABC".lowerCase().equals("abc"));
Clover.test("string2 test19", "Abc".lowerCase().equals("abc"));
Clover.test("string2 test20", "Abc".upperCase().equals("ABC"));
Clover.test("string2 test21", "abc".upperCase().equals("ABC"));

Clover.test("string2 test22", "123".to_int() == 123);
Clover.test("string2 test23", "123.123".to_float() == 123.123f);
Clover.test("string2 test24", "123.123".to_double() == 123.123);
Clover.test("string2 test25", "ABC".multiply(3).equals("ABCABCABC"));

Clover.test("string2 test26", "ABC".compare("DEF") < 0);
Clover.test("string2 test27", "ABC".compare("ABC") == 0);
Clover.test("string2 test28", "DEF".compare("ABC") > 0);
Clover.test("string2 test29", "abc".compareWithIgnoreCase("ABC") == 0);
Clover.test("string2 test30", "0xFF".hex() == 255);
Clover.test("string2 test31", "010".oct() == 8);

#Clover.test("string2 test32", "あいう".scan(/./).equals(equalable_list {"あ", "い", "う"}));


Clover.test("string2 test33", "abcabc".indexOf(/c/) == 2);
Clover.test("string2 test34", "abcabc".indexOf(/c/, 2) == 5);
Clover.test("String2 test35", "abc".insert(1,"A").equals("aAbc"));
Clover.test("String2 test36", "abc".subString(-1,-1).equals("c"));
Clover.test("String2 test37", "ABC".subString(-2, -1).equals("BC"));
*/
