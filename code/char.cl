
x:char = 'A';

System.assert(x == 'A');

x++;

System.assert(x == 'B');

System.assert(x != 'A');

System.assert(x >= 'A');

System.assert(x > 'A');

System.assert(x < 'C');

System.assert(x >= 'B');

y:char = 'あ';

System.assert(y == 'あ');


Clover.test("char test1", 'a'.to_upper == 'A');
Clover.test("char test2", 'A'.to_upper == 'A');
Clover.test("char test3", 'A'.to_lower == 'a');
Clover.test("char test4", 'a'.to_lower == 'a');
