
Clover.test("Array test", { 1,2,3 }.equals({1,2,3}.toArray));

Clover.test("Array test2", {1,2,3}.equals({1.toInteger,2.toInteger,3.toInteger}));

Clover.test("Array test3", {1,2,3}.equals(array { 1,2,3 }));

