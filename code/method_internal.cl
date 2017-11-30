a := new MethodInternal();

Clover.test("method internal", a.method() == 123);

Clover.test("field internal", a.method3() == 234);
Clover.test("field internal2", a.method4() == 345);
Clover.test("field internal3", a.method5() == 234);
Clover.test("field internal4", a.method6() == 468);
