a :byte[] = [ 0x00y, 0xe1y, 0xf5y, 0x05y ]

c:int = 0;
p:pointer = &c;
for(i:=0; i<4; i++) {
    (p+i)->byte = a[i];
}

c.toString().println();

