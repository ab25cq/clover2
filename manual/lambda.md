# lambdaクラス

English page is here [>> English page](lambda-en)


lambdaとはコードの塊をオブジェクトして扱えるようにしたものです。関数型プログラミング言語ではおなじみの機能です。lambdaにはclosureというものもあり、lambdaは親の変数にアクセスできませんがclosureは親の変数にもアクセスできます。例を見たほうが早いと思います。

    > a:lambda(int) = lambda(num:int) {
        for(i:=0; i&lt;num; i++) {
            println("HO!");
        }
    }
    > a(3)
    HO!
    HO!
    HO!

    > n:int = 3;
    > b:lambda() = closure() {
        for(i:=0; i&lt;n; i++) {
            println("HO!");
        }
        n = 999;
    }
    > b()
    HO!
    HO!
    HO!
    > n
    999

closureはlambdaの一種なので型名はlambdaで書くことになっています。closureのほうは親のnという変数にアクセスできています。また、親の変数を書き換えることも可能です。
戻り値も作ることができます。以下を見てください。

    > a:lambda(int):int = lambda(n:int):int {
        return n * 2;
    }
    > a(123)
    246

lambda(n:int):intでintをnを引数として戻り値がint型のlambdaを作っています。この場合中身は引数の2倍を返すlambdaなのでa(123)とすると246が返されています。
