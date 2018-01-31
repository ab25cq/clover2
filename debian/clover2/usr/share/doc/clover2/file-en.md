# File class

A file class is a class that can write data to and read from a file. It is a simple wrapper class of System.read and System.open, and does not provide a particularly convenient method.

To write to a file, do as follows.
```
    > file:File = new File("x.txt", System.O_CREAT|System.O_TRUNC|System.O_WRONLY, 0644);
    > file.write(B"ABC");
    3
    > file.close();
    > cat("x.txt")
    ABC
```
System.O_CREAT | System.O_TRUNC | System.O_WRONLY is a flag for opening a file and means to open in write mode. (Since O_TRUNC means overwriting the file, it will be lost if x.txt already exists.) File.write (B "ABC") means to write a buffer called B "ABC" to the file. B "" is a representation of the value of the Buffer class. I do not explain the Buffer class, but unlike String, I can handle raw texts and binary files. To convert from a String, use "ABC" .toBuffer () and so on. In this case, we create a Buffer object that has just three alphabet characters as data and write it in the file. I close it after writing. Even without closing, it will be done at the end of the program, but since the number of files one process can open is limited, it is normal to close it after using it. It seems there are times when it is actually written to the file at close time (as it is uncertain information) Please close it after using the file. It was confirmed that ABC was actually written in x.txt by cat ("x.txt").

You can also write without opening the file.
```
    > File.write("x.txt","ABC\nDEF\nGHI\n".toBuffer());
    12
    > cat("x.txt")
    ABC
    DEF
    GHI
```
Note that in this case O_TRUNC is specified internally, so it will be forcibly overwritten. If you want to specify file permissions, do as follows.
```
    > File.write("x.txt", B"ABC", 0777);
    3
```
About file permissions is the foundation of UNIX, please search and learn. In this case 0777 so other users have write permission.

Next we will explain the case of reading.
```
    > file2: File = new File("x.txt");
    > data: Buffer = file2.read();
    ABC
    DEF
    GHI
    > file2.close();
    > data.toString().print()
    ABC
    DEF
    GHI
```
If you specify read size as read (3) etc., you can read the file by the specified number of bytes.

There is also a method of reading a file which does not open a file.
```
    > File.read("x.txt")
    ABC
    DEF
    GHI
```
However, since it does not perform read or write or buffering etc, we do not know whether speed will come out due to processing of very large files etc. That user is left to the user.

Reading and writing files is over.
