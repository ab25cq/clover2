# ファイルクラス

English page is here [>> English page](file-en)

ファイルクラスとはファイルにデータを書き込んだり、読み込んだりすることができるクラスです。System.readやSystem.openのシンプルなラッパークラスで、特に便利なメソッドは用意していません。

ファイルに書き込むためには以下の様にします。

    > file:File = new File("x.txt", System.O_CREAT|System.O_TRUNC|System.O_WRONLY, 0644);
    > file.write(B"ABC");
    3
    > file.close();
    > cat("x.txt")
    ABC

System.O_CREAT|System.O_TRUNC|System.O_WRONLYはファイルをopenするときのフラグで書き込みモードでオープンするという意味です。(O_TRUNCはファイルを上書きするという意味があるためx.txtがすでにあるなら消えてしまいます)file.write(B"ABC")というのはB"ABC"というバッファをファイルに書き込むという意味です。B""はBufferクラスの値の表現です。Bufferクラスは解説していませんが、Stringとは違い生のテキストやバイナリファイルを扱うことができます。Stringから変換する場合は"ABC".toBuffer()などとします。この場合は単なるアルファベット3文字をデータとして持つBufferオブジェクトを生成してファイルに書き込んでいます。書き込んだ後はcloseしています。closeはなくてもプログラム終了時に行われますが、一つのプロセスがopenできるファイルの数は限られているはずなので、使った後はcloseするのが普通です。あとclose時にファイルに実際に書き込まれることになる場合もあるようなので（不確かな情報ですが）ファイルを使い終わったあとはcloseしてください。cat("x.txt")で実際にx.txtにABCが書き込まれていることが確認できました。

ファイルをオープンしないで書き込むこともできます。

    > File.write("x.txt", "ABC\nDEF\nGHI\n".toBuffer());
    12
    > cat("x.txt")
    ABC
    DEF
    GHI

この場合O_TRUNCが内部で指定されているため、強制的に上書きされることに注意してください。ファイルのパーミッションを指定したい場合は以下の様にします。

    > File.write("x.txt", B"ABC", 0777);
    3

ファイルのパーミッションについてはUNIXの基礎ですので、検索して学んでください。この場合0777なので他のユーザーからも書き込み権限があります。

次に読み込む場合について解説します。

    > file2:File = new File("x.txt");
    > data:Buffer = file2.read();
    ABC
    DEF
    GHI
    > file2.close();
    > data.toString().print()
    ABC
    DEF
    GHI

readにはサイズをread(3)などと指定すれば、指定したバイト数だけファイルを読み込めます。

ファイルをオープンしないファイルの読み込み方法もあります。

    > File.read("x.txt")
    ABC
    DEF
    GHI

ただしreadにしろwriteにしろバッファリングなどは行っていないため、とても大きなファイルの処理などで速度が出るかはわかりません。そのあたりはユーザー任せになっています。

追記
Systemにfopenやfclose, fwrite,freadを追加したため、ファイルのバッファリングができるようになりました
以下のように使います

    > f := new File("x.txt", "r");
    > f.read();
    ABC
    DEF
    GHI
    > f.close();
    
"w"が書き込み時のファイルオープンです。

    > f := new File("x.txt", "w");
    > f.write(b"ABC");
    > f.close();
    
"a"が書き込む時の追記です。
このファイルのイニシャライザを使った場合のファイルの読み書きはfopenが使われてバッファリングされます。詳しくはC言語のfopenのマニュアルを見てください。

ファイルの読み書きは以上です。




