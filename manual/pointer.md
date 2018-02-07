# pointerクラス

English page is here [>> English page](pointer-en)

pointerクラスはプリミティブ型でアドレスを扱います。ただし不正なアドレスもアクセスできるため、扱いには注意が必要です。型チェックも行われません。以下の様に使います。

    > a:int = 123;
    123
    > b:pointer = &a;
    0x124a778
    > b->int = 245;
    245
    > a
    245

&aでaのアドレスを得てbにそのアドレスを代入してます。 `b->int` でアドレスbをint型として扱い245を代入しています。そうするとa自身も245が代入された状態になります。メソッドの引数に使えば、メソッドの戻り値としても使えるでしょう。その場合は

    def method(b:pointer@int)

の様にpointerの後に@をつけて型名をつけてください。bにはintのアドレスを渡してほしいと明示するためです。@以下はアノテーションといい単なるコメントですがpointer型にはどんなアドレスも代入できてしまうためアノテーションで型名を明示しておいたほうが良いです。

pointerクラスには加算と減算が使えます。例えばb++とすると

    > b++;
    0x124a778
    > b
    0x124a779

となります。加算と減算はバイト単位で++で1バイトのアドレスが増えます。--で1バイトのアドレスが減ります。

    > b += 4ul;
    0x124a77d

+= 4ulでbのアドレスに4バイトが加算されています。ポインタの演算の右辺値にはulong型を使います。64bitのPCの場合アドレスは64bitであるulong型のためです。アドレスは不正防止のため、毎回値が違います。昔はアドレスが固定で毎回同じだったため不正なハックの温床であったためです。MS-DOSがデファクトスタンダードだったころは他のプログラム（プロセス）のアドレスにさえアクセスできたため、いくらでも他のプログラムに悪いことができました。まあ、あの頃はパソコンは一部の人の遊びみたいなもんで、今ほどセキュリティにうるさくなかったためです。インターネットが始まりクレジットカード絡みで不正に他人のお金を使ったりできるようになったため、セキュリティも大事になりました。最近はプロセス単位でアドレスは独立しており、他のプログラムのアドレスにはアクセスできない上に、毎回アドレスの値も違うため、不正なプログラムは作りにくくなっています。