for f in higgs_chunks/*; do
num=$(wc -l $f | cut -f1 -d ' ')
for k in {1..100}; do
#dim=$(head -1 $f | wc -w)
./mrg.out $num $k <"$f" 1>>coreset/$k.txt 2>>radii/$k.txt
done
done
