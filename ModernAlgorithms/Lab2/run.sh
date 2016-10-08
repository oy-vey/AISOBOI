for n in `seq 1 1000`
do 
 echo 'Graph ¹' $n
 octave Graph500.m
 echo 
done