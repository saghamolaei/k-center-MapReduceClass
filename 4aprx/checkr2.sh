for x in cc/*; do
for f in higgs_chunks/*; do
n=$(wc -l <"$f")
m=$(wc -l <"$x")
k=$(basename "$x")
./checkr2.out "$n" "$m" "$x" "$f" >>"GHC/$k"
done
done
