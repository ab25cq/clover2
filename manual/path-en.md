# Path class

The Path class represents a file path. A representation of the value of an object is a string enclosed in double quotes after p, such as p "src/" and p.
Let's quickly introduce the method.
```
    > p"src/main.c".realpath ()
    /home/ab25cq/repo/clover2/src/main.c
```
realpath () returns the absolute path. One point to note is that the file must exist. If you need an absolute path of a nonexistent file, there is a method of temporarily creating a file with touch etc., then erasing it after reading the realpath method.
```
    > p"src/main.c".dirname ()
    src
```
dirname () returns the path of the directory portion of the path.
```
    > p"src/main.c".basename ()
    main.c
```
basename () returns the path of the file name part of the path.
```
    > p"src/main.c".extname ()
    c
```
extname () returns the extension. There is no extension in UNIX filename, it is part of simple file name, but by convention like a file extension is followed by a character string representing the type of file. extname () returns it.
```
    > p"src/main.c".read()
    Inside main.c ...
```
read () reads all the files, stores them in the Buffer object, and returns it. Although File.read is ok but it is useful, I am making it for the time being.
```
    > p"x.txt".write(B"ABC")
    3
    > cat("x.txt")
    ABC
```
A write writes a Buffer object to the file. The file permissions are written with 0644. Like File.write, since the System.O_TRUNC flag is attached, the file is overwritten. Caution is required.
```
    > p"x.txt".chmod (0777)
    > ls("-al", "x.txt")
    -rwxrwxrwx 1 ab25cq ab25cq 3 March 2 11: 34 x.txt
```
chmod changes the file permissions. Since it is 0777, it is -rwxrwxrwx. There is lchmod in chmod 's group. In this case, if the target is a symbolic link, change the permissions of the symbolic link itself.
```
    > p"x.txt".chown(1000, 1000)
```
chown changes the owner of the file. The first argument is the user ID and the second is the group ID. The user ID is written in / etc / passwd and the group ID is written in / etc / group. You will not use it without root authority. If you want to get the user ID from the user name, you can read / etc / passwd and use scan. Or it might be useful to create such a method in the Path class itself. I will leave it to everyone around here. lchown changes the owner of the file of the symbolic link itself.
```
    > p"x.txt".unlink()
    > ls("x.txt")
    I can not access ls: x.txt: No such file or directory
```
unlink will delete the file. External program rm may be more secure.
```
    > p"src/main.c".access(System.F_OK);
    0
```
Make sure the file exists. 0 is returned if it exists. As arguments, one of System.F_OK, System.R_OK, System.W_OK, System.X_OK is used. Each checks whether the file is present, readable, writable, or executable.
```
    > p"src/main.c".utime(System.time(), System.time())
```
utime changes the file access time and modification time. The first argument is the access time and the second argument is the modification time. It will not be used normally.
```
    > p "src/main.c".fnmatch("*.c");
    true

    > p "src/main.c".fnmatch("*.c", 0);
    true
```
fnmatch performs file name determination by glob. Globbing is also different from regular expression in pattern matching of file names. If you are using a shell I think that you know. It was called wild card in MS-DOS. The glob has the followings.
```
    ? Match any single character
    * Matches any string
    [AB] Matches A and B.
    Same as [A-Fa-f0-9] [ABDEFGabcdef0123456789]
    [!A] Match one character except A
```
```
p"src/main.c".fnmatch("*.c")
```
     returns true because it matches \*.c. I think that the second argument of fnmatch does not use much, but it is a flag like the following.

    System.FNM_NOESCAPE If this flag is set, backslash (\) is handled as normal character instead of escape character.
    System.FNM_PATHNAME When this flag is set, slash (/) in string is matched only to the slash itself in pattern and metacharacters of asterisks (*) and question marks (?), Bracket expressions including slashes ( Do not match []).
    System.FNM_PERIOD If this flag is set, the leading period of string matches only the period itself in pattern. The leading period is a period in the first character position of string. However, if the FNM_PATHNAME flag is set at the same time, the period immediately following the slash is also regarded as the leading period.
    System.FNM_FILE_NAME This is a synonym for GNU for FNM_PATHNAME.
System.FNM_LEADING_DIR This flag is an extension in GNU. If this is set, if the pattern matches the first part of string (with a slash), it is assumed to be a match. This flag is mainly used internally by glibc, and it is implemented only for that purpose.
    System.FNM_CASEFOLD This flag is an extension in GNU. When this is set, case matches are not case sensitive.

I do not understand well either. I have copied from man. It may be rarely necessary. I think that it is better to use regular expressions for fine file name processing ,,,,,.
```
    > p"x.txt".link("z.txt");
    > ls("-al", "z.txt");
    -rw-r - r - 2 ab25cq ab25cq 4 March 12:06 z.txt
```
link makes a hard link. A hard link from x.txt to z.txt was created. A hard link is a function that allows you to create two or more different names in the same file. In this case, x.txt and z.txt are the same file.
```
    > p"x.txt".symlink("y.txt");
    > ls("-al", "y.txt");
    lrwxrwxrwx 1 ab25cq ab25cq 5 March 2 12: 09 y.txt -> x.txt
```
symlink creates a symbolic link. It is a short cut in Windows. In this case, x.txt and y.txt are not the same thing but when accessing y.txt the link will be traced and treated as x.txt.
```
    > p"y.txt".readlink ()
    x.txt
```
readlink reads and returns the name of the file pointed to by the symbolic link.
```
    > p"y.txt".rename ("y2.txt")
    > ls("-al", "y2.txt")
    lrwxrwxrwx 1 ab25cq ab25cq 5 March 2 12: 13 y2.txt -> x.txt
```
reanme changes the file name.
```
    > p"x.txt".truncate(1ul)
    > cat("x.txt")
    A
```
truncate shortens the file by the number of arguments. In this case it is 1 ul so it is shortened to 1 character. Argument is ulong type. (Since the file size is up to 64 bits)
```
    > p"src/".chdir ();
```
chdir () changes the current directory. It's cd in the shell. Since cd is not prepared for Clover 2, please change the current directory with this. You may also create a class method called cd in the Global class.

(Command.cd method is difined in the current version.)

```
    > p"my_dir".mkdir ();
    > ls("-dl", "my_dir");
    drwxr-xr-x 2 ab 25 cq ab 25 cq 4096 March 2 12: 34 my_dir /
```
Create a directory. Permission is 0755. If you want to create it with different permissions, please specify 0700 as the first argument.
```
    > p"my_dir".rmdir ();
    > ls("-dl", "my_dir");
    I can not access ls: my_dir /: no such file or directory
```
Delete the directory.
```
    > p"src/".entries ()
    list {src/byte.c, src/exception.c, src/script_ctime.c, src/constant.o, ...., src/code.c}
```
Returns a list of files in the directory as a SortableList <String> type.
```
    > p"src/".glob("*. c")
    list {src/byte.c, src/exception.c, src/script_ctime.c, ..., src/code.c}
```
Returns a list of files matching the glob as a SortableList <String> type.
