matrix_sizes=( 1023 1024 1025 1040 1041 1050 1100 )
for n in "${matrix_sizes[@]}"
do
   valgrind --tool=cachegrind ./Simple $n >> Logs/Simple.log 2>&1
done

for n in "${matrix_sizes[@]}"
do
   valgrind --tool=cachegrind ./Block $n >> Logs/Block.log 2>&1
done

for n in "${matrix_sizes[@]}"
do
   valgrind --tool=cachegrind ./Swapped $n >> Logs/Swapped.log 2>&1
done