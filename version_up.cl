VERSION1:="7.1.1"
VERSION2:="7.1.2"

{ "src/interpreter.c",
  "src/compiler.c",
  "src/get_type.c", 
  "debian/control",
  "debian/files",
  "README.md",
  "src/main.c" }
.each {
    tmpfile := "\{it}.result";
    cat(it).toString().sub(/\{VERSION1}/g, VERSION2).write(tmpfile)
    mv(tmpfile, it);
}
