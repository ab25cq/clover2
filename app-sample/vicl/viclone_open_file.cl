if(Clover.ARGC != 4) {
    println("Invalid argment");
    exit(2);
}

sockfd := socket(AF_UNIX, SOCK_STREAM, 0);

address := sockaddr_un();

address.sun_family = AF_UNIX;
address.sun_path = getenv("HOME").append("/.clover2/vicl/socket");

connect(sockfd, address);

buf := b"OPEN_FILE \{getenv("PWD").append("/").append(Clover.ARGV[2])} \{Clover.ARGV[3]}";

write(sockfd, buf, buf.length());

close(sockfd);