English page is here [>> English page](Home-en)

# Clover2 仕様書

# はじめに

Clover2を使い始めようとするあなたへ。この言語はJavaやC#と同じようにコンパイラと仮想マシンによって構成されます。
コンパイルをするためコンパイル時に型チェックを行うことができます。
そのうえでRubyのような使いやすいライブラリを使うことができるように設計されています。
正規表現やlambda、closureなどは第一級クラスオブジェクトです。リテラルでも使うことができ、メソッドの引数としても渡せます。
プリミティブな配列もありますが、ListやHashもリテラルで使うことができます。
まあ、簡単に言うとRubyみたいな使い勝手を持ったJavaのような感じです。
まだまだライブラリは整備されてませんが、サーバーの管理に気軽に使ってもらえると嬉しいです。

# サポートしている機能

1. プリミティブクラスと普通クラスの2種類あり、プリミティブクラスはヒープを使いません。メソッド呼び出しも無く演算子のみサポートしていてプリミティブクラスの値への処理は高速です。しかしboxingやunboxingがありプリミティブクラスにメソッドコールを行ったときやコンテナライブラリに値を追加する場合などはboxingされてプリミティブクラスの使いずらさを軽減しています。逆に演算子の対象になった場合はunboxingされます。
2. 関数型言語のようにLambdaやclosureは第一級オブジェクトです。正規表現も第一級オブジェクトです。
3. 簡易なGenericsがあります。JavaのGenericsを簡素にしたようものです。コンパイル時のみGenerics情報があり、実行時には消えているので効率的です。
4. 簡略化のために継承はありません。インターフェースとクラスとモジュールのみあります。そのためインターフェースに対するメソッド呼び出し以外はすべてコンパイル時にメソッドが特定でき効率的です。継承の代わりに使える機能として移譲を言語でサポートしています。
5. オープンクラスです。組み込みのクラスを含む全てのクラスに後からメソッドやフィールドを追加することができます。同名のメソッドを定義することができ、mixin-layersスタイルのような差分プログラミングをすることができます。
6. インタプリタもあります。外部コマンドも簡単に実行でき、clover2のメソッドとも簡単に混ぜることができます。

```
> ls().grep("main.c").toString().scan(/./).join("+").toCommand().less()
> m+a+i+n+.+c

```

とless外部コマンドで表示される。
メソッド名や外部コマンド名、ファイル名の補完もされます。JavaのIDEやPowerShellと同じく文脈に沿った補完を行います。

7. --with-jit指定を./configureにつけるとLLVMによるJITが有効になります。処理速度が向上します。大体3倍速くらいです。内部的にはClover2のソースファイルのコンパイル時にJITコンパイルしてダイナミックライブラリを作っているのでJITというよりネイティブコードコンパイラと言っても良いかもしれません。

8. シェルのような記述もできREPLをシェルの代わりに使うことができます。補完もシェルと同等の機能があります。ジョブコントロールも行うためfgやjobsなども動きます。ただしシェルよりは機能は限定的です。

```
> ls -al | less
> egrep str src/*.c
> make && make install && make test
> ./configure --prefix=$HOME --with-optimize --with-interpreter
```

9. メソッドブロックの型推論が出来ます。以下のようなコードが動きます。

```
> a:SortableList<String> = {1,2,3}.map { it.toString() }
```

10.コンパイル時にスクリプトが動きリフレクションを行うことができます。コンパイル時に行うため実行時ではリフレクションのオーバーヘッドは0です。
```
    println("HELLO COMPILE SCRIPT");

    class ReflectionA {
        a:int;
        ClassField: static int;

        def initialize() {
            a = 123;
        }
        def method1() : int {
            123
        }

        def method2(a:int, b:String): String {
            return a.toString.append(b);
        }
    }

    class ReflectionB <T:Object, T2:IEqualable> {
    }

    c :Class = new Class("ReflectionA");
    c.appendField("b", "int");

    c.appendMethod("def setB(b:int) { self.b = b }");
    c.appendMethod("def getB():int { return self.b }");
    c.appendClassField("ClassField2", "String");

    class ReflectionTest
    {
        def main():static {
            a := new ReflectionA();
            Clover.test("refelection test", a.a == 123);
        }
    }

    Clover.appendClass(
        """
        class ReflectionC
        {
            field: String;

            def initialize() {
                field = "ABC";
            }
        }
        """
    );
```

11. C言語へのFFIがあります。
```
    class System
    {
        R_OK: static int from unistd.h
        def strcmp(x:pointer, y:pointer): int from libc.so.6
    }
```
などと拡張ライブラリを作成せずにC言語のライブラリを使うことができます。

12. メモリーセーフなポインタがあります。

```
    p := b"ABC"; p++; Clover.test("Memory safe pointer test", p->byte == 'B'); try { p +=100 } catch(e:Exception) { println("Out of range");  }
```

