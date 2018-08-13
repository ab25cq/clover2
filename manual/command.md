# コマンドクラス

English page is here [>> English page](command-en)

Commandクラスでは外部コマンドを実行することができます。

    > Command.pwd()
    /home/ab25cq

Commandクラスはクラスメソッドを呼ぶ場合Command.を省略することができます。

    > pwd()
    /home/ab25cq

Commandクラスの外部コマンドの戻り値はCommandなのでメソッドチェインでシェルでいうパイプのように外部コマンドをつなげることができます。

    > ls("src/").grep("main")
    main.c

Commandクラスのメソッドの引数には文字列以外にArray, EqualableArray, SortableArray, List, EqualableList, SortableListを渡すことができます。その場合要素が文字列の場合展開されて実行されます。

    > egrep("main", p"src/".glob("\*.c"))
    src/compiler.c:int main(int argc, char** argv)
    src/interpreter.c:int main(int argc, char** argv)
    src/main.c:int main(int argc, char** argv)

`p"src/".glob("\*.c")` の戻り値は `SortableList<String>` ですが、要素であるStringがそれぞれegrepの引数として渡されています。

toString()メソッドで出力されたテキストを文字列に変換できるのでStringのメソッドをCommandの実行結果に使うこともできます。

    > ls("src/").grep("main").toString().scan(/./).join("+")
    m+a+i+n+.+c

toBool()メソッドで外部コマンドの実行結果が正しく終わったかどうかbool値で知ることができます。

    > pwd().toBool()
    true

toBoolAndOutput()メソッドで出力を画面に表示しながら実行結果を得ることができます。（端末制御はされませんが、、、、）

    > pwd().toBoolAndOutput()
    /home/ab25cq
    true

`write(path:STring, permission:mode_t):Command` と `write(path:String): Command` メソッドで出力をファイルに保存することができます。

    > pwd().write("output_of_pwd")
    /home/ab25cq
    > cat("output_of_pwd")
    /home/ab25cq

StringクラスにはtoCommand()メソッドがありCommandクラスに変換することができるので例えばStringオブジェクトをlessしたりすることもできます。

    > "ABC".scan(/./).join("+").toCommand().less()
    A+B+C

Commandクラスは組み込みのクラスではなくユーザークラスです。定義はCommand.clcを見てください。dynamic_classの仕組みを使って実現されています。Clover2はopen classなので、あとからメソッドを追加することも可能です。

Commandクラスのメソッドが一つの場合シェルのような記述ができます。

    > ls -al src/main.c
    -rw-rw-r--. 1 ab25cq ab25cq 1098  9月 18 08:01 src/main.c
    > vim src/main.c

パイプでつなげる記述はありません。パイプのようなことがしたい場合は `ls("-al", "src/main.c").less()` などと通常のClover2の文法通り記述してください。

でしたが、パイプや&&や||も後からの追加ですが入れてます。詳しくはシェルモードの項目を見てください。

あと追加でCommand.getErrorOutput():Command, Command.getOutputWithError():Commandを入れています。エラー出力がCommand型で取れます。前者はエラー出力のみ、後者は標準出力だけです。副作用としてエラー出力が画面には出力されなくなりました。

