
ghc -o moveVarDecls moveVarDecls.hs

if test -e config.h
then
    cp config.h src/
else
    ./configure 
    cp config.h src/
fi

cd src

for i in *.c
do 
    ../moveVarDecls $i > ../src-c89/$i
done


cd ..
