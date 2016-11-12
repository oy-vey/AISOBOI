cat /home/cloudera/Ex1/graph1.tsv | python mapper.py | sort -g | python reducer.py > /home/cloudera/Ex1/hw3-skeleton/Task1/task1output1_python.tsv
cat /home/cloudera/Ex1/graph2.tsv | python mapper.py | sort -g | python reducer.py > /home/cloudera/Ex1/hw3-skeleton/Task1/task1output2_python.tsv
