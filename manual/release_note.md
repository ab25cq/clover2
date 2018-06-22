English page is here [>> English page](release_note-en)

version 4.2.3

    いくつかのバグを修正しました。

version 4.2.2

    JITのランタイムをライブラリに追加しました。(libclover2.so)

    Compile 時のリフレクションでJITを有効にしました。

version 4.2.1

    JITで||と&&にバグが有ったため修正

    JITでb:=123; -b == 0が真になるバグを修正。OP_REVERSEのバグを修正。

version 4.2.0

    GCのアルゴリズムの修正。GC中のファイナライザで更にメモリが必要になったらセグメンテーション違反していましたが、修正。

    LLVMがちゃんと対応できてませんでしたが、修正。LLVM3.8とLLVM4.0 laterに対応。

version 4.1.8
    
    クラスのソースファイルのincludeファイルの検索パスのルーチンを作りました。カレントディレクトリだけでなく$PREFIX/share/clover2や~/.clover2にあるファイルも検索されます。cclover2 -core a.clclなどでinclude "MyOwnLibrary.clcl"などすれば基礎ライブラリの改造が出来ます。

    クラスファイルとモジュールとインクルードファイルのファイルの検索ルーチンのバグを修正しました。カレントディレクトリのクラスファイルが優先されます。またスクリプトファイルがある位置のディレクトリも検索ルーチンに加わっています。

    例外の仕様を変えました。メソッド呼び出し時のみだけでなく、スクリプト最上位で例外が起こってもcatchできます。
    例外のメッセージの出力をClover.onExceptionで行うようにしました。CGIや端末制御しているときは出力先を変えてください。Clover.onException(String,bool):staticをオーバーライドすればそう出来ます。

    -xなどのパースが通らないバグを修正

    /を含む文字列が演算子だと思われずにコマンドだと思われるバグを修正

    クラスの自動コンパイルを廃止しています。

version 4.1.7
    
    Clover.onExceptionフックを作りました。例外が起こったときに実行されます。

version 4.1.6
    
    ラムダの配列でラムダのオブジェクトがマークされない問題を修正。

version 4.1.5
    
    ラムダの配列に対するラムダの実行ができなったので、できるようにしました。

    cloneメソッドのバグを修正。

version 4.1.4

    PathクラスはStringクラスにメソッドを委譲するようになりました。

    Added curses library

version 4.1.3

    Cloneメソッドのバグを修正。

version 4.1.2

    Cloneメソッドのバグを修正。

    クラスフィールドやフィールドの++, --などが動いていなかったため修正。

version 4.1.1

    Cloneメソッドのバグを修正。

    string expressionに、その箇所のあとのスペースが削除されるバグを修正しました。

    free_objectにバグが有ったため修正。

version 4.1.0

    IEqualableとISortableとIHashKeyにcloneメソッドが追加されました。cloneはコンパイル時のリフレクションで自動的に実装されるようになりました。詳しくはReflection.clclを見てください。

version 4.0.9

    拡張ライブラリのオブジェクトのメモリの管理形式を変えました。

version 4.0.8

    Systemにいくつかのメソッドを追加。

    libbsd-devもしくはlibbsd-develのライブラリが必要になりました。(オプション。あるとSystem.getbsizeが有効になる)

    REPLの補完でSystemクラスのクラスフィールドの補完も有効になりました。

    Socketのライブラリをつくりました。詳しくはSocket.clclを見てください。

    signalシステムコールの移植。

    ioctlシステムコールの移植。

    selectシステムコールの移植。

    mutex のバグを直した。

version 4.0.7

    String.removeTagでセキュリティホールが見つかりました。修正。

version 4.0.6

    正規表現で/を使う文字を使っていると正規表現の終端だと処理してしまうバグが有りました。\/で回避できるようにしました。
    
    String.removeTag()の追加

version 4.0.5

    SystemクラスのクラスフィールドはSystem.という表記を省略できるようになりました。つまりaccess(fname, R_OK) == 0などはコンパイルが通ります。

    String.decodeFromForm()をいれました。CGIで便利です

    識別子の処理をリファクタリング。バグがあったと思います。修正。

    同じクラスのクラスメソッドとクラスフィールドの呼び出し時にクラス名を省略できるようになりました。

version 4.0.4

    Multi line stringのインデントのバグを修正。

version 4.0.3

    Regexのバグを修正。

    String Expression(\{})の中は式じゃなくてブロックになりました。

version 4.0.2

    CSVファイルの入出力をサポート。ファイルのロック用のメソッドの用意。

    コンパイラーにバグがありました。修正。

    JITのバグを修正

