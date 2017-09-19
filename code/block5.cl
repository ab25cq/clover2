a:= 1;
b:= 2;

/*
equalable_list { 1, 2, 3 }.map() {|n:Integer|:Anonymous
    return n.toString();
}
*/
equalable_list { 1, 2, 3 }.map(closure(n:Integer):Anonymous { return n.toString(); });

Clover.test("lambda param test", a == 1 && b == 2);
