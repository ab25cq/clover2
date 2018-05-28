while(true) {
    result := "";
    result_before := "";
    fp:pointer@FILE = popen("./clover2 code/thread.cl", "r");

    while(!feof(fp)) {
        buf := Buffer(System.BUFSIZ);
        fgets(buf, System.BUFSIZ, fp);
        result_before = result;
        result = buf.toString();
    }

    rcode := pclose(fp);

    if(rcode != 0) {
        result_before.append(result).write("aaa");
        break;
    }
}
