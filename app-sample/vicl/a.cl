a := { 1, 2, 3 }

it := a.iterator(2);
while(it != null) {
    println(it.item.toString());
    it = it.next;
}
