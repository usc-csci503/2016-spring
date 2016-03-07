#!/bin/sh

for f in /user/vagrant/bin /user/vagrant/dft1-out /user/vagrant/gutenberg /user/vagrant/gutenberg-out; do
  hadoop dfs -rmr $f
done
