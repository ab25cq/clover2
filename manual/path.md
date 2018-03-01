# パスクラス

English page is here [>> English page](path-en)

Pathクラスはファイルのパスを表すクラスです。オブジェクトの値の表現はp"src/"などとpの後にダブルクォートで囲まれた文字列です。
早速メソッドを紹介していきましょう。

    > p"src/main.c".realpath()
    /home/ab25cq/repo/clover2/src/main.c

realpath()は絶対パスを返します。一つ注意したい点はファイルが存在している必要がある点です。もし、存在しないファイルの絶対パスが必要な場合は一時的にtouchなどでファイルを作り、realpathメソッドを読んだ後に、消してしまうという方法があります。

    > p"src/main.c".dirname()
    src

dirname()はパスのディレクトリ部分のパスを返します。

    > p"src/main.c".basename()
    main.c

basename()はパスのファイル名の部分のパスを返します。

    > p"src/main.c".extname()
    c

extname()は拡張子を返します。UNIXのファイル名には拡張子は無く、単なるファイル名の一部ですが、慣習的に拡張子のように.の後にファイルの種別表す文字列をつけます。extname()はそれを返します。

    > p"src/main.c".read()
    ... main.c の中身 ...

read()はファイルをすべて読み込みBufferオブジェクトに格納して返します。File.readでもいいのですが便利なので、一応作っています。

    > p"x.txt".write(B"ABC")
    3
    > cat("x.txt")
    ABC

writeは逆にBufferオブジェクトをファイルに書き込みます。ファイルのパーミッションは0644で書き込まれます。File.writeと同じくSystem.O_TRUNCフラグがつけられているためファイルは上書きされます。注意が必要です。

    > p"x.txt".chmod(0777)
    > ls("-al", "x.txt")
    -rwxrwxrwx 1 ab25cq ab25cq 3 3月 2 11:34 x.txt

chmodはファイルのパーミッションを変えます。0777なので-rwxrwxrwxとなっています。chmodの仲間にlchmodがあります。この場合対象がシンボリックリンクだった場合はシンボリックリンク自身のパーミッションを変えます。

    > p"x.txt".chown(1000, 1000)

chownはファイルの所有者を変えます。一つ目の引数がユーザーIDで２つ目がグループIDです。ユーザーIDは/etc/passwdにグループIDは/etc/groupに書き込まれています。ルート権限がないと使うことはないでしょう。ユーザー名からユーザーIDを得たい場合は/etc/passwdを読み込んでscanなりを使えばいいでしょう。もしくはPathクラス自体にそのようなメソッドを作ると便利かもしれません。そのあたりはユーザーの皆様に任せます。lchownはシンボリックリンク自体のファイルの所有者を変えます。

    > p"x.txt".unlink()
    > ls("x.txt")
    ls: x.txtにアクセスできません：そのようなファイルやディレクトリはありません

unlinkはファイルを削除します。外部プログラムのrmのほうが安全かもしれません。

    > p"src/main.c".access(System.F_OK);
    0

ファイルが存在しているかどうか確認します。存在しているなら0が返されます。引数にはSystem.F_OK, System.R_OK, System.W_OK, System.X_OKのどれかが使われます。それぞれ、ファイルが存在しているか、読み込めるか、書き込めるか、実行できるかを調べます。

    > p"src/main.c".utime(System.time(), System.time())

utimeはファイルのアクセスタイムと修正時間を変更します。第一引数がアクセスタイム、第二引数が修正時間です。普段使うことはないでしょう。

    > p"src/main.c".fnmatch("*.c");
    true

    > p"src/main.c".fnmatch("*.c", 0);
    true

fnmatchはグロブによるファイル名の判定を行います。グロブとはファイル名のパターンマッチングで正規表現とはまた違います。シェルを使っている方なら知っていると思います。MS-DOSではワイルドカードと呼ばれました。グロブには以下のようなものがあります。

    ? あらゆる単一の一文字にマッチする
    * あらゆる文字列にマッチする
    [AB] AとBにマッチする。
    [A-Fa-f0-9] [ABDEFGabcdef0123456789]と同じ
    [!A] A以外の一文字にマッチする

