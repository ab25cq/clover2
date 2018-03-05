# コンテナライブラリ

English page is here [>> English page](collecton-en)

コンテナライブラリとは値を保持するクラスの集まりです。コレクションとも呼ばれます。コレクションは配列のように複数の値を一つの変数に
入れることができます。
Array, List, Hash, Tupleがあります。

Arrayは単なる配列のラッパークラスで、プリミティブ型である配列にメソッドコールができるようにするためにあります。
そのため要素の追加や削除をすることができませんが、インデックスによるランダムアクセス（先頭からアクセスするのではなくて要素の真ん中や好きな場所へのアクセス）は配列と同じく最速です。

Listは長さの変えられるコレクションで、要素の追加や削除をすることができます。ただし、インデックスによるランダムアクセスは遅いです。
（先頭の要素から辿ってアクセスされます）。しかし、要素の数を増やしたり削除したりできるためコレクションでは主力となるクラスでしょう。

Hashは他の言語ではMapとも呼ばれて、keyとitemのペアで要素を保持します。keyでのitemへのアクセスは最速です。変数のある値に対応した値の要素を保持することができます。

Tupleは要素の型がそれぞれ違う場合に便利です。他のコレクションライブラリでは同じ型（インターフェース）を持つものしかコレクションできません。(`List<Object>` などとすれば型の違う要素を入れることができますが)

## Array

Arrayは配列のラッパークラスです。配列にメソッドコールを行うとArrayにboxingされます。

    > a:int[] = [ 1, 2, 3 ]
    3 length array of Integer
    > a.each(lambda(n:Integer) { n.println(); });
    1
    2
    3

要素もboxingされてintからIntegerとなっています。lambda式はブロックのオブジェクトです。処理を塊としてメソッドに渡すことが
できます。Arrayクラスはあまり使わないと思われるためeach以外の組み込みのメソッドは特に用意していません。

Arrayの値の表現は以下です。

    > a:Array<Integer> = array { 1, 2, 3 }
    3 length array of Integer
    > a.each(lambda(n:Integer) { n.println(); });
    1
    2
    3

Arrayクラスの仲間にEqualableArray, SortableArrayがあります。

### EqualableArray

EqualableArrayはequalsによって配列同士を同一の値を要素が保持しているか比較することができます。

    > a:EqualableArray<Integer> = equalable_array { 1, 2, 3 }
    array { 1,2,3 }
    > a.equals(equalable_array { 1, 2, 3 });
    true
    > a.equals(equalable_array { 4, 5, 6});
    false

要素同士の比較のため要素にはIEqualableインターフェースが持つメソッドがある必要があります。
それ以外はEqualableArrayクラスの要素となることができません。

    interface IEqualable 
    {
        def equlas(right:Self): bool;
        def toString(): String;
    }

インターフェースはインターフェースが定義するメソッドを持つクラスはインターフェースに代入することができます。つまり、この場合EqualableArrayの要素はequalsとtoStringメソッドを持つ必要があります。Selfという型はそのクラス自身のクラスを表します。
つまり、EqualableArrayの要素になるためには以下のようにクラスを定義します。

    class EqualableArrayElementClass
    {
        value:int;
        def initialize(value:int) {
            self.value = value;
        }
        def equals(right:EqualableArrayElementClass):bool {
            return self.value == right.value;
        }
        def toString(): String {
            return self.value.toString
        }
    }

このクラスは `IEqualable` に代入することができるので、`EqualableArray<EqualableArraryElementClass>` というコレクションを作ることができます。

### SortableArray

SortableArray はソートすることができます。ソートにはquick sortが行われています。

    > a:SortableArray<Integer> = sortable_array { 4, 3, 5, 1, 2 }
    array {4, 3, 5, 1, 2}
    > a.sort();
    array {1, 2, 3, 4, 5}

SortableArrayの要素になるためには

    interface ISortable
    {
        def equals(right:Self): bool;
        def toString():String;
        def compare(item:Self): int;
    }

ISortableインターフェースを実装する必要があります。compareは例えばInteger型なら以下のように定義されています。

    def compare(right:Integer): int {
        if(self.value < right.value) {
            return -1;
        }
        elif(self.value == right.value) {
            return 0;
        }
        else {
            return 1;
        }
    }

compareは要素同士を比較して左辺値が右辺値より小さいときは-1、大きいときは1、等しいときは0を返すメソッドです。このメソッドとtoString, equalsを実装するとsortable_arrayの要素となることができます。

## List

Arrayは単なる配列のラッパークラスなので配列長さを変えたりすることはできません。(要素の追加や削除はない)
次のListクラスが可変長（サイズの変えられる）のコンテナライブラリとして使うことが多いはずです。

    > a:List<Integer> = new List<Integer>();
    Null list
    > a.add(1);
    1 length list of Integer
    > a.add(2);
    2 length list of Integer
    > a.add(3);
    3 length list of Integer
    > a.each(lambda(item:Integer) { item.println() });
    1
    2
    3
    3 length list of Integer

