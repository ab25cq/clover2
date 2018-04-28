# Thread Class

Threads are used as follows.
```
    a := 123;

    thread := Thread() {
        b := "ABC";

        Clover.test("thread test1", a == 123 && b.equals("ABC"));
    }

    println("main thread");

    thread.join();
```

The blocks after Thread () and println ("main thread") work at the same time. You must join threads and join together. For mutex, cond_wait, etc., please read Thread.clcl. I think that you can roughly understand.
