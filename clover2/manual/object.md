# オブジェクトクラス

English page is here [>> English page](object-en)

Objectクラスは空のインターフェースです。そのため、どのオブジェクトも代入することができます。ただし、呼び出せるメソッドはスペシャルメソッドのみとなります。className(), identfyWith()などはスペシャルメソッドのため使うことができます。className()で実行時のオブジェクトのクラスに応じた処理をしてください。何らかのクラスに変換したい場合は後述するtoAnonymous()を使ってください。もしくはisスペシャルメソッドのほうが便利かもしれません。

    a:List<Object> = new List<Object>();
    a.add(1);
    a.add("ABC");
    a.each(lambda(item:Object) {
        if(item.className().equals("Integer") {
            item2:Integer = item.toAnonymous();
            # Integerの処理
        }
        elif(item.className().equals("String") {
            item2:String = item.toAnonymous();
            # Stringの処理
        }
    });

isスペシャルメソッドを使った例

    a:List<Object> = new List<Object>();
    a.add(1);
    a.add("ABC");
    a.each {
        if(it.is("Integer")) {
            # itはInteger型
        }
        elif(it.is("String")) {
            # itはString型
        }
    });
