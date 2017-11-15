all: hello hello2 fun

hello:
	clover2 Hello.cl
hello2:
	cclover2 Hello2.clcl
	clover2 Hello2.cl
fun:
	clover2 fun.cl
dep_error:
	clover2 dep_error.cl
test:
	clover2 Hello2.cl
	clover2 Hello.cl
	clover2 fun.cl
configure:
	cd ../; ./configure --prefix=$HOME --with-optimize; make; sudo make install
make1:
	cd ../; make; sudo make install
	clover2 dep_error.cl
clean:
	rm -rf *.o*
clean2:
	rm -rf *.o*
