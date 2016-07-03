a:int = 1;

a++;

System.assert(a == 2 && a++ == 2);
System.assert(a == 3);

b:IncrementOperandTest = new IncrementOperandTest();

System.assert(b.a == 111);
b.a++;

System.assert(b.a == 112 && b.a++ == 112);
System.assert(b.a == 113);

System.assert(b.b == 222);
b.b--;

System.assert(b.b == 221 && b.b-- == 221);
System.assert(b.b == 220);

System.assert(b.c == 555);

b.c++;

System.assert(b.c == 556);

b.c--;

System.assert(b.c == 555);

c:int = 2;
c--;

System.assert(c == 1 && c++ == 1);
System.assert(c == 2);

d:long = 4;

d++;

System.assert(d == 5 && d++ == 5);

d--;

System.assert(d == 5);

e:short = 123;

System.assert(e == 123 && e++ == 123);

System.assert(e == 124);

e--;

System.assert(e == 123);

f := 123;

++f;

System.assert(f == 124 && ++f == 125);

--f;

System.assert(f == 124 && --f == 123);



/*
c:int = 3;

c+=4;

System.assert(c == 7);

c+=4;

System.assert(c == 11);

c-=4;

System.assert(c == 7);
*/

