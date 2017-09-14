ls("src/main.c").toString().scan(/./).join("+").toCommand().less()
