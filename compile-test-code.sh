
for i in *.oclcl
do
    if test $i != ExtTest.oclcl && test $i != CloneTest.oclcl && test $i != EFTest.oclcl
    then
        ./bclover2 $i
    fi
done

./bclover2 EFTest.oclcl