addメソッドによってリストに要素を追加することができます。1や2などプリミティブ型の値を引数として渡していますがInteger型にboxingされてListに渡されています。プリミティブ型自体はListの要素になることはできません。
リストの値の表現は以下のように書きます。

    > a:List<Integer> = list { 1,2,3 }
    > a.each(lambda(item:Integer) { item.println() });
    1
    2
    3
    3 length list of Integer

insertで間に要素を入れることができます。

    > a.insert(1, 10);
    4 length list of Integer
    > a.each(lambda(item:Integer) { item.println() });
    1
    10
    2
    3
    4 length list of Integer

insertの第一引数は負数もとることができます。-1が末尾です。

    > a.insert(-1, 7);
    5 length list of Integer
    > a.each(lambda(item:Integer) { item.println() });
    1
    10
    2
    3
    7
    5 length list of Integer

eachは先頭からですがeachReverseは末尾から先頭までブロックを実行します。

    > a.eachReverse(lambda(item:Integer) { item.println() });
    7
    3
    2
    10
    1
    5 length list of Integer

replaceで要素を置き換えることができます。

    > a.replace(0,2);
    5 length list of Integer
    > a.each(lambda(item:Integer) { item.println() });
    2
    10
    3
    7
    5 length of Integer

mapで各要素の値をブロックによって変えて新たなリストを作ることができます。

    > b:List<String> = a.map(lambda(item:Integer):Anonymous { return item.toString(); })
    5 length of Integer
    > b.each(lambda(item:String) { item.println(); });
    2
    10
    2
    3
    7
    5 length list of String

Anonymousクラスはどんな型のクラスも代入することができるクラスです。型チェックをしません。この場合item.toString()で文字列型が返されてますが、lambdaの戻り値の型はAnonymousなので型チェックせずにコンパイルが通ります。mapによってすべての要素が文字列になり、 `b:List<String>` に代入されています。

(2017/10/31に追記)
ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
後からの変更ですがmapの定義が変わったので、型チェックが行えるようなりました。以下はコンパイルが通ります。

    a:List<String> = list { 1, 2, 3 }.map() {|n:Integer| reutrn n.toString() }

まあ、これが通って当たり前ですね。KotlinのList.mpaの定義を参考にしてます。内部的にはmethod genericsが使われています。詳しくはContainer.clcのList.mapの定義を見てください。
ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

selectは各要素である条件を満たすものを選んで新たなリストを作ります。

    > c:List<Integer> = a.select(lambda(item:Integer):bool { return item > 5; });
    2 length list of Integer
    > c.each(lambda(item:Integer) { item.println(); });
    10
    7
    2 length list of Integer

この場合は5より大きな数値が選ばれています。itemはInteger型ですが演算子>の対象になるとunboxingされてint型となるので演算子の対象にすることができます。

subListは部分リストを作ります。

    > a.subList(1,3).each(lambda(item:Integer) { item.println(); });
    10
    2
    2 length list of Integer

第二引数のインデックス自身は含みません。

reverseはリストを反転します。

    > a.reverse().each(lambda(item:Integer) { item.println(); });
    7
    3
    2
    10
    2
    5 length list of Integer

リストにはArrayと同じくEqualableListとSortableListがあります。

### EqualableList

EqualableListはIEqualableインターフェースを実装していれば、要素にすることができます。SortableListはISortableです。

EqualableListはリスト同士を比較して等しいか等しくないかを判定することができます。

    > a:EqualableList<Integer> = equalable_list { 1,2,3 };
    list {1,2,3}
    > a.equals(equalable_list { 1, 2, 3});
    true

### SortableList

SortableListはソートすることができます。マージソートしています。

    > a:SortableList<Integer> = sortable_list { 4,5,1,3,2 };
    list {4,5,1,3,2}
    > a.sort();
    list {1,2,3,4,5}

## Hash

次はHashにいきたいと思います。Hashは他の言語ではMapとも呼ばれて、キーとして使う、あるオブジェクトに対応した、アイテムとなるオブジェクトに素早くアクセスすることがでます。以下の例を見たほうが早いでしょう。

    > a:Hash<String, Integer> = new Hash<String, Integer>();
    hash {}
    > a.put("Daisuke", 38);
    hash {Daisuke:38}
    > a.put("Yuka", 38);
    hash {Daisuke:38,Yuka:38}
    > a.get("Daisuke")
    38
    > a.get("Yuka");
    38

putでキーとアイテムをペアでaに入れています。第一引数がキーで第二引数がアイテムです。getによってキーからアイテムを得ています。
逆にアイテムからキーを得る場合はgetKeyを使います。

    > a.getKey(38)
    Daisuke

