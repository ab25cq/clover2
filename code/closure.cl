
a:String = "ABC";

block_ := closure(b:int, c:int) {
    Clover.test("Closure test1", a.equals("ABC") && b == 1 && c == 2);

    d:String = "DEF";

    block2 := closure(e:String) {
        f:String = "ABC";

        g:int = 123;

        Clover.test("Closure test2", a.equals("ABC") && b == 1 && c == 2 && d.equals("DEF") && e.equals("GHI") && f.equals("ABC") && g == 123);
    }

    block2("GHI");
}

block_(1,2);
