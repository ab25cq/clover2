# Container library

A container library is a collection of classes that hold values. It is also called a collection. A collection can have multiple values ​​like one array
You can put in.
There are Array, List, Hash, Tuple.

Array is just a wrapper class of arrays to make method calls to arrays that are primitive types.
As a result, you can not add or delete elements, but random access by index (access to the middle of elements and favorite places rather than access from the beginning) is as fast as an array.

List is a collection whose length can be changed, and you can add or delete elements. However, random access by index is slow.
(It is accessed by tracing from the first element). However, it will be the main class in the collection because you can increase or remove the number of elements.

Hash is also called Map in other languages ​​and holds elements with key and item pairs. Access to item with key is fastest. You can keep elements of values ​​corresponding to certain values ​​of variables.

Tuple is useful when the element types are different. In other collection libraries, only collections with the same type (interface) can be collected. (`List <Object>` etc can contain elements of different types)

## Array

Array is a wrapper class for arrays. A method call to an array will be boxed to the Array.

```
    > a: int[] = [1, 2, 3]
    3 length array of Integer
    > a.each(lambda(n:Integer) { n.println(); });
    1
    2
    3
```

Elements are also boxed and they are Integer from int. The lambda expression is an object of a block. Passing processing as a chunk to a method
I can do it. Because Array class seems not to be used so much, we do not provide any built-in methods other than each.

The representation of the value of Array is as follows.

```
    > a: Array <Integer> = array {1, 2, 3}
    3 length array of Integer
    > a.each (lambda (n: Integer) {n.println ();});
    1
    2
    3
```

There are EqualableArray, SortableArray in the group of Array class.

### EqualableArray

EqualableArray allows equals to compare arrays with identical values ​​for elements.

```
    > a: EqualableArray<Integer> = equalable_array {1, 2, 3}
    array {1, 2, 3}
    > a.equals(equalable_array {1, 2, 3});
    true
    > a.equals(equalable_array {4, 5, 6});
    false
```

In order to compare elements, the element must have a method that the IEqualable interface has.
Otherwise it can not be an element of the EqualableArray class.

```
    interface IEqualable
    {
        def equlas(right: Self): bool;
        def toString(): String;
        def clone(): Self;
    }
```

Interfaces can be assigned to interfaces whose class has methods defined by the interface. That is, in this case the elements of EqualableArray must have equals and toString methods. The type Self represents the class of its own class.
In other words, in order to become an element of EqualableArray, we define the class as follows.

```
    class EqualableArrayElementClass
    {
        value: int;
        def initialize(value:int) {
            self.value = value;
        }
        def equals(right:EqualableArrayElementClass): bool {
            return self.value == right.value;
        }
        def toString(): String {
            return self.value.toString
        }
        def clone(): EqualableArraryElementClass {
            return EqualableArraryElementClass(self.value);
        }
    }
```

Since this class can be assigned to `IEqualable`, we can create a collection called` EqualableArray <EqualableArraryElementClass> `.

### SortableArray

SortableArray can be sorted. Quick sorting is done for sorting.

```
    > a: SortableArray<Integer> = sortable_array {4, 3, 5, 1, 2}
    array {4, 3, 5, 1, 2}
    > a.sort();
    array {1, 2, 3, 4, 5}
```

In order to become an element of SortableArray

```
    interface ISortable
    {
        def equals (right: Self): bool;
        def toString (): String;
        def compare (item: Self): int;
        def clone(): Self;
    }
```

You need to implement the ISortable interface. For example, compare is defined as follows for integer type.

```
    def compare (right: Integer): int {
        if (self.value < right.value) {
            return -1;
        }
        elif (self.value == right.value) {
            return 0;
        }
        else {
            return 1;
        }
    }
```

compare is a method that compares elements and returns -1 if the lvalue value is less than the rvalue value, 1 if the lvalue value is greater than rvalue value, 0 if they are equal. Implementing this method and toString, equals can be an element of sortable_array.

## List

