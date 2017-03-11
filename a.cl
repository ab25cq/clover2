
3.times(lambda() {
    Clover.realtime(lambda() {
        p"src/parser.c".read().toString().split(/\n/);
    }).toString().print();
});
