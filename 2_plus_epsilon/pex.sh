for c in GHC/*; do
k=$(basename "$c" .txt)
m=$(wc -l <"$c")
for f in higgs_chunks/*; do
n=$(wc -l <"$f")
while read r; do
  ./pex.out "$n" "$k" "$r" "$m" "$c" "$f" 1>>"pexc/$k" 2>>"pexr/$k"
done <output2
done
done
