hadoop jar ./target/task1-1.0.jar edu.gatech.cse6242.Task1 /user/cse6242/graph1.tsv /user/cse6242/task1output1
hadoop fs -getmerge /user/cse6242/task1output1/ task1output1.tsv
hadoop fs -rm -r /user/cse6242/task1output1
sort -g task1output1.tsv -o task1output1.tsv