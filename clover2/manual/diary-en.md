
# dialy

2018/03/05

Version 3.7.1 release. We've included simple expressions of multiple assignments and tuples. Well, even perl had multiple assignments, so I thought I had to enter. You can exchange values ​​of variables etc. (x, y) = (y, x). The rvalue value is a shorthand notation of a tuple. A bit tuple was hard to use, but I think that it became easier to use with this. When returning multiple values ​​with a method it is a good idea to use a tuple. So, on the part receiving the return value of the method, it would be useful to receive the value as a local variable with multiple assignment. However, there is a little dirty. With this multiple assignment it is not possible to assign to a field or class field. I may implement it again if you feel like it. After that, Thread, Socket after the unfinished afterwards, I wonder ,,,,,.

I might leave it to the end, but .... Socket is just a library, so you can implement it right away, but Thread took three months to stabilize with Clover 1, so I do not know if it can be implemented a bit. In addition, I hope that you feel like it. I also want to implement something that is not found in Clover 2 in Ruby's underlying library, though. Well, I will implement it carefree. I think that reflection is seldom necessary. It is funny though. I think that compiling time is more cool for Turing complete. It may be pretty fun making it. That certainly sounds interesting, is not it?

2018/02/23

Version 3.6.5 release. For now, I think REPL's supplementation has stabilized. src/interpreter.c is quite spaghetti> program. However, I think that it can not be helped to make the coding close to the user interface somewhat complicated. So I had a hard time fixing the bugs. I do not want to mess with it anymore.

There is a feeling of having done with version 3.6.5. There are libraries that have to enter Thread, Socket, etc, but we will live by retirement. All I have to do is to add 1 method, C language library and system call everyday. There is also a way to provide Thread as a native method without creating a library. I wonder how many sockets can be with it. In addition, I think that Clover 2's parser combinator is made by Clover 2 itself, Lisp is implemented with Clover 2, and so on.

However, REPL is powerful like PowerShell and Java IDE. I can not use it instead of a shell. Well, there are few people who work directly on the server today, and if you become accustomed to the user interface other than POSIX shell such as bash, zsh, yash etc., there are times when you can not work with bash, There is no meaning to do. Well, if you get tired of bash try using it.

In REPL of Clover 2 I feel that I could finally wanted to be mfiler series, xyzsh. I am 22 years old when I was developing mfiler 2, and it is about 18 years. Finally I feel like I've made my favorite shell. Well, as I am also working as a care worker in a nursing home, I do not have much meaning to myself anymore .... We hope that you will be able to use REPL and write scripts and enjoy the management of the server.

Then enjoy programing!

