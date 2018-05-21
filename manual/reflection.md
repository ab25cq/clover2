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

名前でもフィールドを得られます。

    klass.getField("field1");

メソッドの情報を得るためには以下のようにします。

    klass.getMethod(0);

名前でもメソッドを得られます。

    klass.getField("method1");

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

クラスのクラスは以下のように定義されています。

    class Class
    {
        className:String;
        flags:long;
        genericsParamTypes:String[];
        genericsParamNames:String[];
        numFields:int;
        numClassFields:int;
        numMethods:int;
    }

Classのフィールドの数はnumFields, クラスフィールドの数はnumClassFields, メソッドの数はnumMethodsで得られます。クラスのフラグはflags, ジェネリクスの情報はgenericsParamTypes, genericsParamNamesで得られます。genericsParamTypesはジェネリクスの引数のインターフェスの型が入ってます。genericsParamNamesはジェネリクスの引数の名前です。

Clover.isLoadedClass(name:String)はクラスがロードさているかbool値で分かります。Clover.isDefinedClass(name:String)はクラスが定義されているかどうか分かります。(クラスファイルがあるかどうか)

Clover.append(code:String)でクラスを定義することもできます。

    Clover.appendClass(
        """
        class ReflectionC
        {
            field: String;

            def initialize() {
                field = "ABC";
            }
        }
        """
    );

以上です。色々試して理解してください。

注意してほしいのはappendFieldなどはコンパイル時にしか動かない点です。Clover2は実行時にフィールドやメソッドが追加されても、コンパイル言語なので意味はありません。コンパイル時スクリプティングで使ってください。コンパイル時スクリプティングではClover2の機能全てが使えるため、コンパイル時スクリプティング用のクラスなどを作ったりすれば、コーディングの自動化がだいぶ行えるはずです。マクロやプリプロセッサみたいなものですかね。まあ、色々楽しんでください。

コンパイル時のリフレクションではClover.compileTimeScriptingOnDeclareTime()クラスメソッドがフィールドとメソッドの宣言時にClover.compileTimeScripting()クラスメソッドがコンパイル時のスクリプトが実行される前に呼ばれます。ここでクラスにメソッドなどを追加すれば、クラスの定義時に自動的にメソッドを追加したりフィールドを追加したりできます。詳しくはReflection.clclを見てください。


