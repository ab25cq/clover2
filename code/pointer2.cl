a:int = 123;

b:pointer = &a;

b->int = 234;

Clover.test("pointer test1", a == 234);

c:PointerClassA = new PointerClassA();

Clover.test("pointer test2", PointerClassA.classVar == 123 && c.var == 123);

d:pointer = &c.var;

d->int = 234;

e:pointer = &PointerClassA.classVar;

e->int = 234;

Clover.test("pointer test2", PointerClassA.classVar == 234 && c.var == 234);

f:PointerClassB = new PointerClassB(123);

Clover.test("pointer test3", f.var == 123);

PointerClassA.input_var(&f);

Clover.test("pointer test4", f.var == 234);

g:pointer = &f;

Clover.test("pointer test5", g->PointerClassB.var == 234 && (&f)->PointerClassB.var == 234);

(&f)->PointerClassB.var = 345;

Clover.test("pointer test6", f.var == 345);


