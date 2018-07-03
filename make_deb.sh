#!/bin/bash

mv ../clover2 ../clover2-4.5.0

cd .

if test -e Makefile
then
    make distclean
fi

(rm ../clover2_4.5.0.orig.tar.gz; cd ..; tar cvfz clover2_4.5.0.orig.tar.gz clover2-4.5.0)

sudo dpkg-buildpackage -us -uc

sudo make uninstall

sudo rm -rf debian/clover2

mv ../clover2-4.5.0 ../clover2

cd .

if test -e Makefile
then
    make distclean
fi

