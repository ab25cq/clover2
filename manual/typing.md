# 型推論

English page is here [>> English page](typing-en)

Cloverの型推論にはローカル変数の型推論、ブロックオブジェクトへの型推論の2種類があります。まずはローカル変数の型推論です。

    a:int = 2;

は

    a := 2;

と書くことが出来ます。右辺値の型に応じて変数の型が宣言されます。

もう一つのブロックオブジェクトへの型推論ですが、以下のようになります。

    a:lambda(int,int):int = lambda (a:int, b:int) { return a + b }

returnされた型に応じてブロックオブジェクトの戻り値の型が決定されます。（戻り値の:intを省略できる)

(version 4.9.1よりブロックオブジェクトの型推論の戻り値の方の省略は廃止させてもらってます。すみません。)

# メソッドブロックの型推論

メソッドブロックでは引数と戻り値を省略できます。引数はit,it2,it3,....として宣言されます。

    slist{1,2,3}.each { it.toString().println() }
    1
    2
    3

    a:SortableList<String> = slist{1,2,3}.map { it.toString() }

となります。

----

[<< 前 主な機能](feature) [>> 次 ライブラリリファレンス](libraries)
