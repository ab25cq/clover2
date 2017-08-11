if [ -e Makefile ]
then
    make distclean
fi
if [ ! -e Makefile ]
then
    git add .
    git commit 
    git remote add bit-compiler https://github.com/ab25cq/clover2.git
    git push -u origin bit-compiler
fi
