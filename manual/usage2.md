# 高度な使い方

English page is here [>> English page](usage2-en)

## コンパイルタイムスクリプティング

Clover2のクラスのソースファイルではClover2を動かすことができます。

    > vim ClassA.clcl
    println("HELLO WORLD");

    class ClassA {
        value1:int;
        value2:int;

        def initialize() {
            value1 = 123;
            value2 = 234;
        }
    }
    > cclover2 ClassA.clcl
    HELLO WORLD

これはなんのためにあるかですがコンパイル時にリフレクションを行うためにあります。

    > vim ClassA.clcl
    println("HELLO WORLD");

    class ClassA {
        value1:int;
        value2:int;

        def initialize() {
            value1 = 123;
            value2 = 234;
        }
    }

    klass:Class = new Class("ClassA");

    klass.appendField("value3", "int");
    klass.appendMethod("def method1() { value3 = value1 + value2; }");

    > cclover2 ClassA.clcl
    HELLO WORLD

上記のコードではClassAにはvalue3というフィールドがあり、method1ではvalue3にvalue1とvalue2の合計が代入されます。このコンパイルタイムのスクリプティングはコンパイルが終わった後のタイミングでスクリプトが実行されます。その点に注意してください。これを使うとあるフィールドがあれば、特定のメソッドを実装するなど様々な処理が書けます。詳しくはリフレクションのクラスの解説を見てください。

    version 4.8.2より__BEGIN___, ___END___で囲ったソースがクラスのコンパイル時、コンパイル前に実行されるようになりました。

## ジャストインタイムコンパイル

JITを有効にする場合はconifgureに--with-jitオプションを付けてコンパイルしてください。クラスファイルのバイトコードがClover2のクラスファイルのコンパイル時にネイティブコードにコンパイルされてダイナミックライブラリが作られます。Clover2は実行時にはネイティブコードにはコンパイルしていません。その為Clover2のJITは高速です。JITというより単なるネイティブコードコンパイラという方が正しい呼び方だとは思います。速度的にはバイトコードの3倍程度の速度がでます。ただし、ダイナミックライブラリによって実行されているため$HOME/.clover2を環境変数LD_LIBRARY_PATHに含めてください。ダイナミックライブラリの検索パスに追加しないとダイナミックライブラリが検索されないためバイトコードによって実行されてしまいます。ユーザーが作ったクラスファイルを$HOME/.clover2に登録する場合、lib[クラス名].so, lib[クラス名].so.1.0.0も$HOME/.clover2にコピーしてください。ユーザーが作ったクラスもネイティブコードによって実行されます。

クラスファイルからダイナミックライブラリにコンパイルするためにはbclover2によってコンパイルする必要があります。例えばHash.oclclなら

    bclover2 Hash.oclcl

とする必要があります。

## 対話的なプログラムの実行

iclover2というコマンドを実行すると起動されます。対話的にコマンドを実行でき、コマンドは内部的にコンパイルされて、その仮想マシン用のバイナリがiclover2に含まれた仮想マシンによって実行されます。

    > 1+1; 2*4
    2
    8

    > "ABC".append("DEF")
    ABCDEF

    > a:=2
    2
    > a*2
    4

外部コマンドも簡単に呼び出すことができ端末制御するコマンド、lessやvimなども実行することができます。

    > pwd()
    /home/ab25cq
    > pwd().toString().subString(1,5).toCommand().less()
    home/

ジョブコントロールもできvimやlessなどが実行されているときにCTRL-Zを押すとプログラムがサスペンド（一時停止）されてiclover2に制御が戻ります。
もし制御をサスペンド（一時停止）されたプログラムに戻したいときは

    > Clover.jobs.items(0).forground()

とすれば制御を戻すことができます。0はジョブの番号で複数のプログラムをサスペンドできるので番号で特定のプログラムを指定します。
ジョブの一覧を見たいときは

    > Clover.jobs

と実行すれば一時停止しているプログラムの一覧がリストで返されます。
つまりサスペンドするとJob型のインスタンスがClover.jobsというリストに追加されているということです。
もし詳しい動作が見たい方でUNIXのCが分かる方ならCommand.clclというソースファイルを見れば、内部的にどうなっているかわかると思います。

