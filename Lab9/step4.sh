for i in 100 1000 10000 100000; do
for j in 2 8 32 64; do
echo "100k $i thread $j";
time ./step4 100k $i $j
echo "1m $i thread $j"; 
time ./step4 1m $i $j
echo "10m $i thread $j"; 
time ./step4 10m $i $j
echo "100m $i thread $j";
time ./step4 100m $i $j

done
done
