print("""
      HELLO
      HELLO
      HELLO
      """);

Clover.test("Multi Line String", "Hello World!
Hello World!
Hello World!
".equals( """
          Hello World!
          Hello World!
          Hello World!
          """
));

Clover.test("Multi Line String2", "Hello World!
Hello World!
Hello World!
".equals( 
    """
    Hello World!
    Hello World!
    Hello World!
    """
));
