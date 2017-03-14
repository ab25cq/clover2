
1.times(lambda() {
    Clover.time(lambda() {
        p"src/".glob("*.c").grep(/main/);
    }).toString().println();
});
