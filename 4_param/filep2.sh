for f in *; do
num=$(wc -l $f | cut -f1 -d ' ')
k=1;
while read r; do
  ./../mrg.out $num $r <"$f" 1>>../pc/$k 2>>../pr/$k
  k=$((k+1))
done <../r2.txt
#dim=$(head -1 $f | wc -w)
done