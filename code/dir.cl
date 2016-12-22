dir:Directory = new Directory("test_dir");

entries:SortableList<String> = new SortableList<String>();

while(true) {
    entry:String = dir.readdir();

    if(entry.identifyWith(null)) {
        break;
    }

    entries.add(entry);
}

dir.closedir();

Clover.test("Directory test1", entries.sort().equals(sortable_list {"a", "b", "c", ".", ".."}.sort()));

