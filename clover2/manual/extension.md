# 拡張ライブラリ

English page is here [>> English page](extension-en)

Clover2の拡張ライブラリの作成は結構複雑です。C言語でのソースの書き方はsrc/class_system.cを参考にすればいいと思います。注意点はオブジェクトは必ずClover2のスタック上に存在しないといけないということです。そうでないとGCでゴミオブジェクトと判定されて削除されてしまいます。GCが呼び出されるタイミングはオブジェクトを作る関数全般です。この時スペースが無ければGCが呼び出されます。難しいと思いますがsrc/class_system.cを参考に書いてください。

Clover2の拡張ライブラリの作成は複雑ですが、主にC言語の関数の薄いラッパーとして実装することを想定しています。そうすれば、それほど複雑にせずに作成することが出来ます。一応Clover2のデータはC言語のデータに構造体以外は対応するものを用意しています。構造体もポインタである場合はpointer型として扱うと特に問題がないです。問題は構造体を直接使っている場合で、その場合面倒ですが、構造体の一つ一つのフィールドを引数として渡して、C言語の関数側で構造体を作成してください。そうすれば特に問題なくC言語の関数のラッパーメソッドとして定義することができます。
C言語での定数はクラスフィールドとして定義してinitializeクラスメソッドで初期化してください。初期化の仕方はsrc/class_system.cやFile.clcなどが参考になるでしょう。C言語でのマクロはメソッドとして定義してしまえば特に問題がないです。

後参考になるソースとしてはext.clc, ext.cl, ext/hello.cがあります。テストコードですが簡単な拡張ライブラリの書き方として参考になるかと思います。

もう一つの注意点はnative methodはstaticでしか作れない点です。クラスメソッドとして定義するしかないです。native methodはC言語の関数の薄いラッパーとして定義することを想定しているためです。一度C言語のラッパーメソッドさえ用意してしまえば、あとはClover2側のクラスでそれを使って処理を書いてしまえばいいという考え方です。

一応ちょっとだけ詳しく書いておきます。まずはC言語でext/hello.cを参考に関数を書いてください。そして、その関数を含むダイナミックライブラリを作ってください。ダイナミックライブラリの作り方はMakefileにダイナミックライブラリを作っているコマンドがあるはずなので、それを参考にしてください。それをnative methodを定義したいクラスのクラスメソッドinitializeのなかで、System.dlopenを使ってロードします。そしてSystem.dlsymで関数のポインタを得ます。得た関数のポインタを

    def put_fun_to_hash_for_native_method(
        path:String, fun_name:String, native_method:pointer): static native;

メソッドでClover2に登録します。

    put_fun_to_hash_for_native_method(
        path:String, fun_name:String, native_method:pointer)

の引数のpathは例えばTestAクラスのfun(a:int, b:int)メソッドなら"Test.fun(int,int)"という文字列を渡します。この"Test.fun(int,int)"には空白があってはいけません。引数がない場合は"Test.fun()"などとなります。2番めの引数のfun_nameは"Teset_fun"とします。そしてC言語ではTest_funという関数を定義すると終わりです。C言語の関数をClover2のメソッドとする登録の仕方はext.clcを参考にしてください。

詳しくは `ext.clc`, `ext.cl`, `ext/hello.c` を見て大まかな書き方を学び、 `src/class_system.c` でC言語の関数の書き方を学んでください。

----

[<< 前 高度な使い方](usage2) [>> 次 あとがき](conclusion)
