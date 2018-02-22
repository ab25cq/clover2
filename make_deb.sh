mv ../clover2 ../clover2-3.6.4

cd .

if test -e Makefile
then
    make distclean
fi

(rm ../clover2_3.6.4.orig.tar.gz; cd ..; tar cvfz clover2_3.6.4.orig.tar.gz clover2-3.6.4)

sudo dpkg-buildpackage -us -uc

sudo make uninstall

sudo rm -rf debian/clover2

mv ../clover2-3.6.4 ../clover2

cd .

if test -e Makefile
then
    make distclean
fi

