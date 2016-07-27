a:int[] = new int[10]();

a[1] = 100;
a[2] = 200;

System.assert(a[1] == 100 && a[0] == 0 && a[2] == 200);

b := 3;

a[b] = 300;

c:=3;

System.assert(a[c] == 300);

x:=100;

d:int[] = new int[x]();
