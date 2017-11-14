
wcs:char[] = new char[4];
wcs[0] = 'A';
wcs[1] = 'B';
wcs[2] = 'C';
wcs[3] = '\0';

mbs:byte[]? = null;
System.wcstombs(&mbs, wcs);

Clover.test("wcstombs test", System.strlen(mbs) == 3 && mbs[0] == 'A' && mbs[1] == 'B' && mbs[2] == 'C' && mbs[3] == '\0');
