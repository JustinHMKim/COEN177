for i in 100 1000 10000 100000; do

echo "100k $i";
time ./step3 100k $i
echo "1m $i"; 
time ./step3 1m $i
echo "10m $i"; 
time ./step3 10m $i
echo "100m $i";
time ./step3 100m $i

done