# サンプルコード

    "A,B,C".split(/,/) {it.append("X"); }
    { AX, BX, CX }

    {1,2,3}.map { it * 2 }.each { it.printf("[%d]\n"); }
    [2]
    [4]
    [6]

    > {1,2,3,4,5,6,7}.select { it > 3 }.reverse()
    {7,6,5,4}

    > 2.className().scan(/./).map { it.multiply(5) }.join("\n")
    IIIII
    nnnnn
    ttttt
    eeeee
    ggggg
    eeeee
    rrrrr

    > {1,2,3}.map { it.toString().toCommand() }.each { it.less() }

    > {uname(), hostname(), pwd()}.each { it.less() }
    
    > "AAA".scan(/./).join("+").append("\n").multiply(5000).toCommand().less()
    A+A+A
    A+A+A
    A+A+A
    A+A+A
    A+A+A
    A+A+A

# 動作環境

x86_64, i686, aarch64, armv7hl, ppc64le, sparc64, ppc64le, ppc上のLinuxで動作確認をしています。一応version 3.1.2からOSXでも動きます。OSXはreadlineがeditlineなので、REPLを動かすにはbrewなどでreadlineを入れる必要があると思います。（未確認)
あとはコンパイラにはclangを使っています。

# ライセンス

GPL2です。readlineがGPL2なので、それを利用しているclover2もGPL2となっています。

# インストール

## 依存ライブラリ

コンパイル前に依存しているライブラリの開発版のインストールが必要です。math, iconv, pcre3,readline,libz,ncursesw6つのライブラリが必要です。
Fedoraでしたら、ライブラリ名-develが開発版になります。Debian系(ubuntuなど)はライブラリ名-devのはずです。
詳しくは検索して調べてください。
あとコンパイルにはctagsが必要です。ctagsもインストールしてください。
ちなみにmathは数学用の関数、iconvは多言語化、pcreは正規表現, readlineはインタプリタのインターフェース、libzは圧縮ファイルの解凍用のライブラリ、bsdはBSDでのシステムコールの移植です。
configureオプションに--with-jitしてネイティブコードコンパイルを有効にする場合はLLVMが必要になります。筆者の環境では3.8と5.0です。3.8 laterで動くと思います。
あとはコンパイラにgcc, clang, makeをするためにGNU makeが必要となります。

ubuntu, Debianでは

    sudo apt-get install gcc
    sudo apt-get install ctags
    sudo apt-get install clang
    sudo apt-get install libreadline-dev
    sudo apt-get install libpcre3-dev
    sudo apt-get install libz-dev
    sudo apt-get install libncursesw5-dev
    sudo apt-get install ctags
    sudo apt-get install make

が必要です。
C言語のFFIが必要な場合はlibffcall1-devが必要になります。

## コンパイル

まずはソースコードを入手してください。

    git clone https://github.com/ab25cq/clover2.git

で入手することができます。

    cd clover2

として

    ./configure --prefix=$HOME --with-optimize --with-interpreter
    make
    make install
    make test

としてください。~/bin/にcclover2やclover2が登録されます。
もし管理者権限をお持ちならば

    ./configure --with-optimize --with-interpreter
    make
    sudo make install
    make test

としてください。/usr/local/binにcclover2やclover2が登録されます。
インタプリタが必要な場合は
`--with-interpreter`オプションを`./configure`に追加してください。iclover2という実行ファイル名でインタプリタが入ります。ただし、実行コードは微妙に遅くなります。(Signal Interprruptの判定がコードに埋め込まれるため)。正直誤差の範囲だと思いますが。
Methodのネイティブコードコンパイルが必要になる場合は`--with-jit`オプションを`./configure`に追加してください。--with-jitで動作が不安定な場合は--with-jitを外して実行してみてください。--with-jitはversion 8.0.0で安定しています。それでもバグが出るようなら--with-jitを外して使ってみてください。　
C言語へのFFIが必要な場合は`--with-c-ffi`オプションを`./configure`に追加してください。その場合libffcall1-devが必要になります。
環境の違いよって`--with-optimize`でセグメンテーション違反が出る場合は`--with-optimize`を外してみて実行してください。かなり処理速度が遅くなりますが、セグメンテーション違反がでなくなるかもしれません。
`--with-thread`でThreadが有効になります。その場合は`--with-optimize`がつけられません。スレッドのプログラムで最適化を行うとバグになるためです。

特定のディレクトリにファイルをインストールしたい場合は

    ./configure --with-optimize
    make
    make DESTDIR=$HOME/tmp install

などとしてください。$HOME/tmp/binにclover2, cclover2がインストールされて、$HOME/tmp/share/clover2に基礎ライブラリがインストールされます。

## パッケージング

Fedoraではパッケージになっているので、yum install clover2でいけるはずです（未確認）

Debianではパッケージによるインストールができます。. make_deb.shでパッケージの作成ができます。. install_deb.shでパッケージがインストールされます。アンインストールは sudo apt-get remove clover2です。
パッケージングはできているので、パッケージを登録してもらえるDebianの開発者募集中です。
どなたかよろしくお願いしますm(_ _)m

## リリースノート

* [リリースノート](changelog)

----

[>> 次 使い方](usage)
