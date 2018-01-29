# 使い方

English page is here [>> English page](usage-en)

## HELLO WORLD

    > vim HelloWorld.cl
    println("HELLO WORLD");
    > clover2 HelloWorld.cl
    HELLO WORLD

クラスバージョンでは

    > vim HelloWorld.clcl
    class HelloWorld 
    {
        def fun():static {
            println("HELLO WORLD");
        }
    }
    > vim HelloWorld.cl
    HelloWorld.fun();
    > clover2 HelloWorld.cl

です。HelloWorld.clclはコンパイルしなくてもクラス名とファイル名が同じなので自動的にコンパイルされます。

## ソースコード

clover2のソースコードには2種類あります。一つがクラスを定義したソースファイルで拡張子はclclとしてください。

    > vim HelloWorld.clcl
    class HelloWorld {
        def printHelloWorld(): static {
            println("HELLO WORLD");
        }
    }
    > cclover2 HelloWorld.clcl

    > vim HelloWorld.cl
    HelloWorld.printHelloWorld();
    > clover2 HelloWorld.cl
    HELLO WORLD

のようになります。`cclover2 HelloWorld.clcl`はHelloWorld.oclclというクラスファイルを作ります。
`clover2 HelloWorld.cl`はHelloWorld.oclという仮想マシン用の実行形式のファイルを作り、そのまま実行します。
2種類あるので、めんどくさいと思われるかもしれませんが、複雑なアプリケーションを作る場合はclclファイルを編集してクラスを作り
簡単なスクリプトを作りたいときはclファイルだけ編集することを想定してます。
なので、この例でいえば単にHELLO WORLDしたいだけなので

    > vim HelloWorld.cl
    println("HELLO WORLD");

    > clover2 HelloWorld.cl
    HELLO WORLD

で大丈夫です。

## オープンクラスとincludeとmixin-layersスタイルコーディング

Clover2はオープンクラスなのでクラスの定義後フィールドやメソッドを追加することができます。やり方は単に元のクラスが定義されたソースファイルをincludeして、クラスを定義するだけです。

    > vim("a.clcl");
    class ClassA
    {
        field1:int;
        def initialize(value1:int) {
            self.field1 = value1;
        }
        def setField1(value:int) {
            self.field1 = value;
        }
    }
    > vim("b.clcl");
    include "a.clcl"
    class ClassA
    {
        field2:String;
        def initialize(value1:int, value2:String) {
            self.field1 = value1;
            self.field2 = value2;
        }
        def setField2(value:String) {
            self.field2 = value;
        }
    }

これでClassAにはフィールドがfield1とfield2がありメソッドはsetField1とsetField2があるようになります。コンパイルはこの場合はb.clclだけで大丈夫です。同名のメソッドがある場合後ろに定義されたメソッドが優先されます。その時、inherit(...)でひとつ前の定義のメソッドを呼び出すことができます。うまく使うとmixin-layersというレイヤーを重ねるようにコーディングするスタイルでプログラムが書けます。

    > vim("c.clcl")
    class ClassB
    {
        field1:int;
        def initialize(value1:int) { 
            self.field1 = value1;
        }
        def show() {
            self.field1.toString().println();
        }
    }
    > vim("d.clcl")
    include "c.clcl"
    class ClassB
    {
        field2:String;
        def initialize(value1:int, value2:String) {
            self.field1 = value1;
            self.field2 = value2;
        }
        def show() {
            inherit();
            self.field2.println();
        }
    }

d.clclでフィールドが追加されてメソッドが上書きされています。上書きされたshowはメソッドコールのメソッド検索時にd.clclのものが優先されます。showの中でinherit();が呼ばれているため、元のc.clclのshow()が呼び出されてフィールドは両方のものが表示されます。上書されるメソッドに引数がある場合はinheritに引数をつけてください。<br>

組み込みクラスのStringやHashなどにメソッドやフィールドを追加したい場合はClover2のソースファイルに含まれる。MyOwnLibrary.clclをincludeしてください。このMyOwnLibrary.clclにはFundamental.clcl→String.clc→Container.clcl→File.clcl→Command.clcl→MyOwnLibrary.clclの順でレイヤーが重ねられているため、これらのソースファイルも必要です。
一つ注意点はこの場合コンパイル時に-coreというオプションが必要になることです。
例えば、StringやHashを機能拡張したソースファイルの名前がMyOwnLibrary2.clclだとすると

````
> cclover2 -core MyOwnLibrary2.clcl
````

とコンパイルします。作られたオリジナルのString.oclclなりArray.oclclは$HOME/.clover2にコピーしてください。カレントディレクトリに関係なく、そのStringやArrayを使えるようになります。

Clover2のオープンクラスは単にincudeしたファイルに含まれるクラスももう一度コンパイルすることによって実現されています。なので、メソッドやフィールドを追加することで特に遅くなったりなどの影響は全くありません。inheritもメソッドがコンパイル時には呼び出すメソッドが確定されているので、ただのメソッドコールと同じ実行コストです。安心してmixin-layersスタイルのコーディングを楽しんでください。同名で同引数のメソッドが追加できる秘密は単にそれを許していて、コンパイル時のメソッド検索時にメソッドの配列の末尾から検索をしているので上書きできるだけです。コストは全くかかりません。凄く単純な仕組みで実現しています。

## クラスファイルの登録

クラスファイルの検索パスはカレントディレクトリと$HOME/.clover2となります。どのディレクトリからでもクラスを参照したい場合はoclclファイルを$HOME/.clover2にコピーしてください。あとJITを有効にしている場合はダイナミックライブラリのコピーも必要になります。lib[クラス名].so, lib[クラス名].so.1.0.0を$HOME/.clover2にコピーしてください。無くても動いてしまいますがJITが有効にならずに動いてしまいます。あとはダイナミックライブラリの検索のためにexport LD_LIBRARY_PATH=~/.clover2:$LIBRARY_PATHを.bashrcなどに登録してください。

## クラスの自動コンパイル機能

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

clover2コマンドにソースファイル名を指定すると、自動的にコンパイルしてから実行されます。
依存しているクラスも依存解析を再帰的に行うので、すべて自動的にコンパイルされます。
clover2ではファイル名とクラス名は別でも動作しますが、クラス名とファイル名を同じにしておくと便利でしょう。
ただし、version 3.5.3でも、まだ不安定で、念のためにMakefileなどにはcclover2 hello.clclと書いておいた方がいいかもしれません。エディッタでファイルを修正してもコンパイルされないことがあるためです。この辺り、また修正していきます。すみません。

## クラスの循環参照

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

----

[<< 前 Home](Home) [>> 次 主な機能](feature)