Since Array is just an array wrapper class, it can not change the array length. (There is no addition or deletion of elements)
The following List class should be used as a variable library (variable size) container library in many cases.
```
    > a: List <Integer> = new List <Integer> ();
    Null list
    > a.push (1);
    1 length list of Integer
    > a.push (2);
    2 length list of Integer
    > a.push (3);
    3 length list of Integer
    > a.each (lambda (item: Integer) {item.println ()});
    1
    2
    3
    3 length list of Integer
```
You can add elements to the list with the push method. We pass values ​​of primitive types such as 1 and 2 as arguments, but they are boxed into Integer type and passed to List. The primitive type itself can not be an element of List.
The representation of the value of the list is written as follows.
```
    > a: List <Integer> = list {1, 2, 3}
    > a.each (lambda (item: Integer) {item.println ()});
    1
    2
    3
    3 length list of Integer
```
You can insert elements between inserts.
```
    > a.insert (1, 10);
    4 length list of Integer
    > a.each (lambda (item: Integer) {item.println ()});
    1
    10
    2
    3
    4 length list of Integer
```
The first argument of insert can also take negative numbers. -1 is the end.
```
    > a.insert (-1, 7);
    5 length list of Integer
    > a.each (lambda (item: Integer) {item.println ()});
    1
    10
    2
    3
    7
    5 length list of Integer
```
Each is from the beginning but eachReverse executes the block from the end to the beginning.
```
    > a.eachReverse (lambda (item: Integer) {item.println ()});
    7
    3
    2
    10
    1
    5 length list of Integer
```
Replace the element with replace.
```
    > a.replace (0, 2);
    5 length list of Integer
    > a.each (lambda (item: Integer) {item.println ()});
    2
    10
    3
    7
    5 length of Integer
```
You can create a new list by changing the value of each element by block in the map.
```
    > b: List <String> = a.map (lambda (item: Integer): Anonymous {return item.toString ();})
    5 length of Integer
    > b.each (lambda (item: String) {item.println ();});
    2
    10
    2
    3
    7
    5 length list of String
```
The Anonymous class is a class that can assign any type of class. We do not type check. In this case, a string type is returned by item.toString (), but since the return type of lambda is Anonymous, compilation is passed without checking the type. Every element is converted into a string by map, and it is assigned to `b: List <String>`.

(Additionally written in 2017/10/31)
\----------
I changed it later but the definition of map changed, so I can type check it. Compilation is passed below.
```
    a: List <String> = list {1, 2, 3}. map () {| n: Integer | reutrn n.toString ()}
```
Well, this is commonplace, is not it? I refer to the definition of Kotlin's List.mpa. Internally, method generics is used. For details, see the definition of List.map in Container.clc.
\----------

Select selects those which satisfy the condition which is each element, and makes a new list.
```
    > c: List <Integer> = a.select (lambda (item: Integer): bool {return item> 5;
    2 length list of Integer
    > c.each (lambda (item: Integer) {item.println ();});
    10
    7
    2 length list of Integer
```
In this case, a numerical value larger than 5 is chosen. Although item is of type Integer, it is unboxed and becomes an int type when it is subject to the operator>, so it can be used as an operator.

subList creates a partial list.
```
    > a.sub.List (1,3) .each (lambda (item: Integer) {item.println ();});
    10
    2
    2 length list of Integer
```
It does not include the index of the second argument itself.

reverse inverts the list.
```
    > a.reverse (). each (lambda (item: Integer) {item.println ();});
    7
    3
    2
    10
    2
    5 length list of Integer
```
The list has EqualableList and SortableList like Array.

### EqualableList

An EqualableList can be an element if it implements the IEqualable interface. SortableList is ISortable.

EqualableList can compare lists to determine whether they are equal or not.
```
    > a: EqualableList <Integer> = equalable_list {1, 2, 3};
    list {1, 2, 3}
    > a.equals (equalable_list {1, 2, 3});
    true
```
### SortableList

SortableList can be sorted. It is merge sorting.
```
    > a: SortableList <Integer> = sortable_list {4, 5, 1, 3, 2};
    list {4, 5, 1, 3, 2}
    > a.sort ();
    list {1, 2, 3, 4, 5}
```
## Hash

Next time I would like to go to Hash. Hash is also called Map in other languages, and you can quickly access items that become objects, corresponding to an object used as a key. It is faster to see the example below.
```
    > a: Hash <String, Integer> = new Hash <String, Integer> ();
    hash {}
    > a.put ("Daisuke", 38);
    hash {Daisuke: 38}
    > a.put ("Yuka", 38);
    hash {Daisuke: 38, Yuka: 38}
    > a.get ("Daisuke")
    38
    > a.get ("Yuka");
    38
```
Put keys and items in pair in put. The first argument is the key and the second argument is the item. I get item from key by get.
Conversely, getKey is used to obtain the key from the item.
```
    > a.getKey (38)
    Daisuke
```
Both Daisuke and Yuka have the same item value so either Daisuke or Yuka is obtained.
The expression of the value is as follows.
```
    > b: Hash <String, Integer> = hash {"Daisuke": 38, "Yuka": 38};
    hash {Yuka: 38, Daisuke: 38}
    > b.get ("Daisuke");
    38
```
The order in which you enter the hash and the order in which it is stored are irrelevant. Each one accessing all elements is accessed regardless of the stored order.
```
    > a.each (lambda (key: String, item: Integer) {printf ("name% s age% d \ n", array {key, item});
    name Yuka age 38
    name Daisuke age 38
    hash {Yuka: 38, Daisuke: 38}
```
To prevent this, you have to create a class to store the order in combination with List. Since Clover is neither List nor Hash written in C language, it is described in Clover itself, so it is possible for users to create such classes. Or Clover is an open class so you can store such a class in Hash by storing it in Hash.

