for f in *.txt; do
k=$(basename "$f" .txt)
mx=$(sort -nr "$f"|head -1)
echo "$k" "$mx">>"../output2"
done
