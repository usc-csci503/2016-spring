# HADOOP using Vagrant

[Hadoop](http://hadoop.apache.org) is a MapReduce system developed by the [Apache](http://apache.org) foundation.  This tutorial walks you through the process of setting up a vagrant cluster for development and experimentation.


You can use the configuration as provided in one of two ways:

* Single node, or
* Multiple nodes

For a simple setup single node works fine.  If you want to play with a more complex configuration use the multiple nodes configuration.

### Single Node Configuration

The network setting for single node mode is:

```
node0 192.168.33.100
```

Start up your first single node:

```
cd cs-tools/hadoop
vagrant up node0 --provision
vagrant ssh node0
```

If you look at the `Vagrantfile` you will notice that in the single node mode, we reserve 1024 Mb of memory.  It is recommended that you pick of the two modes when doing testing and development.  You can run out of memory pretty quickly if not careful.

### Multiple Nodes Configuration

The network setting for single node mode is:

```
node1 192.168.33.101
node2 192.168.33.102
node3 192.168.33.103
node4 192.168.33.104
```

Start up your first single node:

```
cd cs-tools/hadoop
vagrant up node1 --provision
vagrant up node2 --provision
vagrant up node3 --provision
vagrant up node4 --provision
vagrant status
```

Now you can `ssh` to any of the four nodes.

## Running Hadoop

The instruction below is applicable to either single node or multiple nodes mode.

### Prepare the hadoop system

```
hadoop namenode -format
start-all.sh
```

### Run java `wordcount` program

```
hadoop dfs -copyFromLocal gutenberg/ /user/vagrant/gutenberg
hadoop dfs -ls /user/vagrant/gutenberg

hadoop jar /opt/hadoop-1.2.1/hadoop-examples-*.jar \
   wordcount /user/vagrant/gutenberg \
   /user/vagrant/gutenberg-out

hadoop dfs -ls /user/vagrant/gutenberg-out
hadoop dfs -copyToLocal /user/vagrant/gutenberg-out out
```

The output files should be copied to `out` folder.

### Run c++ `wordcount` program

```
cd /vagrant/wordcount
make
sh run.sh
hadoop dfs -ls dft1-out
hadoop dfs -copyToLocal dft1-out dft1-out
```

You can now examine the content of `dft1-out` and the result should match `out`.

## References

* [Running Hadoop on Ubuntu Linux (Single-Node Cluster)] (http://www.michael-noll.com/tutorials/running-hadoop-on-ubuntu-linux-single-node-cluster/)

* [Hadoop Tutorial 2.2 -- Running C++ Programs on Hadoop](http://www.science.smith.edu/dftwiki/index.php/Hadoop_Tutorial_2.2_--_Running_C++_Programs_on_Hadoop)
