#creating hbase tables : cf is a cloumn family for output vertex ("cf:out") and input ("cf:in") vertexcolumns
echo 'create "skokleenko-graph-1", "cf", "weight"' | hbase shell;
echo 'create "skokleenko-graph-2", "cf", "weight"' | hbase shell;
#creating temp tsv file with ID for HBASE_ROW_KEY
cat graph1.tsv | awk '{printf "%d\t%s\n", NR, $0}' > temp_graph1.tsv
cat graph2.tsv | awk '{printf "%d\t%s\n", NR, $0}' > temp_graph2.tsv
#moving files to hdfs
hadoop fs -mkdir -p /user/hbase/;
hadoop fs -chown cloudera /user/hbase/;
hadoop fs -put temp_graph1.tsv /user/hbase/graph1.tsv; 
hadoop fs -put temp_graph2.tsv /user/hbase/graph2.tsv;
#removing temp files
rm temp_graph1.tsv;
rm temp_graph2.tsv;
#importing graphs to habse via importtsv
hbase org.apache.hadoop.hbase.mapreduce.ImportTsv -Dimporttsv.columns=HBASE_ROW_KEY,cf:out,cf:in,weight skokleenko-graph-1 /user/hbase/graph1.tsv;
hbase org.apache.hadoop.hbase.mapreduce.ImportTsv -Dimporttsv.columns=HBASE_ROW_KEY,cf:out,cf:in,weight skokleenko-graph-2 /user/hbase/graph2.tsv;
echo 'count "skokleenko-graph-1"' | hbase shell; #321918 rows
echo 'count "skokleenko-graph-2"' | hbase shell; #53380274 rows
