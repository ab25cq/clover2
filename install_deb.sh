#!/bin/bash

if test -e ../clover2_4.0.2-1_i386.deb
then
    if dpkg -l | egrep ^clover2
    then
        sudo apt-get remove clover2
    fi

    sudo dpkg -i ../clover2_4.0.2-1_i386.deb
fi

if test -e ../clover2_4.0.2-1_amd64.deb
then
    if dpkg -l | egrep ^clover2
    then
        sudo apt-get remove clover2
    fi

    sudo dpkg -i ../clover2_4.0.2-1_amd64.deb
fi
