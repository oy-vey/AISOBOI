spark-submit --class edu.gatech.cse6242.Task3 --master local \
  target/task3-1.0.jar skokleenko-graph-2 /user/hbase/graph2

hadoop fs -getmerge /user/hbase/graph2 task3output2.tsv
hadoop fs -rm -r /user/hbase/graph2
sort -g task3output2.tsv -o task3output2.tsv
