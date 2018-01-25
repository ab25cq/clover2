# boxingとunboxing

前述したとおり型にはプリミティブ型とそうでないユーザークラス型の2種類あります。プリミティブ型はGenericsの型引数になるときはboxingされます。以下のように変換されます。

> int → Integer<br>
> uint → UInteger<br>
> byte → Byte<br>
> ubyte → UByte<br>
> short → Short<br>
> ushort → UShort<br>
> long → Long<br>
> ulong -> ULong<br>
> char → Char<br>
> float → Float<br>
> double → Double<br>
> bool → Bool<br>
> pointer → Pointer<br>

またメソッドコールされるときもboxingされます。わかりやすく言うとプリミティブ型には演算子しかありません。またユーザークラスにはメソッドコールしかありません。プリミティブ型にメソッドコールされるときは対応するユーザークラスにboxingされるということです。
また逆にユーザークラスを演算子の対象にするとunboxingされて対応するプリミティブ型になるということです。
