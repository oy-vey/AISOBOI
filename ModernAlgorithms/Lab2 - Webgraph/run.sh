for n in `seq 1 1000`
do 
 echo 'Graph �' $n
 octave Graph500.m
 echo 
done