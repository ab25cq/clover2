timeout := timeval();

while(true) {
    inputs := fd_set();
    FD_ZERO(inputs);
    FD_SET(0, inputs);

    testfds := inputs.clone();

    timeout.tv_sec = 2;
    timeout.tv_usec = 500000;

    result := select(FD_SETSIZE, testfds, null, null, timeout);

    if(result == 0) {
        println("timeout");
        break;
    }
    if(FD_ISSET(0, testfds)) {
        nread:int = 0;

        ioctl(0, FIONREAD, &nread);

        if(nread == 0) {
            println("keyboard done");
            exit(0);
        }

        buf := Buffer(128);
        read(0, buf, nread);
        printf("read %d from keyboard: %s\n", array { nread, buf.toString() });
        break;
    }
}
