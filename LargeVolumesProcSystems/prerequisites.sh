wget poloclub.gatech.edu/cse6242/2015spring/hw3/graph1.tsv
wget poloclub.gatech.edu/cse6242/2015spring/hw3/graph2.tsv
sudo su hdfs
hadoop fs -mkdir /user/cse6242/
hadoop fs -chown cloudera /user/cse6242/
su cloudera
hadoop fs -put graph1.tsv /user/cse6242/graph1.tsv
hadoop fs -put graph2.tsv /user/cse6242/graph2.tsv