端末制御するプログラムの一覧はCommand.controllingTerminalProgramsというEqualableList&lt;String&gt;に入っています。もし追加したい場合はこのリストにプログラム名を追加してください。

    > vim("MyOwnLibrary2.clcl")
    include "MyOwnLibrary.clcl"
    class Command
    {
    　　def initialize():static {
    　　　　inherit();
    　　　　Command.controllingTerminalPrograms.add("mfler4");
    　　　　Command.controllingTerminalPrograms.add("xyzsh");
    　　}
    }

などとして追加することができます。強制的に端末制御させたい場合は"--controlling-terminal"という引数をつければ可能です。例えば

    > make("--controlling-terminal").toBool() && make("--contorlling-terminal", "install").toBool()

などと実行すればmakeは端末制御をしつつtoBool()で戻り値を得ることができます。

逆に端末制御させたくない場合は"--no-contolling-terminal"という引数をつければ可能です。

エラー出力はデフォルトでは次のメソッドに渡されませんが、"--getting-stderr"という引数をつければ可能です。例えば

    > make("--getting-stderr").head()

などと実行すればmakeの標準出力とエラー出力両方がhead()で処理されます。

カレントディレクトリのプログラムを実行したい場合はSystem.system()を使ってください。例えば./configure --with-debug --prefix=$HOMEなら

    System.system("./configure --with-debug --prefix=$HOME")

などとします。

TABキーを押すと文脈によって入力の補助（補完）ができ、コマンド名の補完やメソッド名の補完、ファイル名の補完も使うことができます。

    > 1.[TABキー]
    Integer型のメソッド一覧
    > 123.toString().[TABキー]
    String型のメソッド一覧
    > ls[TABキー]
    lsと名前の付くコマンドの一覧
    > ls("src/ma[TABキー]
    src/main.c"などとファイル名が入力補助される

対話的に使え、外部コマンドが簡単に実行できるため便利に使えると思います。

オプションはiclover2 -s "文字列"で初期入力文字列、-p "数値"でカーソル位置、-cで一度コマンドを実行したらREPLを終了します。

## シェルモード

後からの追加ですが対話的なプログラムの実行時に便利なようにシェルのような記述も行えます。
（どうしてもClover2の文法ではタイプ数が多くなるため何度も実行するvimなどのコマンドでは不便なため)

ls -al src/main.cなども実行できます。

    > ls -al main.c
    -rw-r--r-- 1 ab25cq ab25cq 1098 Sep 23 10:46 src/main.c

cd, fg, jobsなどのシェルのコマンドも入ってます。Commandクラスのメソッドとなってます

グロブも使えます。

    > egrep main src/*.c
    src/compiler.c:int main(int argc, char** argv)
    src/interpreter.c:int main(int argc, char** argv)
    src/main.c:int main(int argc, char** argv, char* const * envp)

パイプも使えます。

    > ls -al | less

内部的には全てCommandクラスのメソッドに変換されています。単なる糖衣構文です。

    > echo $HOME
    /home/ab25cq

環境変数の展開もします。

    > egrep "str str" src/*.c
    > egrep str\ str src/*.c
    > egrep 'str str' src/*.c

クォートもあります。

    > make && make install && make test

&amp;&amp;や||などもあります。

    > ./configure --with-optimize

カレントディレクトリと親ディレクトリのみパスによるコマンドの実行ができます。/usr/bin/bashなどは実行できません。
(正規表現と文法が重なるため)
その場合はbashやzshやyashを実行してシェル上で実行するか、System.system("/usr/bin/bash")などとしてください。

シェルモードはあくまでおまけです。シェルはやっぱりちゃんとしたシェルを使ってください。個人的にシェルの代わりに使うために作っている機能です。

ただし、一つ重要な点はシェルモードで記述した場合、最後のプログラムは端末制御される点です。
つまり`ls`は端末制御されますが`ls()`は端末制御されません。その点に気をつけてコードを書くといいですね。

[<< 前 ライブラリリファレンス](libraries) [>> 拡張ライブラリ](extension)
