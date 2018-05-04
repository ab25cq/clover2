print(
        """
        aaa

        bbb
        ccc
        """
);

Clover.test("here document test",
        """
        aaa

        bbb
        ccc
        """.equals("aaa\n\nbbb\nccc\n")
);
