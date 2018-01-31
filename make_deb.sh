mv ../clover2 ../clover2-3.5.6

cd .

if test -e Makefile
then
    make distclean
fi

(rm ../clover2_3.5.6.orig.tar.gz; cd ..; tar cvfz clover2_3.5.6.orig.tar.gz clover2-3.5.6)

sudo dpkg-buildpackage -us -uc