There is an interface which must also be implemented in Hash.
The interface of the first argument class of Hash Generics needs to implement the following method in IHashKey.
```
    integerface IHashKey
    {
        def getHashKey (): uint;
        def equals (right: Self): bool;
        def toString (): String;
        def clone(): Self;
    }
```
Because equals and toString came out even in ISortable, I think that explanation is unnecessary so I would like to explain getHashKey. getHashKey returns the numeric value unique to the key object. It is called a hash value. For example, if it is a String class, it is defined as follows.
```
    def getHashKey (): uint {
        key: uint = 0;
        for (i: int = 0; i < self.len; i ++) {
            key + = self.buffer[i].to_uint;
        }

        return key;
    }
```

To put it briefly, we convert all the characters of String into numbers by to_uint and return the sum. to_uint is a special field for type conversion, but there is no method in the primitive type, but there is a special field for type conversion. It is like a method. There is no particular problem with hash values ​​even if they conflict (even if they return the same value), but when conflicting get etc. accessing the value of the hash will be slightly delayed. Please return unique values ​​as much as possible.

The second argument of Hash's Generics is IEqualable and it is OK if equals and toString methods are present as described above.

Hash also has the following methods.
```
    > a: = hash {"Daisuke": 38, "Yuka": 38, "Kuniko": 34, "Tomoaki": 35};
    hash {Tomoaki: 35, Yuka: 38, Daisuke: 38, Kuniko: 34}
    > a.length ();
    4
```

length () returns the number of hash keys and item pairs.
In the description of a: = hash, Clover can omit the type name at the time of variable declaration, so it can be written like this.
```
    > a.equals (hash {"Daisuke": 38});
    false
    > a.equals (hash {"Tomoaki": 35, "Daisuke": 38, "Kuniko": 34, "Yuka": 38});
    true
```
equals will return true if the key matches the stored item. Since the hashes are in no particular order, the order does not matter.

## Tuple

I would like to move on to Tuple next time. Tuple would also take an example sooner.
```
    > a: Tuple3<String, Integer, String> = tuple {"Daisuke", 38, "Kameoka"}
    tuple {Daisuke, 38, Kameoka}
    > a.value1
    Daisuke
    > a.value 2
    38
    > a.value 3
    Kameoka
```

The class name of Tuple must specify the number of arguments of Generics. For example, Tuple1 if there are one argument, Tuple2 if two, Tuple3 if three. To access the first value, please access the field called value1. The second one is value 2.

There are the following methods.
```
    > a: = tuple {"Daisuke", 38, "Kameoka"};
    tuple {Daisuke, 38, kameoka}
    > a.equals {tuple {"Daisuke", 38, "Kyoto"};
    false
    > a.equals {tuple {"Daisuke", 38, "Kameoka"};
    true
```
You can compare equals with the same value. The interface that I have to implement with Tuple Generics is IEqualable. equlas and toString must be implemented.
```
    interface IEqualable
    {
        def equlas (right: Self): bool;
        def toString (): String;
        def clone(): Self;
    }
```
That is the end of the collection.

sortable_list {1,2,3} is slist {1,2,3}, equalable_list {1,2,3} is elist {1,2,3}, sortalbe_array {1, 2, 3} Sarray {1,2,3}, equalable_array {1, 2, 3} can be declared as earray {1, 2, 3}.

Tuples can be written as (1, "AAA", 2), and so on.

    a:Tuple3<String, String, Integer> = ("AAA", "BBB", 1)
    assert(a.value1.equals("AAA") && a.value2.equals("BBB") && a.value3 == 1);

Hash can be written as "["AAA"=>1, "BBB"=>2] and so on. a: Hash <String, Integer> = ["AAA"=>2, "BBB"=>3] is compiled

From version 7.0.7.
You can use expressions such as {"AAA", "BBB"} etc in the expression of SortableList. 

