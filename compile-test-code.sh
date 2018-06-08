for i in *.bc
do
    if test $i != ExtTest.bc
    then
        ./bclover2 $i
    fi
done
