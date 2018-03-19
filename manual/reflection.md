# リフレクション

English page is here [>> English page](reflection-en)

リフレクションではまずClassクラスを作成します。コンストラクタの引数はクラス名です。

    klass:Class = new Class("ClassA");

flagsフィールドにはクラスの種類のフラグが入ってます。genericsParamTypesはジェネリクスの引数のインターフェースの名前が入った文字列型の配列です。genericsParamNamesはジェネリクスの引数の名前が入った文字列型の配列です。

フィールドを追加するには以下のようにします。

    klass.appendField("field1", "int");

メソッドを追加するには以下のようにします。

    klass.appendMethod("def method1() { 123 }");

クラスフィールドを追加するには以下のようにします。

    klass.appendClassField("classField1", "String");

フィールドの情報を得るためには以下のようにします。

    klass.getField(0);

0はインデックスです。定義の順番通りの数値を指定します。

メソッドの情報を得るためには以下のようにします。

    klass.getMethod(0);

0はインデックスです。定義の順番通りの数値を指定します。このとき注意してほしいのはフィールドを定義すると自動的にsetterやgetterのメソッドが定義されるため、思ったとおりのメソッドを得られないことがあることです。フィールドが定義されると自動的にsetterやgetterメソッドが定義されるため、それを忘れないでインデックスを指定してください。

フィールドクラスは以下のようになっています。

    class Field
    {
        flags:long;
        name:String;
        resultType:String;
        #value:Anonymous;

        def private():bool {
            return (self.flags & Clover.FIELD_FLAGS_PRIVATE).to_bool;
        }

        def protected():bool {
            return (self.flags & Clover.FIELD_FLAGS_PROTECTED).to_bool;
        }
    }

flagsはフィールドの種類を表します。nameはフィールド名、resultTypeはフィールドの型です。

メソッドのデータのクラスは以下のようになっています。

    class Method
    {
        flags:long;
        name:String;
        path:String;
        methodNameAndParams:String;
        index:int;

        params:MethodParam[];

        resultType:String;

        varNum:int;

        genericsParamTypes:String[];
    }

flagsはメソッドの種類が入っています。nameはメソッド名。pathはクラス名も含めたメソッド名です。methodNameAndParamsはメソッド名と引数の型が入った文字列が入っています。indexはクラス内でのメソッドの上から順番に定義されたインデックスが入っています。

paramsは引数の情報の配列です。

    class MethodParam
    {
        name:String;
        type:String;
    }

nameは引数の変数名。typeは引数の型の名前となっています。

varNumはローカル変数の数が入っています。

genericsParamTypesはメソッドジェネリクスのインターフェース名が入った配列です。

以上です。色々試して理解してください。
注意してほしいのはappendFieldなどはコンパイル時にしか動かない点です。Clover2は実行時にフィールドやメソッドが追加されても、コンパイル言語など意味はありません。コンパイル時スクリプティングで使ってください。コンパイル時スクリプティングではClover2の機能全てが使えるため、コンパイル時スクリプティング用のクラスなどを作ったりすれば、コーディングの自動化がだいぶ行えるはずです。マクロやプリプロセッサみたいなものですかね。まあ、色々楽しんでください。
