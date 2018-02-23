if [ -e Makefile ]
then
    make distclean
fi
if [ ! -e Makefile ]
then
    git add .
    git commit 
    git remote add origin https://github.com/ab25cq/clover2.git
    git push -u origin master
fi

