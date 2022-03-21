for f in *
do
sort $f | uniq >../sorted/$f
done