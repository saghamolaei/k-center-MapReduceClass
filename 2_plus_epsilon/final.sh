for f in *
do
cat $f <(echo "$f") >>../final
done