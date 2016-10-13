
a:regex = /^A/;

Clover.test("regex test", System.pcre_exec(a, "ABC") >= 0);

