
object: SelfTest = new SelfTest(111,222);

Clover.test("Self test1", object.getSelf().value1 == 111);