DaisukeもYukaもアイテムの値が同じなのでDaisukeかYukaかどちらかが得られます。
値の表現は以下です。

    > b:Hash<String, Integer> = hash { "Daisuke":38, "Yuka":38 };
    hash {Yuka:38,Daisuke:38}
    > b.get("Daisuke");
    38

ハッシュには入れた順番と格納されている順番は無関係です。全部の要素にアクセスするeachは格納されている順番とは全然関係なくアクセスされます。

    > a.each(lambda(key:String, item:Integer) { printf("name %s age %d\n", array { key, item }); }
    name Yuka age 38
    name Daisuke age 38
    hash {Yuka:38,Daisuke:38}

これを防ぐにはListと組み合わせて順番を格納するクラスを作るしかないです。CloverはListもHashもC言語で書かれていなくてClover自身で記述されているので、そのようなクラスをユーザーが作ることも可能です。もしくはCloverはopen classなのでHashにListを格納して、そのようなクラスを作ることも可能でしょう。

Hashにも実装されていないといけないインターフェースがあります。
HashのGenericsの第一引数のクラスのインターフェースはIHashKeyで以下のメソッドが実装されている必要があります。

    integerface IHashKey
    {
        def getHashKey(): uint;
        def equals(right:Self): bool;
        def toString(): String;
    }

equalsやtoStringはISortableでも出てきたので説明は不要だと思うのでgetHashKeyの説明をしたいと思います。getHashKeyとはキーとなるオブジェクト固有の数値を返すものです。ハッシュ値と呼ばれます。例えばStringクラスなら以下のように定義されています。

    def getHashKey(): uint {
        key:uint = 0;
        for(i:int = 0; i<self.len; i++) {
            key += self.buffer[i].to_uint;
        }
>
        return key;
    }

これは簡単に言うとStringのすべての文字をto_uintによって数値に変換して合計したものを返しています。to_uintは型変換用のスペシャルフィールドでプリミティブ型にはメソッドがありませんが、型変換用にスペシャルフィールドはあります。メソッドのようなものです。ハッシュ値は衝突しても（同じ値を返しても）特に問題はありませんが、衝突するとハッシュの値にアクセスするgetなどが少し遅くなります。できるだけ固有の値を返してください。

HashのGenericsの第二引数はIEqualableで前述したとおりにequalsとtoStringメソッドがあればOKです。

Hashには以下のようなメソッドもあります。

    > a := hash { "Daisuke":38, "Yuka":38, "Kuniko":34, "Tomoaki":35 };
    hash {Tomoaki:35,Yuka:38,Daisuke:38,Kuniko:34}
    > a.length();
    4

length()はハッシュのキーとアイテムのペアの数を返します。
a := hashという記述はCloverは変数の宣言時に型名は省略できるのでこのように記述できます。

    > a.equals(hash {"Daisuke":38});
    false
    > a.equals(hash {"Tomoaki":35, "Daisuke":38, "Kuniko":34, "Yuka":38 });
    true

equalsは格納されているアイテムとキーが一致すればtrueを返します。ハッシュは順不同なので順番は関係がありません。

## Tuple

次にTupleに移りたいと思います。Tupleも例を見ていただいたほうが早いでしょう。

    > a:Tuple3<String, Integer, String> = tuple { "Daisuke", 38, "Kameoka" } 
    tuple {Daisuke,38,Kameoka}
    > a.value1
    Daisuke
    > a.value2
    38
    > a.value3
    Kameoka

Tupleのクラス名はGenericsの引数の数を明示しないといけません。例えば引数が1個ならTuple1, 2個ならTuple2, 3個ならTuple3です。一つ目の値にアクセスするためにはvalue1というフィールドにアクセスしてください。２つ目はvalue2です。

以下のメソッドがあります。

    > a := tuple { "Daisuke", 38, "Kameoka" };
    tuple {Daisuke,38,kameoka}
    > a.equals(tuple {"Daisuke", 38, "Kyoto" });
    false
    > a.equals(tuple {"Daisuke", 38, "Kameoka" } );
    true

equalsで値が同一か比較することができます。TupleのGenericsで実装しておかないといけないインターフェースはIEqualableです。equlasとtoStringが実装されている必要があります。

    interface IEqualable 
    {
        def equlas(right:Self): bool;
        def toString(): String;
    }

以上でコレクションは終わりです。

後からの追加ですがsortable_list{1,2,3}はslist{1,2,3}, equalable_list{1,2,3}はelist{1,2,3},sortalbe_array{1,2,3}はsarray{1,2,3}, equalable_array{1,2,3}はearray{1,2,3}と省略して宣言することができます。

タプルは(1, "AAA", 2)などと書けます。

    a:Tuple3<String, String, Integer> = ("AAA", "BBB", 1)
    assert(a.value1.equals("AAA") && a.value2.equals("BBB") && a.value3 == 1);