version 4.0.1

    CGIのためのライブラリを作り始めています。System.setlocaleの追加。System.setenvの第３引数を省略できるようにしました。

    コンパイラーにバグがありました。修正。

version 4.0.0

    スレッドを追加しました。詳しくはThreadクラスの解説を読んでください。

    def allocSize(): size_t でヒープから取得するメモリのサイズを指定できるようになりました。主に拡張ライブラリで使います。

    allocSize()スペシャルメソッドを追加しました。オブジェクトのヒープから取得したメモリのサイズを返します。主に拡張ライブラリ使うもので特にユーザーは使うことがないでしょう。

    headOfmemory()スペシャルメソッドを追加しました。オブジェクトのヒープから取得したメモリの先頭サイズを返します。主に拡張ライブラリで使うもので特にユーザーは使うことがないでしょう。

    クラスファイルの仕様が変更されてます。コンパイルされたクラスファイルは再度コンパイルが必要になってます。再コンパイルをお願いします。

    UShortのboxingのbugをfix

version 3.7.6

    Multi line stringを入れました。

    CloverクラスにgetMethod(name:String), getClassField(name:String), getField(name:String)を入れました。またClassクラスにnumFields, numMethods, numClassFieldsをフィールドを追加。

    CloverクラスにisLoaded(name:String), isDefined(name:String)クラスを追加。

    CloverクラスにappendClassを入れました。

    オブジェクトの作成時newを省略できるようになりました。

version 3.7.5

    コンパイル時スクリプティング機能が入りました。リフレクション機能が入りました。

version 3.7.4

    getppid, setsid, getsid, setpgrp, setpigdをSystemクラスに追加しました。

    REPLで配列に対するメソッドコールの補完にバグが有りました。修正。

version 3.7.3

    hashの値の表現に簡易表現を追加しました。a:Hash<String,Integer> = [ "AAA":2, "BBB":3 ]はコンパイルが通ります。

version 3.7.2

    変数への数値の代入時にint --> floatなどdoubleやfloatの場合は自動変換しなくなりました。
    (int --> long)などは暗黙のキャストが行われます

version 3.7.1

    ローカル変数の多重代入を入れました。

    > (a, b) := (1,2)
    > (a, b) = (b, a)

    タプルの表記で簡単なものを追加しました。

    (1,"AAA", 1.1)  # == Tuple<Integer, String, Double>

version 3.7.0

    コマンドライン引数のバグを修正。

    System.getopt, System.getopt_long, System.getopt_long_onlyを追加。

    -clean, --version, -versionオプションの廃止（-> 同名のコマンドライン引数が取れなくなるため)

version 3.6.9
    
    whenにパターンマッチングが入りました。以下のように使います。

    e := new Array<String>();

    f := when(e.className()) {
        match /.+<String>/: {
            123;
        }
        else {
            456;
        }
    }

    Clover.test("when test5", f == 123);

version 3.6.8

    メモリリークといくつかのバグを修正しました。

version 3.6.7

    コマンドのサスペンドがversion 3.6.3でバグになっていました。修正。

version 3.6.6

    cd コマンドを実行した時に環境変数PWDを設定するようになりました。

    System.setenvの戻り値をBufferからStringに変更しました

version 3.6.5

    REPLの補完のバグを修正。

version 3.6.4

    プリミティブ型じゃない配列に対するメソッドコールのバグを修正。

    REPLの補完のバグを修正。

    Clover.ARGV, ARGC, VERSIONを追加。

version 3.6.3

    System.mbstowcs, System.wcstombsのAPIの変更。詳しくはString.clclを見てください。

    System.tcgetatter, System.cfmakerawのAPIの変更。詳しくはCommand.clclを見てください。

    REPLの補完のバグを修正。

version 3.6.2

    Systemクラスのクラス名を省略できるようになりました。

    各種システムコールの追加

version 3.6.1
    
    ポインタの演算子の右辺値はulongじゃなくても大丈夫になりました。a := 1; b := &a; b += 4は動きます。

version 3.6.0

    ファイルクラスにnew File("fname.txt", "w");などを入れました。内部的にはfopenやfwrite, freadされてバッファリングされます。

version 3.5.9

    メソッドの引数で数値型の変換は暗黙で行われるようになりました。int --> ulongなど。

version 3.5.8

    configureの他のCPUへの対応やディレクトリ内のファイルの整理をしました。

version 3.5.7

unset 変数名という命令を加えました。変数の宣言を取り消します。

PowerPCに対応しました。

Version 3.5.6

