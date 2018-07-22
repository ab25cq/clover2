
    a := b"ABCDEFGHI";

    a+=2;

    Clover.test("Memory safe pointer test2", memcmp(a, b"CD", 2) == 0);
