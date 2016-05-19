#######################################################
# installed directories
#######################################################
prefix=/home/ab25cq
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
datadir=${datarootdir}
mandir=${datarootdir}/man
libdir=${exec_prefix}/lib
sharedstatedir=${prefix}/com
sysconfdir=${prefix}/etc/clover2
includedir=${prefix}/include/clover2
datarootdir=${prefix}/share/clover2
docdir=${datarootdir}/doc

##########################################################
# environmnet variables
##########################################################
CC=clang
INSTALL=/usr/bin/install -c
CFLAGS=-Isrc/ -I. -L . -I/home/ab25cq/include -L/home/ab25cq/lib -fPIC -DSYSCONFDIR="\"${sysconfdir}/\"" -DDOCDIR="\"${docdir}/\"" -DDATAROOTDIR="\"${datarootdir}/\"" -I/usr/local/include -L /usr/local/lib -g -DMDEBUG -Werror -DVM_DEBUG -Qunused-arguments
LIBS= -lutil -lonig -lpthread -lreadline -ldl -lm
DESTDIR=
SO_VERSION=1.0.0
LIBSONAME=libclover2.so
LIBSO2NAME=libclover2.so.1.0.0
OS=LINUX
OBJS=src/main.o src/vm.o src/type.o src/stack.o
COMPILER_OBJS=src/compiler.o src/parser.o src/node_type.o src/node.o src/vtable.o src/script.o src/block.o src/class_compiler.o src/klass_compile_time.o src/method_compiler.o
LIB_OBJS=src/buffer.o src/debug.o src/xfunc.o src/klass.o src/constant.o src/code.o src/native_method.o src/exception.o src/object.o src/heap.o src/class_system.o src/class_clover.o

##########################################################
# main
##########################################################
all: lib cclover2 clover2
	if test $(OS) = DARWIN; then ctags src/*.c > /dev/null 2>&1; else ctags -R; fi

cclover2: config.h $(COMPILER_OBJS)
	clang -o cclover2 $(COMPILER_OBJS) $(CFLAGS) -lclover2 $(LIBS)

clover2: config.h $(OBJS)
	clang -o clover2 $(OBJS) $(CFLAGS) -lclover2 $(LIBS)

lib: $(LIBSONAME)
#	rm -f install

########################################################
# clover2 libraries
########################################################
libclover2.so.$(SO_VERSION): $(LIB_OBJS)
	clang -shared -o libclover2.so.$(SO_VERSION) $(LIB_OBJS) -lc $(LIBS) $(CFLAGS)

libclover2.so: libclover2.so.$(SO_VERSION)
	ln -s -f libclover2.so.$(SO_VERSION) libclover2.so.1
	ln -s -f libclover2.so.$(SO_VERSION) libclover2.so

########################################################
# clover2 libraries on Darwin
########################################################
libclover2.$(SO_VERSION).dylib: $(OBJ)
	clang -dynamiclib -o libclover2.$(SO_VERSION).dylib $(OBJ) -lc $(LIBS) $(CFLAGS)

libclover2.dylib: libclover2.$(SO_VERSION).dylib
	cp libclover2.$(SO_VERSION).dylib libclover2.1.dylib
	cp libclover2.$(SO_VERSION).dylib libclover2.dylib

#########################################################
# Object files
#########################################################
$(OBJ): src/*.h Makefile configure

#########################################################
# uninstall
#########################################################
uninstall:
	rm -Rf ~/.clover2

#########################################################
# permission
#########################################################
permission:
	chmod 644 *
	chmod 755 .git man src configure
	chmod 644 src/*.c
	chmod 644 src/*.h

########################################################
# clean
########################################################
clean:
	rm -fR clover2 clover2.dSYM cclover2 cclover2.dSYM src/*.o libclover* config.log config.status *.stackdump autom4te.cache .DS_Store core.* a.out *.clcl *.clo code/*.clo

distclean: clean
	rm -fR  config.h Makefile autom4te.cache

########################################################
# test
########################################################
test:
	@echo "Compile to test code..."
	./cclover2 code/block_var_test.cl && ./clover2 code/block_var_test.clo
	./cclover2 -class code/user_object.clc code/user_object.cl && ./clover2 code/user_object.clo

