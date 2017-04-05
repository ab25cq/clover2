
1.times(lambda() {
    Clover.realtime(lambda() {
        p"src/".glob("*.c").grep(/main/);
        #p"src/parser.c".read().toString().split('\n')
    }).toString().println();
});