Debianのパッケージを作るスクリプトを用意しました。. make_deb.shでパッケージが作られます。. install_deb.shでインストールされます。
基礎ライブラリのロードにバグがありました。修正。

version 3.5.6

OSのパッケージ化のために基礎ライブラリのインストール先を${PREFIX}/share/clover2か${DESTDIR}/share/clover2に移動しました。

自動コンパイル機能をシンプルにしました。ソースファイルを変更時は自動的にコンパイルはしません。

make DESTDIR=$HOME installなどとすると$HOME/bin, $HOME/share/clover2にソフトウェアのファイルを移動するようになりました。

version 3.5.5

英語ドキュメントをrepositoryに追加。

version 3.5.3

ドキュメントをrepositoryに追加。

versioin 3.5.2

メソッドブロック関連でバグがありました。修正。

versioin 3.5.1

ネイティブコードコンパイラにまだバグがありました。あとメソッドブロック関連でバグが頻出してまいした。かなり不安定だった様子です。修正しました。すみません。

version 3.5.0

ネイティブコードコンパイラのバグが無くなりました。ようやく完成です。心置きなく./configure --with-jitで使ってみてください。

version 3.3.1

メソッドの引数でboxingやunboxingが起こるようになりました。
Rangeクラスを作っています。StringクラスやBufferクラス、Listクラスなどで範囲を示す引数のメソッドを追加。
同一クラス内のフィールドがコマンド名より優先されない問題を修正。

version 3.3.0

JITでバグが見つかりました。修正。JITでテストコードを全てネイティブで動かしました。JITは安定したと思います。

version 3.2.9

例外の起こったメソッドのソースコードと行番号が分かりやすくなりました。

version 3.2.9

クラスフィールドやクラスメソッドの検索ルーチンにバグが有りました。かなり致命的なバグでした。ダウンロードお願いします。

version 3.2.9

クラスファイルの検索ルーチンにバグがありました。かなり致命的なバグでした。ダウンロードお願いします。

version 3.2.9

オブジェクトに型情報が入りました。new Array<String>().className().equals("Array<String>")は真です。

version 3.2.8

数値のラッパークラスのオブジェクト表現を入れました。

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

version 3.2.7

whenの仕様が変わってます。
whenにwildcardを入れました。

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
             "else"$
         }
     }

     Clover.test("Pattern maching test2", d.equals("111"));

     e:Anonymous = new PatternMatchingTest(111, "ABC");

     f:String = when(e) {
         case new PatternMatchingTest(111, "ABC"): {
              "ABC";
         }
         else {
             "DEF";
         }
     }

     Clover.test("Pattern matching test3", f.equals("ABC"));

     g:Anonymous = new PatternMatchingTest(222, "DEF");

     f = when(g) {
         case new PatternMatchingTest(111, "DEF"): {
             "ABC"
         }
         case new PatternMatchingTest(222, wildcard): {
             "DEF";
         }
         else {
             "GHI";
         }
      }

      Clover.test("Pattern matching test4", f.equals("DEF"));

      i:Anonymous = new PatternMatchingTest2(123, "ABC");

      j:String = when(i) {
           case new PatternMatchingTest2(wildcard, wildcard): {
                "ABC";
           }
           else {
                "DEF";
           }
       }

       Clover.test("Pattern matching test5", j.equals("ABC"));

ただし、wildcardはプリミティブ型には代入することができないので、wildcardを使いたい時はintクラスじゃなくてIntegerクラスなどを使ってください。

version 3.2.6a
whenにisと!isを入れました。

version 3.2.6

if文のバグを修正しました。

version 3.2.5

例外が起こったときに起こったソースコード名とソースコード番号のスタックトレースが表示されるようになりました。

version 3.2.4

例外が起こったときに起こった場所が出力されるようになりました。

version 3.2.3b
whenには戻り値もあります。

     > vim a.cl
     a:int = when("ABC") {
        "ABC" {
            1;
        }
        "DEF","GHI" {
            2;
        }
        else {
            3;
        }
    }
    Clover.test("when test", a == 1);
    > clover2 a.cl
    when test...OK

version 3.2.3 リリース 2017/12/4

when式が入りました。

    a := 123;
    when(a) {
       1 {
           println("1");
       }
       2,3 {
           println("2,3");
       }
       123 {
           prinntln("123");
       }
       else {
           println("else");
       }
    }

    a := "ABC";
    when(a) {
       "ABC" {
           println("ABC");
       }
       "DEF","GHI" {
           println("DEF or GHI");
       }
       else {
           println("else");
       }
    }