p"src/main.c".fnmatch("\*.c")は\*.cにマッチするためtrueが返っています。fnmatchの二番目の引数はあまり使わないと思いますが以下のようなフラグです。

    System.FNM_NOESCAPE このフラグがセットされていると、バックスラッシュ (\) をエスケープ文字 ではなく通常の文字として扱う。
    System.FNM_PATHNAME このフラグがセットされていると、 string 中のスラッシュ (/) を pattern にあるスラッシュそのものにだけマッチさせ、 アスタリスク (*) や疑問符 (?) のメタキャラクターや、 スラッシュを含むブラケット表現 ([]) にはマッチさせない。 
    System.FNM_PERIOD このフラグがセットされていると、 string の先頭ピリオド (leading period) は pattern 中のピリオドそのものにしかマッチしない。先頭ピリオドとは、 string の最初の文字位置にあるピリオドのことである。ただし FNM_PATHNAME フラグが同時にセットされている場合には、スラッシュの直後に続くピリオド も先頭ピリオドとみなされる。 
    System.FNM_FILE_NAME これは FNM_PATHNAME に対する GNU での同義語である. 
System.FNM_LEADING_DIR このフラグは GNU での拡張である。これがセットされている場合には、 パターンが string の最初の部分 (にスラッシュを付けたもの) にマッチすれば、 マッチしたものとみなされる。 このフラグは主として glibc で内部的に使用するもので、そのためにのみ実装されている。 
    System.FNM_CASEFOLD このフラグは GNU での拡張である。これがセットされている場合には、 パターンのマッチに大文字小文字が区別されない。 

僕もよくわかってません。manからコピーしてきました。まれに必要になるかもしれません。細かなファイル名の処理は正規表現を使ったほうがいいと思いますが、、、、。

    > p"x.txt".link("z.txt");
    > ls("-al", "z.txt");
    -rw-r--r-- 2 ab25cq ab25cq 4  3月 12:06 z.txt

linkはハードリンクを作ります。x.txtからz.txtへのハードリンクが作られました。ハードリンクとは同一のファイルに別の名前を２つ以上作ることができる機能です。この場合x.txtとz.txtは同一のファイルです。

    > p"x.txt".symlink("y.txt");
    > ls("-al", "y.txt");
    lrwxrwxrwx 1 ab25cq ab25cq 5 3月 2 12:09 y.txt -> x.txt

symlinkはシンボリックリンクを作ります。Windowsでいうショートカットですね。この場合x.txtとy.txtは同一のものではありませんがy.txtにアクセスされるとリンクが辿られてx.txtとして扱えます。

    > p"y.txt".readlink()
    x.txt

readlinkはシンボリックリンクがさしているファイル名を読み込んで返します。

    > p"y.txt".rename("y2.txt")
    > ls("-al", "y2.txt")
    lrwxrwxrwx 1 ab25cq ab25cq 5 3月 2 12:13 y2.txt -> x.txt

reanmeはファイル名を変更します。

    > p"x.txt".truncate(1ul)
    > cat("x.txt")
    A

truncateはファイルを引数の数だけ短くします。この場合1ulなので1文字に縮められてます。引数はulong型です。（ファイルのサイズは64bitまであるので）

    > p"src/".chdir();

chdir()はカレントディレクトリを変更します。シェルでいうcdですね。Clover2にはcdは用意していないため、これでカレントディレクトリを変更してください。Globalクラスにcdというクラスメソッドを作ったりしてもいいかもしれません。

(現在cdメソッドはCommandクラスに実装されています)

    > p"my_dir".mkdir();
    > ls("-dl", "my_dir");
    drwxr-xr-x 2 ab25cq ab25cq 4096 3月 2 12:34 my_dir/

ディレクトリを作成します。パーミッションは0755です。別のパーミッションで作りたい場合は第一引数に0700などと指定してください。

    > p"my_dir".rmdir();
    > ls("-dl", "my_dir");
    ls: my_dir/にアクセスできません: そのようなファイルやディレクトリはありません

ディレクトリを削除します。

    > p"src/".entries()
    list {src/byte.c,src/exception.c,src/script_ctime.c,src/constant.o, .... ,src/code.c }

ディレクトリのファイルの一覧をSortableList&lt;String&gt;型で返します。

    > p"src/".glob("*.c")
    list {src/byte.c,src/exception.c,src/script_ctime.c,...,src/code.c }

グロブにマッチするファイルの一覧をSortableList&lt;String&gt;型で返します。
