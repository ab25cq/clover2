VERSION1:="7.0.7"
VERSION2:="7.0.8"

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
