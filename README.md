# clover2 computer language

[![Build Status](https://travis-ci.org/ab25cq/clover2.svg?branch=master)](https://travis-ci.org/ab25cq/clover2)


version 3.5.2

サポートしている機能

    1. プリミティブクラスと普通クラスの2種類あり、プリミティブクラスはヒープを使いません。メソッド呼び出しも無く演算子のみサポートしていてプリミティブクラスの値への処理は高速です。しかしboxingやunboxingがありプリミティブクラスにメソッドコールを行ったときやコンテナライブラリに値を追加する場合などはboxingされてプリミティブクラスの使いずらさを軽減しています。逆に演算子の対象になった場合はunboxingされます。

    2. 関数型言語のようにLambdaやclosureは第一級オブジェクトです。正規表現も第一級オブジェクトです。

    3. 簡易なGenericsがあります。JavaのGenericsを簡素にしたようものです。コンパイル時のみGenerics情報があり、実行時には消えているので効率的です。

    4. 簡略化のために継承はありません。インターフェースとクラスとモジュールのみあります。そのためインターフェースに対するメソッド呼び出し以外はすべてコンパイル時にメソッドが特定でき効率的です。継承の代わりに使える機能として移譲を言語でサポートしています。

    5. オープンクラスです。組み込みのクラスを含む全てのクラスに後からメソッドやフィールドを追加することができます。同名のメソッドを定義することができ、mixin-layersスタイルのような差分プログラミングをすることができます。

    6.インタプリタもあります。外部コマンドも簡単に実行でき、clover2のメソッドとも簡単に混ぜることができます。

ls().grep("main.c").toString().scan(/./).join("+").toCommand().less()
m+a+i+n+.+c

    とless外部コマンドで表示される。 メソッド名や外部コマンド名、ファイル名の補完もされます。JavaのIDEやPowerShellと同じく文脈に沿った補完を行います。

    7.--with-jit指定を./configureにつけるとLLVMによるJITが有効になります。処理速度が向上します。大体3倍速くらいです。内部的にはClover2のソースファイルのコンパイル時にJITコンパイルしてダイナミックライブラリを作っているのでJITというよりネイティブコードコンパイラと言っても良いかもしれません。

    8. シェルのような記述もできREPLをシェルの代わりに使うことができます。補完もシェルと同等の機能があります。ジョブコントロールも行うためfgやjobsなども動きます。ただしシェルよりは機能は限定的です。

ls -al | less
egrep str src/*.c
make && make install && make test
./configure --prefix=$HOME --with-optimize --with-interpreter

    9.メソッドブロックの型推論が出来ます。以下のようなコードが動きます。

a:SortableList<String> = slist{1,2,3}.map { it.toString() }

サンプルコード

    "A,B,C".split(/,/) {it.append("X"); }
    { AX, BX, CX }

    slist{1,2,3}.map { it * 2 }.each { it.printf("[%d]\n"); }
    [2]
    [4]
    [6]

    list{1,2,3}.map { it.toString().toCommand() }.each { it.less() }

    list{uname(), hostname(), pwd()}.each { it.less() }

Yet another compiler and a Virtual Machine.

FEATURES

    1. primitive class and none primitive class with boxing and unboxing
    2. Lambda and closure, regex are first-class object
    3. Generics
    4. No inheritance, only interfaces and classes, modules
    5. open class
    6. REPL with completion like shell
    7. LLVM native code compiling 

See clover2 wiki on github (Japanese) https://github.com/ab25cq/clover2/wiki

LICENSE is GPL-2.0. see LICENSE file

Sample Code

    "A,B,C".split(/,/) {it.append("X"); }
    { AX, BX, CX }

    slist{1,2,3}.map { it * 2 }.each { it.printf("[%d]\n"); }
    [2]
    [4]
    [6]

    list{1,2,3}.map { it.toString().toCommand() }.each { it.less() }

    list{uname(), hostname(), pwd()}.each { it.less() }
