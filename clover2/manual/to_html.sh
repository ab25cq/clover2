for i in *.md
do
    pandoc -f markdown -t html $i > ${i%.md}.html
done
