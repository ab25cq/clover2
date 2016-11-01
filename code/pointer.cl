
a:pointer = System.malloc(123);

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

System.free(a);
