# バッファークラス

English page is here [>> English page](buffer-en)

Stringクラスは文字列を表すクラスですがバッファークラスはバイト列を表すクラスです。内部的にはpointerオブジェクトにmallocしてメモリを確保しています。使い方は以下です。

    > a:Buffer = new Buffer(3.to_ulong);
    > a.append('A'.to_byte);
    > a.append('B'.to_byte);
    > a.append('C'.to_byte);
    > a
    ABC

注意してほしいのはnull-terminatedされないことです。toString()されるときはnull-terminatedされますが、バッファは上の例だとABCのみ入っていて末尾に0は入っていません。
Bufferオブジェクトもappendできます。

    > a:Buffer = new Buffer(3.to_ulong);
    > a.append(B"ABC");
    > a
    ABC

Bufferクラスのオブジェクト表現はB""です。Bufferクラスは大きさは決まっていなくappendされると自動的に新しくメモリが確保されます。その時reallocされるので、self.bufferのさすメモリは変わる可能性があることに注意してください。
charsでoffset(先頭メモリからのインデックス)によるデータのアクセスができます。戻り値はbyteです。

    > a:Buffer = B"ABC";
    ABC
    > a.chars(0)
    65
    > a.chars(1)
    66
    > a.chars(-1)
    67

equalsでBufferオブジェクト同氏を比較できます。

    > B"ABC".equals(B"ABC")
    true
    > B"ABC".equals(B"DEF")
    false

subBufferで部分バッファがとれます。

    > B"ABCDEF".subBuffer(1,3);
    BC
    > B"ABCDEF".subBuffer(3,-1);
    DEF

-1は末尾を表します。
