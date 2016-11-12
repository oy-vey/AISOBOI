spark-submit --class edu.gatech.cse6242.Task3 --master local \
  target/task3-1.0.jar skokleenko-graph-1 /user/hbase/graph1

hadoop fs -getmerge /user/hbase/graph1 task3output1.tsv
hadoop fs -rm -r /user/hbase/graph1
sort -g task3output1.tsv -o task3output1.tsv
