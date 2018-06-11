# regexクラス

English page is here [>> English page](regex-en)

正規表現のプリミティブ型です。正規表現はString型でしか使わないためString型と一緒に解説します。正規表現とは文字列処理に使うもので、以下のようなものがあります。

メタ文字

    \A	文字列先頭
    \Z	文字列末尾
    \b	単語境界
    \B	単語境界以外
    \w	英数字と '_'(アンダースコア)
    \W	英数字と '_'(アンダースコア)以外
    \s	空白文字 ( ' '(スペース), '\t', '\n', '\r' )
    \S	空白文字以外
    \d	数字 (0...9)
    \D	数字以外
    \t	タブ文字
    \n	改行文字 (\0x0d)
    \r	復帰文字 (\0x0a)
    \xHH	2桁の16進数(HH)で指定される文字コード

例えば `\d` は `1` から `9` を全部を表します。例えば `9999` は `\d\d\d\d` にマッチします。

    ^	行頭
    $	行末
    \b	単語の区切り
    \B	単語の区切り以外

例えば `^\d` は行頭に来る数値だけにマッチします。

    {n,m}	n回以上、m回以下の繰り返し
    {n,}	n回以上の繰り返し
    {n}	n回の繰り返し
    \*	0回以上の繰り返し ({0,}に同じ)
    \+	1回以上の繰り返し ({1,}に同じ)
    \?	0または1回の繰り返し ({0,1}に同じ)

例えば `ba+` は `baa` や `baa`, `baaaaa` にマッチます。 `ba{1,2}` だと `ba` と `baa` のみです。

    [a-z]	'a' から 'z' までの英小文字のどれかにマッチ
    [A-Z]	'A' から 'Z' までの英小文字のどれかにマッチ
    [a-zA-Z]	英小文字または英大文字のいずれかにマッチ
    [0-9]	'0' から '9' までのいずれかの数字にマッチ
    [a-zA-Z0-9]	数字または英文字のいずれかにマッチ
    [\]\-]	] または - にマッチ

例えば `[a-zA-Z]+` だと英単語にマッチします。

    (strings)	strings が一つのグループ
    (str1 | str2)	str1またはstr2 にマッチ

Clover2 の正規表現はpcreを使っているのでperl5と互換性があります。ここでは以上にしておきます。詳しくは他のページに解説を譲ります。

次にString型で正規表現を使っているメソッドを解説します。

String.matchは文字列が正規表現にマッチするかどうかbool値で戻り値を返します。trueだとマッチしたということを表し、falseだとマッチしなかったと表します。

    > "ABC".match(/\d/)
    false
    > "ABC".match(/^A/)
    true

正規表現は/.../と表現します。 `"ABC"` は数値でないため `\d` にはマッチしません。そのためfalseが返っています。ABCは行頭にAが来ているため^Aにはマッチします。そのためtrueが返っています。グループ化文字列を取りたい場合は以下の様にします。グループ化文字列とはマッチした正規表現で()で囲んだ部分の文字列を言います。

    > group_strings := new EqualableList&lt;String&gt;();
    list {}
    > "ABCABCABC".match(/^A(..)/, group_strings);
    true
    > group_strings
    list {BC}

/^A(..)/でAの次に来る任意の２文字はBCなのでgroup_stringsにBCが入っています。

String.subは文字列を変換するメソッドで以下の様に使います。

    > "ABCABCABC".sub(/^A/, "B")
    BBCABCABC

/^A/で行頭のAを表します。それを"B"に変換しています。グループ化した文字列を得たい場合は以下の様にしてください。

    > group_strings = new EqualableList&lt;String&gt;();
    list {}
    > "ABCABCABC".sub(/A(..)/g, "B", group_strings);
    BBB
    > group_strings
    list {BC,BC,BC}

