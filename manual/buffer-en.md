# Buffer class

The String class represents a string, but the buffer class represents a byte string. Internally, I allocate memory by pointing to the pointer object malloc. How to use is below.
```
    > a: Buffer = new Buffer(3.to_ulong);
    > a.append('A'.to_byte);
    > a.append('B'.to_byte);
    > a.append('C'.to_byte);
    > a
    ABC
```

Please note that it is not null-terminated. When it is toString () it is null-terminated, but in the above example the buffer contains only ABC and 0 is not at the end.
Buffer objects can also be append.
```
    > a: Buffer = new Buffer(3.to_ulong);
    > a.append(B"ABC");
    > a
    ABC
```
The object representation of the Buffer class is B "". The size of the Buffer class is not fixed, and when it is appended, new memory is automatically allocated automatically. Please be aware that the memory in self.buffer may change as it is reallocated at that time.
Data can be accessed by offset (index from the first memory) in chars. The return value is byte.

```
    > a: Buffer = B"ABC";
    ABC
    > a.chars(0)
    65
    > a.chars(1)
    66
    > a.chars(-1)
    67
```

You can compare the Buffer object with equals.

```
    > B"ABC".equals(B"ABC")
    true
    > B"ABC".equals(B"DEF")
    false
```

A partial buffer can be set with subBuffer.

```
    > B"ABCDEF".subBuffer(1,3);
    BC
    > B"ABCDEF".subBuffer(3,-1);
    DEF
```


-1 indicates the end.
