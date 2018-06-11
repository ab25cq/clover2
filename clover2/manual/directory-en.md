# Directory class

Class of the directory. Like the File class, there are two ways of opening and closing and accessing the list of file names at once. Basically, I think that it only uses the method of obtaining the list of file names at a time.
```
    > dir: Directory = new Directory("src/");
    > dir.readdir();
    byte.c
    > dir.closedir();
```

readdir () continues to return a list of file names until it returns null. Normally you will loop until while returning null in the while statement. Next, I will show you how to get the list at once.

```
    > Directory.entries ("src/");
    list {src/byte.c, src/exception.c, src/script_ctime.c, ..., src/code.c}
```

You can get a list of filenames of type `SortableList <String>` in entries. The first argument is the target directory.

```
    > Directory.glob("src/", "*.c");
    list {src/byte.c, ..., src/code.c}
```

glob gets a list of filenames matching globs. The first argument is the target directory. The second argument is glob.

```
    > Directory.glob("*.clc");
    list {./File.clc,./Container.clc,./Fundamental.clc,./Command.clc,./String.clc,./MyOwnLibrary.clc,./x.clc}
```

Using glob as one argument gives a list of file names matching the glob in the current directory.
