k=1;
while read r; do
	num=$(wc -l $k | cut -f1 -d ' ')
  ./../mrg.out $num $r <"$k" 1>>../sc/$k 2>>../sr/$k
  k=$((k+1))
done <../rad2.txt