ユーザークラスの場合IEqualableインターフェースが実装されている必要があります。equalsによって値を比較しているためです。

version 3.2.2b リリース 2017/12/1

'{'や"...{..."などがあると正しくコンパイルできないバグを修正。なんで、こんなバグが残っていたんだろうroz

version 3.2.2a リリース 2017/12/1

フィールドのselfの省略にバグが有りました。修正。

version 3.2.2 リリース　2017/12/1

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

version 3.2.1 リリース　2017/12/1

同一クラスのメソッドのself省略

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

上記のような感じです。フィールドの方はselfは省略できません。エディッタでのフィールド名の置き換えで便利なので。あとはローカル変数とフィールド名がバッティングするのは良くないと思うためです。

version 3.2.0 リリース 2017/11/29

関数の再帰表現に対応しました。スクリプト内のdefで関数を定義した場合再帰が出来ませんでしたが対応しています。
(クラスのメソッドの再帰表現はもともとできる)

version 3.1.9 リリース 2017/11/28

setterとgetterがフィールドを定義すると自動的に定義されるようになりました。

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

version 3.1.8b リリース 2017/11/26

make uninstall && ./configure && make && make test && make installのコンパイル順に対応しました。

version 3.1.8 リリース 2017/11/24

列挙型

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

version 3.1.7 リリース 2017/11/24

メソッドのデフォルト引数を入れました。下記のように使います。

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

version 3.1.6 リリース 2017/11/21

isメソッドがAnonymousメソッド以外にも呼べるようになりました。List&lt;Object&gt;などで便利だと思います。

    > a := new List<Object>();
    > a.add(1);
    > a.add("ABC");
    > a.each {
    >    if(it.is("String")) {
    >        it.printf("[%s]"); # itはString型
    >    }
    >    elif(it.is("Integer")) {
    >        it.printf("[%d]"); # itはInteger型
    >    }
    > }

みたいな感じです。その時気づいたのですが、List&lt;Object&gt;に1をaddする時boxingもされずにObject型に代入できてしまうためセグメンテーション違反が出てました。ちゃんとインタフェースにはプリミティブ型は代入できないようにチェックするようにしました。またインターフェースへのプリミティブ型の代入はboxingされるようにしました。上のコードはversion 3.1.6ではちゃんと動きます。

version 3.1.5b リリース 2017/11/21

Anonymousクラスのisメソッドの仕様が変更されてます。if文のあとではAnonymousクラスに戻ってましたが、最後にisをしたクラスのままになるようになりました。ちょっとif文だけ特別なのもどうかと思いまして。

    a:Anonymous = "ABC";

    if(a.is("Integer")) {
        #aはInteger
    }
    elif(a.is("String")) {
        #aはString
    }

    #aはString

version 3.1.5a リリース 2017/11/20

自動コンパイル時のソースファイルの検索のアルゴリズムを改良しました。（特に普通は影響がない変更)

version 3.1.5 リリース 2017/11/20

クラスの循環参照の問題を解決しました。

    > vim ClassA.clcl
    class ClassA {
        field1: static int;

        def hello(): static {
            ClassB.hello();
        }
    }
    > vim ClassB.clcl
    class ClassB {
        def hello(): static {
            println("ClassA.field1 \{ClassA.field1}\n");
        }
    }

このようなコードの場合ClassA.clcl, ClassB.clcl両方のコンパイルが通りませんが以下の様にすれば大丈夫です。

    > vim ClassA.clcl
    include "ClassB.clcl"

    class ClassA {
        field1: static int;

        def hello(): static {
            ClassB.hello();
        }
    }
    > vim ClassB.clcl
    include "ClassA.clcl"

    class ClassB {
        def hello(): static {
            println("ClassA.field1 \{ClassA.field1}\n");
        }
    }

循環参照しているソース両方でincludeしてください。どちらかのソースをコンパイルするとコンパイルが通ります。

version 3.1.4 リリース 2017/11/18

クラスの自動コンパイル機能を入れました。クラス名をファイル名に持つクラスは自動的にコンパイルされます。
例えば

    > vim Hello.clcl
    class Hello {
        def hello() {
           println("HELLO WORLD");
        }
    }
    > vim hello.cl
    Hello.hello();
    > clover2 hello.cl
    HELLO WORLD

のような感じです。クラス名はファイル名と同じにしておくほうが自動的コンパイルされるので便利かもしません。
あとコメントを日本語で書き始めました。そのほうがしっくりきました。Clover2は日本人向けに作っていきたいと思います。

version 3.1.2a リリース 2017/11/18

