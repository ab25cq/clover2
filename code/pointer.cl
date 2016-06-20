
a:pointer = Clover.malloc(123);

a->int = 123;
System.assert(a->int == 123);

b:pointer = a + 4;

b->int = 245;

System.assert(b->int == 245);

b++;
b++;
b++
b++;

b->int = 345;

c:pointer = a + 8;
System.assert(c->int == 345);

Clover.free(a);

/*
(a.addres + 4)->int = 234;
System.assert(a.address->int == 123);
System.assert((a.address + 4)-> int == 234);
*/
