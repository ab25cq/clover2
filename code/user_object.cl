System.assert(UserObjectTest.method() == null);
System.assert(UserObjectTest.method3(3, 7) == 10);

a := new UserObjectTest2();
System.assert(a.a == 1);
System.assert(a.b == 2);

System.assert(UserObjectTest2.c == 111);
System.assert(UserObjectTest2.d == 222);

