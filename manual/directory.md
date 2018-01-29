# ディレクトリクラス

English page is here [>> English page](directory-en)

ディレクトリのクラスです。Fileクラスと同じくopenしてclosedirする方法と一度にファイル名の一覧にアクセスする方法の二つあります。基本的に一度にファイル名の一覧を得る方法しか使わないと思います。

    > dir:Directory = new Directory("src/");
    > dir.readdir();
    byte.c
    > dir.closedir();

readdir()はnullを返すまでファイル名の一覧を返し続けます。普通はwhile文でnullを返すまでループさせるでしょう。次に一覧を一回で得る方法を紹介します。

    > Directory.entries("src/");
    list {src/byte.c,src/exception.c,src/script_ctime.c,...,src/code.c}

entriesで `SortableList<String>` 型のファイル名の一覧が得られます。第一引数が対象のディレクトリです。

    > Directory.glob("src/", "\*.c");
    list {src/byte.c, ..., src/code.c}

globはグロブにマッチするファイル名の一覧が得られます。第一引数は対象のディレクトリです。第二引数がグロブです。

    > Directory.glob("\*.clc");
    list {./File.clc,./Container.clc,./Fundamental.clc,./Command.clc,./String.clc,./MyOwnLibrary.clc,./x.clc}

globを一つの引数で使うとカレントディレクトリでグロブにマッチするファイル名の一覧が得られます。
