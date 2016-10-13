
a:regex = /^A/;

Clover.test("regex test", System.pcre_exec(a, "ABC") >= 0);
Clover.test("regex test2", System.pcre_exec(/^a/, "abc") >= 0);

