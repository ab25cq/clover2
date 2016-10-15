a:List<String> = new List<String>();

a.add("AAA");
a.add("BBB");
a.add("CCC");

a.each(lambda(item:String) { 
    System.println(item);
})

b:List<String> = list {"A", "B", "C"};

b.each(lambda(item:String){
    System.println(item);
})

c:List<Integer> = list {1,2,3 };

c.each(lambda(item:Integer) {
    System.println(item.toString());
})
