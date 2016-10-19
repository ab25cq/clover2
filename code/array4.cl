b:int[] = new int[3]();

for(i:=0; i<3; i++) {
    b[i] = i;
}

b[2] = 4;

Clover.test("array test4-1", b[0] == 0 && b[1] == 1 && b[2] == 4);


a:ArrayTest4 = new ArrayTest4();

a.value[2] = 4;

Clover.test("array test4-2", a.value[0] == 0 && a.value[1] == 1 && a.value[2] == 4);


