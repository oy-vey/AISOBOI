package edu.gatech.cse6242


import org.apache.spark._
import org.apache.spark.rdd.NewHadoopRDD
import org.apache.spark.SparkContext._
import org.apache.hadoop.hbase.{HBaseConfiguration, HTableDescriptor}
import org.apache.hadoop.hbase.client.HBaseAdmin
import org.apache.hadoop.hbase.mapreduce.TableInputFormat
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hbase.HColumnDescriptor
import org.apache.hadoop.hbase.util.Bytes
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.HTable;





object Task3 {
  def main(args: Array[String]) {
    val sc = new SparkContext(new SparkConf().setAppName("Task3"))
    
    //Table name
    val tableName = args(0)

    val conf = HBaseConfiguration.create()
    // Add local HBase conf
    conf.addResource(new Path("/etc/hbase/conf/hbase-site.xml"))
    conf.set(TableInputFormat.INPUT_TABLE, tableName)

    //create rdd
    val hBaseRDD = sc.newAPIHadoopRDD(conf, classOf[TableInputFormat], 
      	classOf[org.apache.hadoop.hbase.io.ImmutableBytesWritable],
      	classOf[org.apache.hadoop.hbase.client.Result])

    //get the row count
   val count = hBaseRDD.map(line => (line._2)) //scan
                        .map(result => (result.getValue("cf".getBytes(), "in".getBytes()),
                                        result.getValue("weight".getBytes(), "".getBytes())))
                        .map(row => (row._1.map(_.toChar).mkString, row._2.map(_.toChar).mkString.toInt))
			

    val reduce = count.reduceByKey(_+_)
                      .map(line => line._1 + "\t" + line._2)

    reduce.saveAsTextFile("hdfs://localhost:8020" + args(1))
    System.exit(0)
  }
}

