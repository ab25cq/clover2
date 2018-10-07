for i in *.bc
do
    if test $i != ExtTest.bc && test $i != CloneTest.bc
    then
        ./bclover2 $i
    fi
done

