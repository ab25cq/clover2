a:int = 1;

a++;

System.assert(a == 2 && a++ == 2);
System.assert(a == 3);

b:IncrementOperandTest = new IncrementOperandTest();

System.assert(b.a == 111);
b.a++;

System.assert(b.a == 112 && b.a++ == 112);

System.assert(b.b == 222);
b.b--;

System.assert(b.b == 221 && b.b-- == 221);

c:int = 2;
c--;

System.assert(c == 1 && c++ == 1);

