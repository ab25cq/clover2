# 構文

English page is here [>> English page](feature-en)


## フリーフォーマット

clover2はフリーフォーマットです。特に改行や空白には意味がありません。自由に改行や空白を入れてください。

## 変数と関数について

変数とはデータの入れ物です。アセンブラというコンピュータが直接理解できる機械語レベルではメモリを表します。
コンピュータとはもともと人間の知能を模すため作られたものですが（子供がいなかったイギリスのバベッジ夫妻が考えました）
人間にも記憶があるようにコンピュータにも記憶する場所があります。機械語レベルではメモリがそれを表します。
メモリとは記憶を格納するための場所でアドレスという番地（住所みたいなもの）に1か0かが格納されています。
1か0かが格納できればメモリと呼べます。今は電子的に1か0かを格納していますが、最初は歯車で表していたそうです。
変数はこのメモリのようにデータを記憶する場所で例えば

    a:int = 256;

とclover2では書きますが、この場合aという名前の変数に256という数値が格納されます。
機械語レベルではaはある番地(8bitのコンピュータの場合16進数でいえば0x0000から始まり0xFFFFで終わります。)の別名で
そこに256という数値が格納されます。人間でいうとaという名前に256という数値を記憶するようなものです。
メモリは1か0かしか格納できないのですが、256は16進数では0xFFで2進数でいえば11111111で1か0かでも表現することができます。
intというのはデータの型で簡単にいうとデータの種類のことです。例えば文字列の場合

    b:String = "ABC"

などと書き、文字列データ"ABC"をbという変数に格納します（記憶します）。
記憶すると何がうれしいかというとデータを処理するときに統一的に処理することができます。
例を出す前に関数のことも説明しておきます。関数とは手続きの単位です。ある定型処理に名前を付けて何度も使いまわしてやろうというものです。
例えば

    def show(name:String, age:int) {
        println(name);
        println(age.toString());
    }

と関数を定義すると

    show("Daisuke Minato", 39);
    show("Yuka Minato", 38)

などと呼び出すと一回showを作るだけで別のデータを何度も出力することができます。
関数には引数を取ることができ、引数は変数に格納されます。
上の例でいえばnameが第一引数で文字列型、ageが第二引数で数値型を表します。
printlnは文字列を表示する関数でnameという名前のデータをまず表示しています。
次にage、年齢を表示しています。.toString()は型変換を行うもので数値型を文字列型に変換しています。
ここでは深く考えないでください。
このプログラムの実行結果は

    Daisuke Minato
    39
    Yuka Minato
    38

です。プログラムはこのように変数と関数で出来上がっていています。このようなプログラミング方法を構造化プログラミングと呼びます。
その前は関数がなく、機械語を直接書いて上から下に処理する方式がとられていました。僕も最初はそのような言語から
プログラムを覚えました。最近の言語は構造化プログラミングが最低条件でもっと新しいパラダイムが出ています。
それがオブジェクト指向でclover2はオブジェクト指向言語です。
オブジェクト指向は関数やデータをクラスという一つまとめにして扱おうという考え方でできています。
あるデータというのは密接な関係をもつ関数が必ずあります。そのため、それをクラスでまとめてしまって
プログラムを書きやすくしたり読みやすくしようというものです。

## 条件分岐と演算子

変数には値が格納できると説明しましたが、ある値に対して特別な処理を行いたい場合条件分岐を使います。

    age:int = 39;
    if(age >= 40) {
        println("40 age over");
    }
    elif(age >= 30) {
        println("30 age over");
    } 
    else { 
        println("You are young");
    } 
    println("END");

