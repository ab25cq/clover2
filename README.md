# clover2 computer language

この言語はアプリケーションを作るタイプの言語ではないかもしれません。iclover2を使ってシェルとして使うといいと思います。

version 11.0.0

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

    8. シェルのような記述もできREPLをシェルの代わりに使うことができます。補完もシェルと同等の機能があります。ジョブコントロールも行うためfgやjobsなども動きます。ただしシェルよりは機能は限定的です。

    ls -al | less
    egrep str src/*.c
    make && make install && make test
    ./configure --prefix=$HOME --with-optimize --with-interpreter

    9.メソッドブロックの型推論が出来ます。以下のようなコードが動きます。

    a:SortableList<String> = {1,2,3}.map { it.toString() }

    10.コンパイル時にスクリプトが動きリフレクションを行うことができます。コンパイル時に行うため実行時ではリフレクションのオーバーヘッドは0です。

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

    11. C言語へのFFIがあります。

    class System
    {
        R_OK: static int from unistd.h
        def strcmp(x:pointer, y:pointer): int from libc.so.6
    }

    などと拡張ライブラリを作成せずにC言語のライブラリを使うことができます。

    12. メモリーセーフなポインタがあります。

    p := b"ABC"; p++; Clover.test("Memory safe pointer test", p->byte == 'B'); try { p +=100 } catch(e:Exception) { println("Out of range");  }

詳しく以下を見てください。https://github.com/ab25cq/clover2/wiki
(もしくはrepositoryに含まれるmanualディレクトリ以下のドキュメントを見てください)

サンプルコード

    > "A,B,C".split(/,/) {it.append("X"); }
    { AX, BX, CX }

    > {1,2,3}.map { it * 2 }.each { it.printf("[%d]\n"); }
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

Yet another compiler and a Virtual Machine.

This compiler may be not used as making application. It may be used as shell with iclover2.

FEATURES

    1.There are two kinds of primitive classes and ordinary classes, primitive classes do not use heap. There is no method call, only operators are supported, and processing to the value of the primitive class is fast. But there are boxing and unboxing. When you make a method call to a primitive> class, add a value to a container library etc, it is boxing to reduce> use distortion of primitive class. Conversely, if it becomes an object of an operator, it is unboxed.

    2. Like functional languages, Lambda and closure are first class objects. Regular expressions are also first class objects.

    3. There is a simple Generics. It seems to simplify Java's generics. Generics information is only available at compile time, it is efficient as it disappears at run time.

    4. There is no inheritance for simplicity. There are only interfaces, classes and modules. Therefore, it is efficient to specify the method at compile time except for method calls to the interface. It is a function that can be used instead of inheritance. We support transfer in language.

    5. It is open class. You can add methods and fields later to all classes including built-in classes. You can define methods with the same name, you can do differential programming like mixin-layers style.

    6. I also have an interpreter. External commands can also be easily executed and can be easily mixed with clover2's methods.
```
    ls().grep("main.c").toString().scan(/./).join("+").toCommand().less()
    m+a+i+n+.+c
```
    And less displayed with an external command. Method names, external command names, file names are also supplemented. Just like Java IDE and PowerShell, we will complement the context.

    8. You can write like a shell and REPL can be used instead of shell. Complementation also has the same function as shell. Since job control is also performed, fg and jobs etc. also move. However, the function is more limited than the shell.

    ls -al | less
    egrep str src/*.c
    make && make install && make test
    ./configure --prefix=$HOME --with-optimize --with-interpreter

    9. You can type in method block types. The following code works.

    a:SortableList<String> = {1,2,3}.map { it.toString() }

    10. The script can perform motion reflection at compile time. Since it is done at compile time, the overhead of reflection is 0 at run time.

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

    14. Memory safe pointer

    p := b"ABC"; p++; Clover.test("Memory safe pointer test", p->byte == 'B'); try { p +=100 } catch(e:Exception) { println("Out of range");  }

See clover2 wiki on github (Japanese and English) https://github.com/ab25cq/clover2/wiki

LICENSE is GPL-2.0. see LICENSE file

Sample Code

    > "A,B,C".split(/,/) {it.append("X"); }
    { AX, BX, CX }

    > {1,2,3}.map { it * 2 }.each { it.printf("[%d]\n"); }
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

