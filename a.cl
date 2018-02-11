Clover.realtime() {
    p"../clover2/src/".glob("*.c").grep(/main/);
}.toString().println();


# clover-lang.org 2.0sec

# wonderwand.net 1.5sec - 2.0sec
# LOOX u/c30 10sec

# wonderwand.net no jit with optimize 3sec

# woderwand.net with jit with optimize 1.1-2.0sec
