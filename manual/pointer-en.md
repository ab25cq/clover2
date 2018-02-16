# pointer class

The pointer class treats addresses as primitive types. However, since invalid addresses can also be accessed, care must be taken in handling. No type checking is done. I use it as follows.
```
    > a: int = 123;
    123
    > b: pointer = & a;
    0x124a778
    > b -> int = 245;
    245
    > a
    245
```
&a obtains the address of a and assigns that address to b. `b->int` treats address b as int type and assigns 245. Then, a itself will also be assigned with 245. If it is used as an argument of a method, it can be used as a method return value. In that case
```
    def method(b: pointer @int)
```
Please add a model name with @ after pointer as shown. This is to indicate that you want to pass the address of int to b. @ The following is a simple comment with annotation, but since it is possible to assign any address to the pointer type, it is better to specify the type name by annotation.

Addition and subtraction can be used for pointer class. For example, if b ++
```
    > b++;
    0x124a778
    > b
    0x124a779
```
. Adding and subtracting are ++ byte units and one byte of address increases. - decreases the 1 byte address.
```
    > b + = 4ul;
    0x124a77d
```
\+= 4ul and four bytes are added to the address of b. The ulong type is used for the right side value of the pointer operation. In the case of a 64 bit PC, the address is for ulong type which is 64 bit. The value is different every time to prevent illegal addresses. It was because the address was fixed and it was a hotbed of invalid hacks because it was the same each time. When MS - DOS was the de facto standard, I could access even the addresses of other programs (processes), so I could do bad things with other programs as much as possible. Well, at that time the computer seemed to be some people's play, because it was not as secure as it was for security. Since the Internet began and credit card involvement allowed illegal use of other people's money, security became more important. Recently, addresses are independent on a process basis, and addresses of other programs are not accessible, and address values ​​are also different every time, so it is difficult to make illegal programs.

Additional notes
The right side value of the pointer operator is okay if it is not ulong type. In the above code, it moves with b += 4 instead of b += 4ul.
