# スレッドクラス

English page is here [>> English page](thread-en)

スレッドは以下のように使います。

    a := 123;

    thread := Thread() {
        b := "ABC";

        Clover.test("thread test1", a == 123 && b.equals("ABC"));
    }

    println("main thread");

    thread.join();

Thread()のあとのブロックとprintln("main thread")は同時に動きます。threadは必ずjoinして合流しないとダメです。

mutexやcond_waitなどはThread.clclを読んでください。大体分かると思います。

