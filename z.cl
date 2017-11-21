a:List<Object> = new List<Object>();

a.add(1);
a.add("ABC");

a.each {
    if(it.is("Integer")) {
    }
    elif(it.is("String")) {
    }
}
