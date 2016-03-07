#!/bin/sh

REMOTE_DATA=/user/vagrant/gutenberg
REMOTE_BINARY=/user/vagrant/bin/wordcount

hadoop dfs -copyFromLocal gutenberg $REMOTE_DATA
hadoop dfs -copyFromLocal wordcount $REMOTE_BINARY

hadoop pipes \
  -D hadoop.pipes.java.recordreader=true \
  -D hadoop.pipes.java.recordwriter=true \
  -input $REMOTE_DATA \
  -output dft1-out \
  -program $REMOTE_BINARY
