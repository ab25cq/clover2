
a:regex = /^A/;

pcre_ovec: PcreOVec = new PcreOVec(3);

Clover.test("regex test", System.pcre_exec(a, "ABC", 3, pcre_ovec) >= 0);

for(i:=0; i<pcre_ovec.start.length; i++) 
{
    System.println("pcre_ovec.start[".append(i.toString).append("] -->").append(pcre_ovec.start[i].toString));
    System.println("pcre_ovec.end[".append(i.toString).append("] -->").append(pcre_ovec.end[i].toString));
}

pcre_ovec2: PcreOVec = new PcreOVec(3);

Clover.test("regex test2", System.pcre_exec(/bc$/, "abc", 3, pcre_ovec2) >= 0);

for(i=0; i<pcre_ovec2.start.length; i++) 
{
    System.println("pcre_ovec2.start[".append(i.toString).append("] -->").append(pcre_ovec2.start[i].toString));
    System.println("pcre_ovec2.end[".append(i.toString).append("] -->").append(pcre_ovec2.end[i].toString));
}