上記のようにif文を使います。ageという年齢を表す変数に39という数値型を入れてます。
もしこのageの値が40歳以上なら40 age overと出力されます。
30歳以上なら30 age overです。それ以外だとYou are youngと表示されます。この場合ageには39が入っているので30 age overと
表示されるはずです。
ageの後の>=は比較演算子で左右を比較して左のほうが大きければtrueを返します。もしif文の()の中がtrue(真)なら、そのあとの{}の中身が
実行されます。{}を実行したあとはelif, elseの部分は飛ばされて最後のprintln("END");の部分が実行されます。
もし、ageの値が41であれば、40 age overが実行されて、最後のprintln("END");が実行されます。elseはどのif文やelif文がtrueに
ならない場合(すべてがfalse(偽）の場合)に実行されます。
比較演算子には以下のものがあります。

    --- 比較演算子 ---
    演算子
    a < b aはbより小さい
    a <= b aはb以下
    a > b aはbより大きい
    a >= b aはb以上
    a == b aとbは等しい
    a != b aとbは異なる

次は算術演算子の説明に入ります。算術演算子とは足し算や引き算のことで数値型の変数や値に対して計算を行うことができます。

    age:int = 39 + 10;
    if(age >= 40) {
        println("40 age over");
    }
    elif(age >= 30) {
        println("30 age over");
    }
    else {
        println("You are young");
    }
    println("END");

上の例をもう一度出してageの39に+ 10しています。そうするとageには49が入り、今度は40 age overが表示されるはずです。

    --- 算術演算子 ---
    a + b aとbの足し算
    a - b aからbを引いた結果を返す
    a * b aとbの掛け算の結果を返す
    a / b aとbの割り算
    a % b aをb割り算してあまりの値

ちなみに行末の;はclover2ではあってもなくても大丈夫です。ただC言語とか他の言語の場合、必要になることがあるので
慣習的に;をつける癖をつけておくほうが無難です。

if文には戻り値があります。以下のようなものです。

    > a: int = if(true) { 123 };
    123
    > a
    123

最後に実行された値を返します。

    > b := 123;
    > a := if(b == 123) { 123 } else { "ABC" }
    > Clover.test("if result test", a.cast("int") == 123);

この場合はaはAnonymous型となります。使う場合はキャストしてください。

## 論理演算子

if文に2つの条件を付けたい場合などでは論理演算子を使います。

    age:int = 39 + 10;
    if(age >= 40 && age <= 49) {
        println("forty (years of age)");
    }
    elif(age >= 30 && age <= 39) {
        println("thirty (years of age)");
    }
    else {
        println("You are young or old");
    }
    println("END");

    a && b aとbが共に真の場合「真」
    a || b aまたはbが真の場合「真」
    !a aが偽の場合「真」、aが真の場合「偽」

上の例だとage >= 30 && age <=39でage >= 30がtrueかつage <= 39がtrueになると式全体がtrueとなります。

## ビット演算子

ビット演算子はビット単位でデータを操作する演算子です。操作できる型は整数です。

    a & b aとbのビット単位のAND
    a | b aとbのビット単位のOR
    a ^ b aとbのビット単位の排他的OR
    << 左シフト
    a << b aをbビット分、左へシフト
    a >> b aをbビット分、右へシフト
    ~a aの各ビットを反転

ビット演算子はローレベルの整数の処理を行う場合に使われます。あまり最初のうちは使わないでしょう。
バイナリファイルの処理やフラグの処理に使われます。
ANDは数値にビットが含まれているかどうかでよく使います。
ORは数値にビットを含める場合によく使います。
ビットの反転に&0xFFなどを取ればあるビットをなくすことができます。

## ループ

ループとはプログラムの流れを制御するためのものです。繰り返し処理を行いたい場合に使われます。
clover2にはwhile文とfor文があります。とりあえず、例を出します。

    i:int = 1;
    while(i < 3) {
        println("HELLO LOOP");
        i++;
    }
    println("END");

このプログラムはまず、変数iに1が入ります。そしてwhile文に入る前にwhile文のi < 3が実行されます。これがtrueなら
ループの中に入ります。{}の中のことです。そして、println("HELLO LOOP");でHELLO LOOPが実行されます。その後i++で
iに2が入ります。++とはインクリメント演算子で変数の値をプラス1します。その後はまたループの最初に戻ります。
i < 3が真ならもう一度ループを実行します。この場合iは2なので、もう一度実行されるでしょう。
ループの中をもう一度実行すると、こんどはiは3となっているはずです。今度のi < 3はfalseとなるのでループの中は実行されません。
最後のprintln("END");が実行されます。結局HELLO WORLDが3回表示されて、最後にENDが表示されるということですね。<br>
for文に移ります。

    for(i:int = 0; i<3; i++) {
        println("HELLO LOOP");
    }
    println("END");

このプログラムの結果はさっきと全く一緒です。HELLO LOOPが3回表示されてENDが最後に表示されます。詳しく追っていくと、まずforの中のi:int = 0;が実行されます。そしてi<3が真ならループの中が実行されます。ループを実行した後はi++が実行されます。そしてi<3がtrueならまたループを実行します。i<3がfalseになったら、ループを抜けます。
<br>
ループの中でループを脱出したくなるときはbreak文を使います。僕がよく使うのは無限ループとbreak文です。while文の条件式に条件を明記しないことはあまりよくないと言われますが、僕は無限ループとbreak文のほうが読みやすいプログラムがある場合もあると考えてます。

    i:int = 0;
    while(true) {
        if(i == 3) {
            break;
        }
        else {
            println("HELLO LOOP");
            i++;
        }
    }
    println("END");

このプログラムも前のループの例と実行結果は全く同じでHELLO LOOPを3回表示して最後にENDを表示して終わります。このプログラムを説明します。まず、iに0が入ります。その後while文の条件式trueにきます。これが真ならループを実行します。もちろんtrueなので何度判定しても真です。if文の条件式i==3が実行されます。iは0なので偽ですのでelseの部分が実行されます。println("HELLO LOOP"); i++;です。iが1になりました。その後はまたwhile文の条件式にきます。trueなので、もう一度ループが実行されます。今度もiは1なのでelse文が実行されます。HELLO LOOPが表示されてiが2になります。そしてまたwhile文の条件式にきます。trueなので、もう一度ループが実行されます。iは2なのでelse文が実行されます。HELLO LOOPが表示されてiが3になります。今度もwhile文はtrueなのでもう一度ループが実行されます。if文のi == 3はtrueなのでif文のブロックが実行されます。break;です。すると今度はwhile文から脱出して、最後のprintln("END");が実行されます。このようにbreakは実行されるとループから脱出します。ちなみにC言語にはcontinue文というのもあるのですが、clover2にはありません。長らくC言語を使ってますが、僕は一度程度しかcontinue文を使ったことがないので、入れませんでした。ほとんどの場合はwhile,for,if,breakでプログラムの流れは制御できると思います。昔は行番号やラベルというものがあり、上から下にプログラムは実行されてループがなく、GOTO文というある特定の行番号へ移動する命令を使って流れを制御していました。現在はGOTO文の代わりにwhile,for,if,breakでプログラムの流れは制御できることが分かりGOTO文と行番号は廃止されてます。C言語にはラベルとgotoがありますが、clover2にはありません。goto文を使いたい場面はないことはないです。ループが2重にも3重にもなっていいて、その一番奥のループから脱出したい場合です。clover2にはgoto文がないので、この場合は困るかもしれません。一応以下のようにフラグを使って多重のループを脱出する方法があるので、そうしてください。

    flg_loop_out:bool = false;
    value1:int = 128;
    for(i:int =0; i<3; i++) {
        for(j:int =0; j<3; j++) {
            for(k:int =0; k<3; k++) {
                if(value == 128) {
                    flg_loop_out = true;
                    break;
                }
            }
            if(flg_loop_out) {
                　break;
            }
        }
        if(flg_loop_out) {
            break;
        }
    }

ちょっとわかりずらいですがflg_loop_outがtrueになるとすべてのfor文から脱出ができます。

## ブロック

一つの式で幾つかの式を実行したい場合ブロックが便利です。以下のように使います。

    > { println("HELLO"); println("HELLO"); println("HELLO"); }
    HELLO
    HELLO
    HELLO

最後に実行された値がブロックの戻り値です。

    > a: int = { 123 };
    123
    > a
    123

## コメント

/\*と\*/で囲まれた部分（複数行可能）がコメントになります。
あと一行のコメントは#から始まり行末(\n)までです。

    /*
       Output Hello World Program
    */
    
    println("HELLO WORLD");       # output HELLO WORLD

コメントは実行されません。コンパイル時に削除されます。

## アノテーション

型名のあととメソッドの引数の後には@をつけることによってアノテーションをつけることが出来ます。
アノテーションはコメントの一種です。メソッドの引数に分かりやすいようにコメントをつけることが出来ます。
アノテーションは英数字と_を使うことが出来ます。

    def fun(str:String, number:int) {
        return str.append(number.toString());
    }
    fun("ABC"@str, 123@number);
    def fun2(str:String@Nullable, p:pointer@int[]) {
        /* 処理 */
    }
    a := new int[123];
    fun2(null, &a);

このように使います。

## ナルエイブル

nullは空を表す値で、Nullクラスのインスタンスです。nullはプリミティブ型以外のクラス全ての変数に代入することができます。ただし制限があって、クラス名の後に?がある変数にしかnullは代入することができません。クラス名の後に?がある場合はnullが入っているかもしれないと注意してコードを読んで下さい。

    a:String = null;   # コンパイルエラー

    b:String? = null;   # nullは代入できる。bは空だということでnullを代入している。
                        # ただし、bはnullが入っているかどうか注意してコーディングしないといけない

## プリミティブクラス

    byte: 8bit符号付き数値型
    ubyte: 8bit符号なし数値型
    short: 16bit符号付き数値型
    ushort: 16bit符号なし数値型
    int: 32bit符号付き数値型
    uint: 32bit符号なし数値型
    long: 64bit符号付数値型
    ulong: 64bit符号なし数値型

数値型にはたくさん種類があります。主にデータの大きさによって判別できます。byte型は8bitで扱えるデータの大きさの数値型を扱うことができます。byteは符号付なので-128～127の数値を扱うことができます。ubyteは符号なしの8bitなので0～256の数値を扱うことができます。8bitとは何かというとメモリは1か0しか扱えないと言いましたが、8bitだと、このメモリを8つ使って数値を表現するという意味です。2進数でいうと11111111や01010101など8桁の数値を扱えるということです。ubyteだと最小値は00000000で最大値は11111111なので、これを16進数で表すと0x00から0xFFなので、扱える数は0～256まで扱えるということです。負数の表現はコンピュータによって違うことがあるかもしれませんが大体は最上位のビットが1なら負の数として扱うことが普通です。byteなら最小値が10000000で-128となり最大値が011111111が127となります。なのでbyteは-128～127までの数値を扱うことができるということです。

    float: 32bit符号付浮動小数点
    double: 64bit符号付小数点

floatは浮動小数点の型です。小数を使うことができます。doubleは64bit分のより細かな小数を使うことができます。値の表現はfloatは0.1fなど、doubleは0.11などです。floatの場合は小数にfをつけないといけません。

    pointer: アドレスを格納する型

詳しくはまた後で説明しますがアドレスを扱うことができるプリミティブクラスです。clover2はポインタがあります。ポインタ操作はメモリが保護されていないので不正なアドレス操作はスクリプト自体がSegmentation Faultを起こし落ちます。（デバッグが難しいので修正は大変です）
バイナリ操作など以外では使わないほうが無難です。ただし、引数で関数の呼び出し側の値を変えたい場合（関数に2つ以上の戻り値が欲しい場合）などでは便利に使えます。例えば

    def fun(a:pointer@int):int {
        a->int = 345;
        return 123;
    }
    
    value1:int = 0;
    value2:int = 0;
    value1 = fun(&value2)
    value1.toString().println();
    value2.toString().println();

型の後の@はアノテーションといい単なるコメントです。この場合はpointerクラスは型チェックをしないのでint型のアドレスを渡してほしいという意味でアノテーションをつけています。このプログラムの出力は123と345になります。&value2でvalue2のアドレスを得ています。そのアドレスを関数に渡しa->intでint型の値として345を代入しています。するとfunに渡したvalue2に345が代入されます。value1は単に関数の戻り値を代入しているだけなので123が代入されます。この引数の渡し方をcall by refferenceといいます。普通の引数の渡し方はcall by valueといいます。

    char: 文字列型を格納する型

文字を表す値を型です。値の表現は'A'や'あ'などです。clover2は文字や文字列をUTF32で表すため日本語の一文字もchar型として扱うことができます。

    a:char = 'A';
    b:char = 'あ';

    bool: 真偽値を格納する型

真偽値を表す型です。trueかfalseが入ります。

プリミティブ型にメソッドコールを送ることはできません。演算子のみが対象となります。
もしプリミティブ型にメソッドコールを送ると後述するboxingという機能が働きラッパークラス（包み込むクラス）
にメソッドコールが送られます。
逆に非プリミティブ型に演算子を使うとunboxingされてプリミティブ型として演算されます。

### 数の表現

    数値 123, 256など。10進数で数を表現します。
    0x数値 OxFF,0x11など。16進数で数を表現します。
    0数値 017, 011など。8進数で数を表現します。
    数値.数値f 1.1f, 2.2fなど。float型の小数を表します。
    数値.数値 1.1, 2.2など。double型の小数を表します。
    数値y 123yなど。byte型の数値を表します。
    数値uy 256uyなど。ubyte型の数値を表します。
    数値s 123sなど。short型の数値を表します。
    数値us　１２３usなど。ushort型の数値を表します。
    数値u 123uなど。uint型の数値を表します。
    数値l 123456lなど。long型の数値を表します。
    数値ul 123456ulなど。ulong型の数値を表します。

## 配列

配列とは添え字でアクセスできるオブジェクトやプリミティブ型の値の集合です。まとめて数値などを扱うことができます。

以下のようにつかいます。

    > a:int[] = new int[3]();
    3 length array of Integer
    > a[0] = 100;
    100
    > a[1] = 200;
    200
    > a[2] = 300;
    300
    > a[1]
    200

配列を作るにはもう一つ方法があります。以下のように作ります。

    > a:int[] = [ 100, 200, 300 ];
    3 length array of Integer
    > a[1]
    200;

表示では3 length array of Integerと表示されますが、内部的にはint型の配列が作られてます。インタプリタではtoString()を内部的に呼び出しているため、Array&lt;Integer&gt;というint[]の配列のラッパークラス（包み込むためのクラス）が作られてtoString()が呼び出されているためです。プリミティブ型はメソッドコールされるとラッパークラスに自動的にboxingされます。

配列がなぜあるかですが、まとめて値を処理したい場合に便利だからです。

    > a:int[] = [ 100, 200, 300 ];
    3 length array of Integer
    > for(i:int = 0; i&lt;3; i++) {
        a[i] = a[i] + 100;
    }
    > a[0];
    200
    > a[1];
    300
    > a[2];
    400

上の例ではまとめて配列一つ一つの要素に+100しています。

## クラス

クラスはメソッドとフィールドの集合です。メソッドは手続きのことでクラスに属する関数のことです。フィールドはクラスに属する変数のことです。

以下のように定義します。

    class Student
    {
        name: String
        age: int
    
        def initialize(name:String, age:int) { 
            self.name = name;
            self.age = age;
        }
    
        def getName(): String { 
            return self.name;
        }
    
        def getAge(): int {
            return self.age;
        }

        def show() {
            printf("name: %s\nage %s\n", array { self.name, self.age });
        }
    }

classの後にクラス名が来ます。クラスとは機能の集合で変数の型でもあります。プログラムの部品と考えることもできます。
クラスはフィールドとメソッドの集合です。上の例でいえばnameとageがフィールドです。データの入れ物と考えるとわかりやすいと思います。
このクラスの場合は学生のデータを表しています。nameに文字列型で名前をageに数値型で年齢を入れることができます。
メソッドはdefの後にメソッド名を書き、引数を()の中に書きます。メソッドとはプログラムのことで命令を順次書いていきます。
initializeメソッドは特別なメソッドでクラスのインスタンス（実態）を初期化するときに呼ばれます。
逆にfinalzieメソッドを定義するとインスタンスが破棄されるときに呼ばれます。
Stundentクラスのインスタンスは以下のように作ります。

    student_a:Student = new Student("Daisuke Minato", 39);
    student_b:Student = new Student("Yuka Minato", 38);

student_aはDaisuke Minatoという学生のデータを表し、student_bはYuka Minatoという学生のデータを表します。
この時def initializeで定義した初期化用のメソッドが呼ばれます。内容は"Daisuke Minato"と39などの引数を
インスタンスのフィールドに保存しています。selfというのはそのインスタンスをあらわします。
この場合、そのインスタンスのフィールドのnameとageに引数の内容を代入しています。
メソッドが返す値の型は:の後に書きます。戻り値がない場合は:がいりません。
作られたインスタンスに対してメソッドを呼ぶには

    student_a.show();
    student_b.show();

などとします。この場合はshowの中でデータをprintfで表示しているので学生のデータの内容が表示されます。
<br>
他の言語と違いフィールドやメソッドでselfを省略することはできません。また型は変数名の後ろにきます。
クラスフィールドやクラスメソッドを定義したい場合は戻り値の型の前にstaticをつけます。
戻り値の後にstaticをつけることはできないので注意してください。ちなみにprivate指定はありません。
printfのところでarrayを使っているのはClover2には可変長引数がないため
printfの第二引数にはArray&lt;Object&gt;を取るためです。とりあえず、そういうものだと思ってください。
前述のとおりStudentクラスの定義はStudent.clcなどとファイル名を付けて保存してください。そのStudentクラスを使うスクリプト本体は
Student.clなどとしてください。コンパイルは

    > cclover2 Student.clcl

とします。コンパイル後はStudent.oclclという学生のデータ用のクラスファイルが作られます。

実行は

    > clover2 Student.cl

です。

後からの追加ですが、student := new Student("Yuka Minato", 38);はstudent := Student("Yuka Minato", 38)とnewを省略することができます。

## クラスフィールドとクラスメソッド

クラスフィールドやクラスメソッドとはクラス固有のフィールドやメソッドのことです。
インスタンスを作ってもクラスメソッドやクラスフィールドは新たには作られません。以下のように使います。

clclファイル

    class ClassA {
        classField: static int;
        def classMethod(a:int): static {
            printf("ClassA.classMethod %d\n", array { a });
        }
    }

clファイル

    ClassA.classField = 1;
    printf("ClassA.classField %d\n", array { ClassA.classField });
    ClassA.classMethod(2);

実行結果は

    ClassA.classField 1
    ClassA.classMethod 2

となります。

フィールドの型前やメソッドの戻り値の型の前にstaticを指定するとクラスフィールドやクラスメソッドが作成されます。
クラスフィールドをクラス側で初期化したい場合はinitializeメソッドにstaticをつけてください。
クラスのロード時に呼ばれます。逆にクラスの削除時にはfinalizeメソッドが呼ばれます。

clclファイル

    class ClassB
    {
        classField: static int;
    
        def initialize():static {
            ClassB.classField = 123;
        }
        def finalize():static {
            println("ClassB is deleted");
        }
    }

clファイル

    printf("ClassB.classField %d\n", array { ClassB.classField });

出力は

    ClassB.classField 123
    ClassB is deleted

となります。

## dynamic_class

dynamic_classのオブジェクトにはどのようなメソッド名や引数のメソッドも呼び出すことができます。呼び出されたメソッドは実行時にcallingMethodというメソッドが呼ばれて、その中で具体的な処理を行うことができます。例えば

    dynamic_class MyDynamicClass
    {
        def initialize() {
        }
        def callingMethod(method_name:String, params:Array<Object>, num_method_chains:int, max_method_chains:int) {
            if(method_name.equals("hoge") {
                println("hoge");
            }
            elif(method_name.equals("hogehoge") {
                println("hogehoge");
            }
        }
        def callingMethod(method_name:String, params:Array<Object>, num_method_chains:int, max_method_chains:int):static {
            if(method_name.equals("hoge") {
                println("class method hoge");
            }
            elif(method_name.equals("hogehoge") {
                println("class method hogehoge");
            }
        }
    }

のように定義します。呼び出し側は

    > a:MyDynamicClass = new MyDynamicClass();
    > a.hoge();
    hoge
    > a.hogehoge();
    hogehoge
    > MyDnamicClass.hoge()
    class method hoge

などとします。paramsには引数のオブジェクトが配列で入ってます。Object型なので引数のオブジェクトのクラスに応じて処理を行いたい場合はclassName()メソッドを使って処理してください。num_method_chainsにはメソッドチェインで何番目かの情報がmax_method_chainsにはメソッドチェインの数がいくつ続いたかの情報が入ってます。ただ通常は使うことはないでしょう。

## boxingとunboxing

ユーザークラスは演算子の対象となるとunboxingされてプリミティブ型となります。逆にプリミティブ型はGenericsの引数に代入された場合やメソッドコールされた場合はboxingされて対応するユーザークラスとなります。対応するユーザークラスとプリミティブクラスは以下です。

    int → Integer
    uint → UInteger
    byte → Byte
    ubyte → UByte
    short → Short
    ushort → UShort
    long → Long
    ulong → ULong
    float → Float
    double → Double
    pointer → Pointer
    char → Char
    bool → Bool

となります。

Bufferクラスはpointerクラスにunboxingされます。つまり以下は動きます。

    str := strdup(b"ABC");
    strcmp(str, b"ABC") == 0
    free(str);

## ラッパークラスの数値の表現

    a:Integer = 5I;
    b:UInteger = 5UI;
    c:Byte = 5Y
    d:UByte = 5UY;
    e:Short = 5S;
    f:UShort = 5US;
    g:Long = 5L;
    h:ULong = 5UL;
    i:Float = 5.5F;
    j:Double = 5.5D;

## プリミティブ型とスペシャルフィールド

プリミティブ型にメソッドコールはありませんがスペシャルフィールドはあります。フィールドなのでメソッドコールのように()はいりません。例えば

    1.to_long
    1.1.to_int
    true.to_int

などと書きます。

プリミティブ型には以下のものがあります

    toString 文字列クラスにキャストする
    toByte Byteクラスにキャストする
    toUByte UByteクラスにキャストする
    toShort Shortクラスにキャストする
    toUShort UShortクラスにキャストする
    toInteger Integerクラスにキャストする
    toUInteger UIntegerクラスにキャストする
    toLong Longクラスにキャストする
    toULong ULongクラスにキャストする
    toFloat Floatクラスにキャストする
    toDouble Doubleクラスにキャストする
    toPointer Pointerクラスにキャストする
    toChar Charクラスにキャストする
    toBool Boolクラスにキャストする
    to_byte byte型にキャストする
    to_ubyte ubyte型にキャストする
    to_short short型にキャストする
    to_ushort ushort型にキャストする
    to_int int型にキャストする
    to_uint uint型にキャストする
    to_long long型にキャストする
    to_ulong ulong型にキャストする
    to_float float型にキャストする
    to_double double型にキャストする
    to_char char型にキャストする
    to_pointer pointer型にキャストする
    to_bool bool型にキャストする

charクラスには以下のものがあります

    to_upper アルファベットを小文字に変換します
    to_lower アルファベットを大文字に変換します

配列には以下のものがあります。

    length 配列の大きさを得る。
    toArray Arrayクラスにキャストされます。

正規表現クラスには以下のものがあります。

    global グローバルフラグがあるかboolで返します
    ignoreCase 検索時の大文字小文字を無視するフラグをboolで返します
    multiline 検索時のマルチラインフラグをboolで返します
    extended 拡張正規表現を使っているかboolで返します
    dotAll dotAllフラグをboolで返します
    anchored anchordフラグをboolで返します
    dollarEndOnly dollarEndOnlyフラグをboolで返します
    ungreedy ungreedyフラグをboolで返します。

## スペシャルメソッド

ユーザークラスには必ず持っているメソッドがあります。

    identifyWith(object:Object): bool

変数が保持しているオブジェクトが同じかどうか判定します。

    > a:Integer = new Integer(5);
    5
    > b:Integer = a;
    5
    > b.identifyWith(a)
    true
    > c := new Integer(6);
    6
    > b.identifyWith(c)
    false

nullを保持しているかどうかの判定にも使えます。

    > a:Integer = null;
Null pointer eception(3)
compile or runtime error
    > a.identifyWith(null)
    true

インタプリタではtoString().chomp().println()されているためエラーが出ています。あまり気にしないでください。

次にオブジェクトのクラス名を得るclassNameがあります。

    className():String

    > a := new Integer(5);
    5
    > a.className();
    Integer

Anonymous型に変換するtoAnonymous()があります。

    toAnonymous():Anonymous

    > a := new Integer(5);
    5
    > b:String = a.toAnonymous()
    field index is invalid
    compile or runtime error
    > c:Integer = a.toAnonymous()
    5

Anonymous型に変換するとどんな型の変数にも代入できます。型チェックを完全に無視することができます。
上の例ではaがInteger型でString型のbに代入していますがコンパイルエラーにならずにコンパイルは通ってます。
たまたまランタイム時にエラーが検出できてエラーとなっていますが、偶然です。
toAnonymous()はユーザーの責任でエラーがないかチェックしないといけません。

    toNull(): Null

nullに変換します。インタプリタで戻り値の表示を抑制したい場合に使ってください。

    ID(): int

オブジェクトの固有のIDを返します。デバッグ用で特にユーザーでは使うことはないでしょう。

    allocatedSize():size_t

オブジェクトの取得されたメモリーのサイズを返します。デバッグ用で特にユーザーでは使うことがないでしょう。主に拡張ライブラリでのデバッグに使われます。

    headOfMemory():pointer

オブジェクトの取得されたメモリーの先頭アドレスを返します。主に拡張ライブラリで使われます.

    is(class_name:String):bool

オブジェクトの型をチェックして引数のクラス名を持つクラスのオブジェクトなら真を返します。その後もし変数に対してisが行われていれば、その変数をclass_nameの型にします。

    a:Anonymous = "ABC";
    if(a.is("String") {
        # aはString型
    }
    elif(a.is("Integer") {
        # aはInteger型
    }

    # aはInteger型

## インターフェース

インターフェースとは実装しなければならないメソッドを定義して、そのメソッドがある複数のクラスを統一的に扱おうというものです。
具体的には

    interface IMyIntereface
    {
        def getValue(): int
        def show()
    }

のように定義します。インタフェース名には慣習的にIを最初につけることが多いです。このIMyInterfaceというインタフェースにはint型の値を得るgetValue()というメソッドとshow()という値を表示するためのメソッドを定義する必要があることを定義しています。
例えば

    class MyClasssA
    {
        def initialize() {
        }
        def getValue():int {
            return 123;
        }
        def show() {
            println("123");
        }
    }

    class MyClasssB
    {
        def initialize() {
        }
        def getValue():int {
            return 345;
        }
        def show() {
            println("345");
        }
    }

というクラスを定義すると

    a:IMyInterface = new MyClassA();

や

    b:IMyInterface = new MyClassB();

のようにIMyInterfaceという変数にgetValue()やshow()が定義されているためMyClassAやMyClassBが代入することができます。
代入したインターフェースには定義されているメソッドを呼び出すことができ、入っているMyClassAかMyClassBのメソッドを呼び出すことができます。

    > a.show();
    123
    > b.show();
    345

どのようなときに便利かというとメソッドの引数にインターフェースを使う場合などです。例えば

    class MyClassC
    {
        def initialize() {
        }
        def show(my_interface:IMyInterface) {
            my_interface.show();
        }
    }

などです。MyClassCのshowメソッドの引数にはClassAもClassBのオブジェクトも渡すことができます。

    > a:MyClassA = new MyClassA();
    > b:MyClassB = new MyClassB();
    > c:MyClassC = new MyClassC()
    > c.show(a);
    123
    > c.show(b);
    345

このように変数に代入されたオブジェクトによって呼ばれるメソッドが変わることをポリモフィズムといいます。IMyInterfaceのメソッドを実装していれば、どのようなクラスもMyClassCのshowに渡すことができ、便利なのです。

インターフェースの実装時、実装しているクラス自身を表したいときがあります。そのときはSelfというクラス名を使ってください。

    interface MyInterface2
    {
        def equals(right:Self):bool;
    }

このインターフェスは以下の様に実装します。

    class MyClassA
    {
        value:int;
        def initialize(value:int) {
            self.value = value;
        }
        def equals(right:MyClassA):bool {
            return self.value == right.value;
        }
    }

Selfの部分はその定義しているクラス自身のクラス名を使うとMyInterface2を実装したことになります。

## 移譲

移譲は継承のないClover2にとっては継承の代わりになる機能です。以下のように使います。

    class ClassB
    {
        def initialize() {}
        def show() {
            println("HELLO delegate");
        }
        def get():int {
            return 123;
        }
    }

    class ClassA
    {
        b:delegate ClassB;
        def initialize() { self.b = new ClassB() }
    }

    a := new ClassA();
    a.show();
    Clover.test("delegation test", a.get() == 123);

このような感じです。delegate指定をしたフィールドのクラスのメソッドはそのフィールドを含むクラスのメソッドとして定義されます。def getやdef showはClassAに定義されているのでdef getやdef showを含むインターフェースにも代入することができます。delegate指定のあるフィールドは複数持つことができます。もしメソッドが衝突したら後にdelegate指定したフィールドのメソッドが優先されます。もしメソッドが衝突した場合は自分で同名のメソッドを作り、好きなフィールドを呼ぶこともできます。Clover2は後から定義したメソッドが優先されるので。delegateをしたフィールドのメソッドの動きを変えたいときも同名のメソッドを後ろの方に定義すれば、そちらが優先されます。継承で言うoverwriteみたいなもんです。<br>
<br>
内部的にdelegate指定した場所で上の例で言うとClassAに以下のようなメソッドが定義されています。<br>

    def get() {
        return self.b.get();
    }
    def show() {
        self.b.show();
    }

単純な仕組みです。delegateによって実装も共有できますしインターフェースの要件も満たすようなクラスをフィールドの含むことによって継承と同じような働きが期待できます。移譲は継承より上の概念だと思います。ぜひ、使いこなしてください。

## モジュール

Clover2には継承がないのでクラス間で実装を共有したい場合モジュールを使います。モジュールは単なるテキストでclassの定義の中でincludeされると、そのテキストがコピーされて、実装されたメソッドやフィールドが使えるようになります。

    module MModuleA
    {
        field: int;
        def getFeild():int
            return self.field;
        }
    }

    class ClassA
    {
        include MModuleA
        def initialize(num:int) {
            self.field = num;
        }
    }

    class ClassB
    {
        include MModuleA
        def initialize(num:int) {
            self.field = num * 2;
        }
    }

MModuleAをincludeしているのでClassAやClassBではfieldフィールドやgetFieldメソッドが使えるようになります。
モジュールとインタフェースを組み合わせると継承したかのように２つ以上のクラスを同じものとして扱うことができます。この場合、例えば

    interface IInterfaceA
    {
        def getField():int
    }

というインターフェースを実装するとIInterfaceAという型を持つ変数を作った場合、その中にClassAやClassBを代入することができます。

    a:IInterfaceA[] = new IInterface[2];
    a[0] = new ClassA(123);
    a[1] = new ClassB(123);
    for(i:=0; i<2; i++) {
        a[i].getField().toString().println();
    }

このようにインタフェースとモジュールを組み合わせると継承したかのようにポリモフィズムが起こります。ポリモフィズムとはオブジェクト指向用語である違うクラスが代入された変数にあるメソッドを実行した場合代入されているオブジェクトに応じたメソッドが呼ばれる仕組みを言います。

もし、モジュールの中でincludeしたクラス自身のクラス名を使いたいときはSELFというクラス名を使います。

    module MEquals
    {
        def equals(right:SELF):bool {
            return self.value == right.value;
        }
    }

    class ClassA
    {
        value:int;
        def initialize(value:int) {
            self.value = value;
        }
        include MEquals
    }

    class ClassB
    {
        value:float;
        def initialize(value:float) {
            self.value = value;
        }
        include MEquals
    }

ClassAではdef equals(right:ClassA):boolが実装されてClassBではdef equals(right:ClassB):boolが実装されます。MEqualsモジュールのSELFの部分はClassAでincludeされたときはClassAにClassBでincludeされたときはClassBに変化するためです。
モジュールの中では型チェックなどは行われません。単にテキストが張り付けられてコンパイルされるだけです。その時エラーになることはあります。

## ジェネリクス

Clover2のGenericsは主にコレクションを実現するために用意されています。そのため他の言語のGenericsほど、高機能ではありません。定義は以下の様にします。

    class MyArray<T:ISortable>
    {
        items:T[];
        def initialize() {
            self.items = null;
        }
        def add(item:T) {
            # ....
        }
    }

クラス名の後に&lt;T:ISortable&gt;とつけていますが、Tがクラス引数です。ISortableは実装していないといけないインターフェースです。使う時は

    a:MyArray<Integer> = new MyArray<Integer>();

などとしてMyArrayにIntegerクラス引数を渡します。IntegerはISortableを実装しているのでコンパイルエラーになりません。クラス引数がISortableを実装していない場合はエラーとなります。TはISortableを実装しているためメソッドの定義の中ではTはISortableとして扱われ、ISortableが実装しているメソッドは呼び出すことができます。<br>

Javaと同じでnew T()はできません。Tはインターフェースなので、newできないためです。new T\[\]\(\)もできません。

## メソッドジェネリクス

    def <T:Object, R:AnInterface> method(a:T, b:R):List<T> {
    }

のように定義します。戻り値の型は引数の型によって変化します。

## 関数

    def fun(a:int, b: int):int { 123 }

のように宣言するとfunというローカル変数にlambda(int,int):intというブロックオブジェクトが代入されます。fun(1,2)のように呼び出すことが出来ます。スコープはローカル変数と同じです。単なるブロックオブジェクトなのでメソッドの引数として渡したり別の変数に代入したりできます。

## 列挙型

    > vim EnumTest.clclc
    class EnumTest {
        enum { Value1, Value2, Value3 }
        enum { BValue1, BValue2, BValue3 }
    }
    > vim enum_test.cl
    Clover.test("enum test", EnumTest.Value1 == 0 && EnumTest.Value2 == 1 && EnumTest.Value3 == 2 && EnumTest.BValue1 == 0 && EnumTest.BValue2 == 1 && EnumTest.BValue3 == 2);
    > clover2 enum_test.cl
    enum test...OK

になります。enum型の要素は初期化される単なるstatic intです。糖衣構文みたいなもんですね。

## 自動setterとgetterの定義

setterとgetterがフィールドを定義すると自動的に定義されるようになりました。(version 3.1.9より)

    > vim SetterAndGetter.clcl
    class SetterAndGetter {
        field1:int;
        field2: String;
        field3: private int;

        def initialize() {}
    }
    > vim setter_and_getter.cl
    a := new SetterAndGetter();
    a.field1(123);
    a.field2("ABC");
    Clover.test("setter and getter", a.field1() == 123 && b.field2().equals("ABC"));

    # a.field3()は定義されているがa.field3(123)は定義されていない。

デフォルトの定義が気に食わないときはそのようなメソッドを後から定義してください。Clover2は後から定義されたメソッドがメソッド検索時に優先されるので。

## when文

    a := 123;
    when(a) {
       case (1) {
           println("1");
       }
       case (2,3) {
           println("2,3");
       }
       case (123) {
           prinntln("123");
       }
       else {
           println("else");
       }
    }

    a := "ABC";
    when(a) {
       case ("ABC") {
           println("ABC");
       }
       case ("DEF","GHI") {
           println("DEF or GHI");
       }
       else {
           println("else");
       }
    }

ユーザークラスの場合IEqualableインターフェースが実装されている必要があります。equalsによって値を比較しているためです。

whenには戻り値もあります。

    > vim a.cl
    a:int = when("ABC") {
       case ("ABC") {
           1;
       }
       case ("DEF","GHI") {
           2;
       }
       else {
           3;
       }
    }
    Clover.test("when test", a == 1);
    > clover2 a.cl
    when test...OK

whenの戻り値の方が違う場合Anonymous型が返されます。castして使ってください。

    > vim a.cl
    a := when("ABC") {
       case ("ABC") {
           1;
       }
       case ("DEF","GHI") {
           "ABC
       }
       else {
           new Integer(123);
       }
    }
    Clover.test("when test", a.cast("int") == 1);
    > clover2 a.cl
    when test...OK

when文ではisや!isも使えます。

    > vim a.cl
    a := when("ABC") {
       is String {
           1;
       }
       else {
           new Integer(123);
       }
    }
    Clover.test("when test2", a.cast("int") == 1);
    > clover2 a.cl
    when test2...OK

    > vim a.cl
    a := when("ABC") {
       !is Integer {
           1;
       }
       else {
           new Integer(123);
       }
    }
    Clover.test("when test3", a.cast("int") == 1);
    > clover2 a.cl
    when test3...OK

wildcardは以下のように使います。wildcardはどんな値にもマッチします。

     > vim PaternMatching.clcl

     class PatternMatchingTest
     {
         value1: int;
         value2: String;

         def initialize(value1:int, value2:String) {
             self.value1 = value1;
             self.value2 = value2;
        }$

        def equals(right:PatternMatchingTest):bool {
            return self.value1 == right.value1 && self.value2.equals(right.value2);
        }
     }

     class PatternMatchingTest2
     {
          value1: Integer;
          value2: String;

          def initialize(value1:Integer, value2:String) {
              self.value1 = value1;
              self.value2 = value2;
          }$

          def equals(right:PatternMatchingTest2):bool {                                                            
              return self.value1.equals(right.value1) && self.value2.equals(right.value2);
          }$
     }$

     > vim a.cl
     a:Anonymous = "ABC";

     c:String = when(a) {
          is String {
               a;
          }
          else {
               "else";
          }
     }

     Clover.test("Pattern matching test", c.equals("ABC"));

     b:Anonymous = new Integer(123);

     d:String = when(b) {
         !is String {
             "111";
         }
         else {
             "else"
         }
     }

     Clover.test("Pattern maching test2", d.equals("111"));

     e:Anonymous = new PatternMatchingTest(111, "ABC");

     f:String = when(e) {
         case (new PatternMatchingTest(111, "ABC")) {
              "ABC";
         }
         else {
             "DEF";
         }
     }

     Clover.test("Pattern matching test3", f.equals("ABC"));

     g:Anonymous = new PatternMatchingTest(222, "DEF");

     f = when(g) {
         case (new PatternMatchingTest(111, "DEF")) {
             "ABC"
         }
         case (new PatternMatchingTest(222, wildcard)) {
             "DEF";
         }
         else {
             "GHI";
         }
      }

      Clover.test("Pattern matching test4", f.equals("DEF"));

      i:Anonymous = new PatternMatchingTest2(123, "ABC");

      j:String = when(i) {
           case (new PatternMatchingTest2(wildcard, wildcard)) {
                "ABC";
           }
           else {
                "DEF";
           }
       }

       Clover.test("Pattern matching test5", j.equals("ABC"));

ただし、wildcardはプリミティブ型には代入することができないので、wildcardを使いたい時はintクラスじゃなくてIntegerクラスなどを使ってください。
またcase文で値を比較したい場合はequalsを実装する必要があります。まあ、これは当然ですが。

パターンマッチングもあります。以下のように使います。

    e := new Array<String>();

    f := when(e.className()) {
        match (/.+<String>/) {
            123;
        }
        else {
            456;
        }
    }

    Clover.test("when test5", f == 123);

whenの値はStringでないといけません。またmatchの値は正規表現じゃないといけません。

## 変数の宣言の取り消し

    a := 123;

と宣言したなら

    unset a

で宣言が取り消せます。REPLでは便利に使えると思います。

## 多重代入

タプルは複数のローカル変数に代入することができます。

    > (a, b) := (1,2)

右辺値はタプルです。詳しくはコレクションの項を見てください。
aは1でbが2が入ってます。

変数の値の交換も可能です。

    > a := 1; b := 2;
    > (a, b) = (b, a)

aは2でbが1が入ります。
今のところちょっと手抜きでローカル変数しかこの多重代入はすることが出来ません。
クラスフィールドやフィールドへの代入は普通に行ってください。
また気が向いたら、そのあたり実装するかもしれません。

## 代入時の自動キャスト

intやshort, longの場合はラッパークラスも含めて相互に自動的にキャストが行われて代入やメソッドの引数になる時型が違っても大丈夫です。float, double, Float, Doubleは自動的にキャストされません。

## 例外処理

書くのを忘れてましたが、もちろん例外処理もあります。

try {
    throws new Exception("TEST");
}
catch(e:Exception) {
    println("catch EXCEPTION");
}

Javaのように例外は型付けされているわけじゃないです。e.messsageに入っているメッセージで起こった例外を判断してください。

## 複数行の文字列

以下のように使います。

    print(
        """
        HELLO WORLD
        HELLO WORLD
        HELLO WORLD
        """);

変数の展開は以下のように使います。

    name := "Tom";

    print(
        """
        HELLO \{name}
        HELLO \{name}
        HELLO \{name}
        """);

インデントにはタブは使えません。スペースのみとなっております。インデントは必要ない場合は普通の文字列を使ってください。普通の文字列でも改行を含めることができます。

    print("HELLO WORLD
    HELLO WORLD
    HELLOWORLD
    ");

## C言語へのFFI

使う場合はconfigureに--with-c-ffiオプションをつけてコンパイルしてください。

    ExtensionTest.c

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int getValue(int x, int y) 
    {
        return x + y;
    }

    long getValue2(long x, long y)
    {
        return x + y;
    }

    char* getStr(char* x, char* y) 
    {
        size_t len = strlen(x) + strlen(y) + 1;

        char* result = calloc(1, len);

        strcpy(result, x);
        strcat(result, y);

        return result;
    }

    ExtensionTest.h

    #define ABC 123

    ExtensionClassTest.clcl

    class ExtensionClassTest
    {
        ABC: static int from ExtensionTest.h

        def getValue(x:int, y:int): int from libExtensionTest.so;
        def getValue2(x:long, y:long): long from libExtensionTest.so;
        def getStr(x:pointer, y:pointer): pointer@alloc from libExtensionTest.so;

        def main():static {
            Clover.test("Extension Test1", getValue(1, 2) == 3);
            Clover.test("Extension Test2", getValue2(1l, 2l) == 3l);

            str := getStr(b"ABC", b"DEF");

            Clover.test("Extension Test3", strcmp(str, b"ABCDEF") == 0);

            free(str);

            Clover.test("Extension Test4", ABC == 123);
        }
    }

    CLibrary.clcl

    include "SystemCalls.clcl"

    class System
    {
        def strcmp(x:pointer, y:pointer): int from libc.so.6
    }

構造体はサポートしません。構造体を使うC言語の関数はnative methodから使ってください。

## ローカル変数の宣言

var a := 123;
a = 245;

val b := 123;
b = 234;   # error

後からの追加ですが、変数はvar 変数名=値。readonlyはval 変数名=値です。

## 糖衣構文

### lambdaクラスの糖衣構文

メソッドの引数となるlambdaオブジェクトを作る場合記述が煩雑になる場合があります。その為糖衣構文が用意されています。以下の様に書きます。

    3.times() { println("HO!"); };
    
    sum := 0; list { 1, 2, 3 }.each() {|n:Integer| sum + = n }
    
    str := ""; list { 1, 2, 3 }.map() {|n:Integer|:Anonymous return n.toString(); }.each() {|n:Anonymous| str.append(n.cast("String")); }

Ruby風の書き方となっております。最後の引数にブロックを取るメソッドはこのように記述できます。

この場合メソッドの()は省略することができます。

    list { 1,2,3 }.each {|n:Integer| println(n.toString()) }

### 文字列への式の埋め込み

    a:int = 123;
    b:String = "abc\{a.toString()}def";

のようにします。Path, Regex, Bufferへの式の埋め込みも同様です。

`toString()` は省略できます:

    a:int = 123;
    b:String = "abc\{a}def";

は上記と同等のコードです。

### return文の省略

メソッドのreturn文は省略することが出来ます。最後に実行された値がreturnされます。
lambdaのreutrn文も戻り値の型を明示した場合は省略することができます。

    def get():int { 123 }

getは123を返します。

    a:lambda():int = lambda() { 123 }

a()は123を返します。

### メソッドのデフォルト引数

    > vim ClassA.clcl
    class ClassA {
        def initialize() {}
        def method(a:int, b:int=2, c:int=3) {
            return a + b + c;
        }
    }
    > vim a.cl
    a := new ClassA();
    Clover.test("Method arg default value", a.method(1) == 6);
    > clover2 a.cl
    Method arg default value...OK

上記のようにメソッドの引数のデフォルト値が設定できます。

### 同一クラスのメソッドとフィールドのself省略

    > vim InternalMethodTest.clcl
    class InternalMethodTest {
        def initialize() {}
        def method():int {
            return method2();
            # return self.method2()と書いても良い
        }
        def method2():int {
            return 123 
        }
    }
    > vim a.cl
    a := new InternalMethod();
    Clover.test("internal method test", a.method() == 123);
    > clover2 a.cl
    internal method test...OK

上記のような感じです。

同一クラスのフィールドのself省略

    > vim InternalFieldTest.clcl
    class InternalFieldTest {
        field:int;
        def initialize(value:int) {
            field = value;
        }
        def get(): {
            return field;
        }
    }
    > vim a.cl
    a := new InternalFieldTest(123);
    Clover.test("internal field test", a.get() == 123);
    > clover2 a.cl
    internal field test...OK

上記のような感じです。ローカル変数とフィールドとの名前空間がバッティングしますが検索のアルゴリズムはローカル変数が優先されるので、曖昧な時はフィールドにselfを付けてください。このアルゴリズムで、selfは省略しても特に問題ないと判断しました。今までのコードとも互換性があります。

----

[<< 前 使い方](usage) [>> 次 型推論](typing)
