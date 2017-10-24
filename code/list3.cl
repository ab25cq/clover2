list { 1, 2, 3 }
    .map(lambda(n:Integer):Anonymous { return n * 2; })
    .each(lambda(m:Anonymous) { m.toString().println();})

list { 1, 2, 3 }.toString().println();