/A(..)/はAで始まり任意の一文字が二つものという意味です。/A(..)/の後にgがついていますが、gがついていると１回マッチすると処理を終わるのではなく、マッチが終わるまで何回も繰り返します。
(..)の()はグループ化でこの場合group_stringsに入れたい文字列を指定します。/A(..)/でABCがマッチしているのでBCが3個group_stringsに入っています。

gなどの正規表現のオプションには以下があります。

    m  複数行モード - ^ と $ が内部的な行にマッチします
    i  大小文字の違いを無視します
    s dotall
    A anchored
    D dollar_endonly
    U ungreedy
    x  読みやすさの拡張 - 空白やコメントを自由に置けます
    g  グローバル - マッチするものすべて

詳しくはpcreのマニュアルを見てください。作者もgとiとm以外はあまりわかっていません、、、、。

subにはlambda式もとることができます。

    > "ABCABCABC".sub(/A(.)(.)/g, lambda(match_string:String, group_strings:EqualableList&lt;String&gt;):String {
        return "A".append(group_strings.join("+"));
    })
    AB+CAB+CAB+C

/A(.)(.)/gとしているため、この正規表現にマッチするごとにlambda式が実行されます。lambda式の戻り値が変換結果です。引数はこの場合match_stringにABCというマッチした文字列全体が、group_stringsに{B,C}が入っています。group_strings.join("+")でB+Cが返されるため、"A".append(group_strings.join("+"))でAB+Cがlambda式の戻り値です。この文字列を変換結果にしてA(.)(.)にマッチする文字列が変換されます。

次にString.scanを解説します。String.scanは文字列から任意の文字列を取り出すメソッドです。例を見ていただいたほうが早いです。

    > "ABC".scan(/./)
    list {A,B,C}

scan(/./)によって一文字ずつ文字がとられてlistになっています。/./は任意の一文字を表すためです。scanはgをつけなくても正規表現のマッチを繰り返します。もう一つ例を見てみましょう。

    > "ABC123ABC345".scan(/\d\d\d/)
    list {123,345}

`scan(/\d\d\d/)` によって数値３桁を取り出すことができます。lambda式を取ることもできます。

    > "ABC123ABC345".scan(/\d\d\d/, lambda(match_string:String, group_strings:EqualableList&lt;String&gt;): String {
        return match_string.scan(/./).join("+");
    });
    list {1+2+3,3+4+5}

lambda式の戻り値がscanの戻り値のListの要素一つ一つになります。`group_strings:EqualableList<String>` は()で囲った部分の正規表現がある場合、()内にマッチした文字列がはいります。(グループ化といいます）

次にString.splitの解説に移ります。String.splitは文字列を区切り文字列で分けることができるメソッドでちょうどscanの逆だと考えることもできます。例を見てみましょう。

    > "ABC\nDEF\nGHI\n".split(/\n/);
    list {ABC,DEF,GHI}

この場合改行文字でsplitしているためテキストの各行を取ることができます。もう少し例を見ましょう。

    > "ABC,DEF,GHI\nJKL,MNO,PQR\nSTU".split(/,|\n/);
    list {ABC,DEF,GHI,JKL,MNO,PQR}

カンマ区切りで各行に英単語がありますが、英単語だけ取り出しています。 `/,|\n/` は,と改行文字が区切りのためです。

splitにもlambda式を取ることができます。

    > "ABC,DEF,GHI".split(/,/, lambda(match_string:String):String {
        return match_string.chars(0).toString();
    });
    list {A,D,G}

match_stringにマッチした文字列が入っているため、その先頭の文字をchars(0)で取って返しています。lambda式の戻り値がsplit自体の戻り値の要素の一つになります。

次にindexOfの解説に行きたいと思います。indexOfはマッチする文字列のオフセット(先頭からのインデックス）を返します。見つからなかった場合は-1を返します。

    > "ABC123".indexOf(/\d\d\d/)
    3
    > "ABC".indexOf(/\d\d\d/)
    -1

indexOf()の戻り値が-1かどうかを判定すれば、ある部分文字列が文字列に含まれるかどうかを判定することができます。

以上です。