シェルモードでfg, jobs, cdを使えるようにしました。ちょっと使えなくなってました。

version 3.1.2 リリース 2017/11/18

Darwinでコンパイルとテストしました。一応動いている様子です。深くはチェックしません。その時クラスフィールドやクラスメソッドを呼び出すとき小文字で始まるクラスはクラスフィールドやクラスメソッドは呼べなくしました。ちょっと色々ありまして。OSXはファイル名で大文字と小文字を区別しないので、list.headなどがListというクラスのフィールドだと勘違いしてしまうバグと出くわしたので。まあ、普通クラス名は大文字から始まると思うので、このような変更を加えました。一応小文字から始まるクラスは定義はできます。小文字から始めるクラス名のクラスのクラスフィールドとクラスメソッドが呼び出せないだけです。

SystemクラスのnativeメソッドでNull pointerのチェックが甘くセグメンテーション違反してましたが、全部チェックするようになりました。と言ってもNull Pointer Exceptionが起こるようになっただけですけどね。ユーザーには何が起こったのか分かるだけでもまだマシですね。ああ、そうだ。他のnative methodのNull pointer Exceptionのチェックしてませんね、、、今からします。

version 3.1.1 リリース 2017/11/14

ナルエイブルを入れました。

    a:String = null;   # コンパイルエラー

    b:String? = null;   # nullは代入できる。bは空だということでnullを代入している。
                        # ただし、bはnullが入っているかどうか注意してコーディングしないといけない

version 3.1.0 リリース 2017/11/14

スクリプトの自動コンパイル機能を入れました。clファイルはコンパイルせずに直接clover2で実行できます。

    > vim HelloWorld.cl
    println("HELLO WORLD");
    > clover2 HelloWorld.cl
    HELLO WORLD

拡張子の変更。
<br>
    普通のソースファイル cl --> cl<br>
    クラスのソースファイル clc --> clcl<br>
    普通のソースファイルのコンパイル結果 clo --> ocl<br>
    クラスファイル clcl --> oclcl<br>
<br>
大きな変更です。すみません。お手数ですが手元のソースファイルの拡張子も変更してください。拡張子を変えたのは出力ファイルをrm \*.o\*などと一括で消せるようにするためです。そのような要望があったので。

version 3.0.7 リリース 2017/11/14

Anonymousクラスにisメソッドを作りました。以下のように使います。

    a:Anonymous = "ABC";

    if(a.is("Integer")) {
        #aはInteger
    }
    elif(a.is("String")) {
        #aはString
    }

    #aはanonymous

version 3.0.6a リリース 2017/11/13

端末制御するコマンドを端末制御させたくない場合は--no-controlling-terminalという引数を付けると端末制御しなくなりました。例えばlsは端末制御するのですが、以下のようにすると端末制御しません。

list{ls("--no-controlling-terminal"),hostname(),pwd()}.each { it.less() }

version 3.0.6 リリース 2017/11/12

メソッドブロック関連のメモリのバグを修正しています。稀にセグメンテーション違反が起きる致命的なバグなのでダウンロードをお願います。
JITでメソッドのreturn文の省略が可能になりました。
これで知っているバグは全部修正できました。3.0.6を安定版とします。

version 3.0.5d リリース 2017/11/11

REPLの補完のバグを修正しました。メソッドブロックの型推論も含めて確認できる限りではほとんど期待どおり動きます。

version 3.0.5c リリース 2017/11/10

メソッドブロックの戻り値を省略した場合、returnを使うと型チェックが正しく行われてませんでした。修正。
具体的には

> a:SortableList&lt;String&gt; = slist{1,2,3}.map { return it.toString(); }<br>

で型チェックがおかしくなってました。

version 3.0.5b リリース 2017/11/09

if文にバグが有りました。修正しています。elseがある場合の戻り値でバグが有りました。簡単なコードでは分かりませんが、ループ回数が3000回とかになるforの中にif文があると問題になっていたはずです。結構致命的なバグなので、できればダウンロードお願いします。

version 3.0.5a リリース 2017/11/08

メソッドブロックの型推論に不備がありました。slist{1,2,3}.map { it * 3 }が動きませんでした。修正。

version 3.0.5 リリース 2017/11/07

シェルモードが悪さをしてslist{1,2,3}.select { it > 1 }などが動きませんでしたが修正しました。
コンパイラでコマンド名をPATHからサーチしてからシェルモードに入るようにしています。

version 3.0.4a リリース

1. slist{1,2,3}.each { "ABC"[TAB]で補完がIntegerになってましたが、修正しています。
