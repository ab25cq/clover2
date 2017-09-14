1.times(lambda() {
    Clover.realtime(lambda() {
        p"src/".glob("*.c").grep(/main/);
        #p"src/parser.c".read().toString().split('\n')
    }).toString().println();
});


# wonderwand.net 1.5sec - 2.0sec
# LOOX u/c30 10sec
