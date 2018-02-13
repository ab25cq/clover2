mv ../clover2 ../clover2-3.5.9

cd .

if test -e Makefile
then
    make distclean
fi

(rm ../clover2_3.5.9.orig.tar.gz; cd ..; tar cvfz clover2_3.5.9.orig.tar.gz clover2-3.5.9)

sudo dpkg-buildpackage -us -uc

sudo make uninstall

sudo rm -rf debian/clover2

mv ../clover2-3.5.9 ../clover2

cd .

if test -e Makefile
then
    make distclean
fi

