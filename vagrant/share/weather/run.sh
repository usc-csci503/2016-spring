#!/bin/sh

hadoop fs -rmr ncdc_data/
hadoop fs -rmr output/
hadoop fs -copyFromLocal ncdc_data ncdc_data

hadoop jar /opt/hadoop-1.2.1/contrib/streaming/hadoop-streaming-1.2.1.jar \
  -input ncdc_data/* \
  -output output \
  -mapper `pwd`/mapper.py \
  -reducer `pwd`/reducer.py

hadoop fs -copyToLocal output output
